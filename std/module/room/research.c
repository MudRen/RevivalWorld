/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : research.c
 * Author : Clode@RevivalWorld
 * Date   : 2006-01-07
 * Note   : 全球研發中心
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <map.h>
#include <feature.h>
#include <message.h>
#include <daemon.h>
#include <npc.h>
#include <skill.h>

inherit ROOM_ACTION_MOD;
#define PRODUCT_MODULE_PATH		"/std/module/product/"

#define RANDOM_THING			({ "豬血糕", "牛肉麵", "羊肉爐", "薑母鴉", "蛋炒飯", "人參雞", "臭豆腐", "肉圓", "大腸包小腸", "新竹貢丸", "碗粿", "米粉粳", "炒螺肉", "蚵仔麵線", "蚵仔煎" })

// 取得所有可以生產的產品 module 物件陣列
private object *query_available_products()
{
	string product;
	object *modules, module;
	
	modules = allocate(0);
	
	foreach(product in get_dir(PRODUCT_MODULE_PATH))
	{
		catch( module = load_object(PRODUCT_MODULE_PATH + product +"/module") );
		
		if( !objectp(module) ) continue;
		
		modules += ({ module });
	}
	
	return modules;
}

void do_list_action(object me, string arg)
{
	int i;
	string file, msg;
	object env = environment(me);
	object master = env->query_master();
	object product;
	mapping product_info;
	string *productslist = query("productslist", master);
	
	if( !sizeof(productslist) )
		return tell(me, "這個研發中心尚未設計出任何可以生產的產品。\n");
	
	msg = env->query_room_name()+"目前已經研發完成的產品依照最新發表順序如下表：\n";
	msg += WHT"───────────────────────────────────────\n"NOR;
	msg += HIW"編號 產品名稱                           產品種類          鑲嵌數 價值          \n"NOR;
	msg += WHT"───────────────────────────────────────\n"NOR;
	
	i = 0;
	foreach(file in productslist)
	{
		catch(product = load_object(file));
	
		if( !objectp(product) ) continue;
			
		product_info = product->query_product_info();
		
		msg += sprintf("%-4s %-34s %-18s%-7d%s\n", (++i)+".", product->query_idname(), product_info["name"]+"("+product_info["id"]+")", query("design/inlay", product), product_info["value"]);
	}
	
	msg += WHT"───────────────────────────────────────\n"NOR;
	
	me->more(msg);
}

void do_design_action(object me, string arg)
{
	string value;
	mapping product_info;
	object *products, product;
	object env = environment(me);
	object master = env->query_master();

	if( !arg )
	{
		string msg;
		mapping design = query("design", master);
		
		if( !mapp(design) )
			return tell(me, "目前沒有任何產品研發資料，是否要研發產品？(type, id, name, inlay, finish)\n");
			
		msg = "目前最新研發中的產品為：\n";
		msg += WHT"────────────────────\n"NOR;
		msg += NOR"產品種類(type) ："NOR+(design["type"]||"未設計")+"\n";
		msg += NOR"產品英文(id)   ："NOR+(design["id"]||"未設計")+"\n";
		msg += NOR"產品中文(name) ："NOR+(design["name"]||"未設計")+"\n";
		msg += NOR"鑲嵌物品(inlay)：\n"NOR;
			
		if( mapp(design["inlay"]) )
		foreach(string file, int num in copy(design["inlay"]))
		{
			file = replace_string(file, "#", "/");
			
			if( !file_exists(file) ) continue;

			product = load_object(file);
			
			if( !objectp(product) ) continue;
			
			msg += "                 "+QUANTITY_D->obj(product, num, 1)+"\n";
		}
		else
			msg += "                  未鑲嵌任何物品\n";
		
		msg += WHT"────────────────────\n"NOR;

		
		tell(me, msg);
		return;
	}

	if( query("owner", env) != me->query_id(1) )
		return tell(me, pnoun(2, me)+"不是這間全球研發中心的擁有者。\n");

	sscanf(arg, "%s %s", arg, value);
	
	switch(arg)
	{

		case "type":
		{
			if( !value || !value[0] )
				return tell(me, pnoun(2, me)+"想要研發哪一種產品(plist)？\n");

			products = query_available_products();
		
			if( !sizeof(products) )
				return tell(me, "這種工廠目前無法研發任何產品。\n");
			
			foreach( product in products )
			{
				product_info = product->query_product_info();
						
				if( product_info["id"] == value )
				{
					if( query("technology", master) < product_info["technology"] )
						return tell(me, "研發中心目前累積的科技值不足以開發此種產品。\n");

					if( member_array(value, query("learned_products", me)||allocate(0)) == -1 )
						return tell(me, pnoun(2, me)+"不明白這個東西該怎麼製造，得先找到產品設計圖研究一下。\n");

					foreach(string skill, int level in product_info["skill"])
						if( me->query_skill_level(skill) < level )
							return tell(me, pnoun(2, me)+"的"+(SKILL(skill))->query_name()+"等級不足 "+level+" 無法研發此項產品。\n");

					msg("$ME耗費了 "+product_info["technology"]+" 點的科技值進行「"+product_info["name"]+"("+product_info["id"]+")」種類產品的開發。\n", me, 0, 1);
					
					addn("technology", -product_info["technology"], master);
					
					set("design/type", value, master);

					master->save();
					return;
				}
			}
			
			return tell(me, "無法研發 "+value+" 這種產品，"+pnoun(2, me)+"想要研發哪一種產品(plist)？\n");
			break;
		}
		case "name":
		{
			if( !value || !value[0] )
				return tell(me, pnoun(2, me)+"想要替產品取什麼樣的中文名稱？\n");

			value = kill_repeat_ansi(value+NOR);
			
			if( !is_chinese(value) )
				return tell(me, "請用「中文」取產品的中文名稱。\n");
			
			if( noansi_strlen(value) > 16 || noansi_strlen(value) < 2 )
				return tell(me, "中文名字必須在 1 到 8 個中文字之間。\n");
			

			msg("$ME將產品之中文名稱設計為「"+value+"」。\n", me, 0, 1);
			
			set("design/name", value, master);
			
			master->save();
			break;
		}
		case "id":
		{
			if( !value || !value[0] )
				return tell(me, pnoun(2, me)+"想要替產品取什麼樣的英文名稱？\n");

			value = kill_repeat_ansi(lower_case(value)+NOR);

			if( !is_english(value) )
				return tell(me, "請用「英文」取產品的英文名稱。\n");
			
			if( noansi_strlen(value) > 16 || noansi_strlen(value) < 3 )
				return tell(me, "英文名稱必須在 3 到 16 個英文字數之間。\n");

			value = replace_string(value, " ", "-");

			msg("$ME將產品之英文名稱設計為「"+value+"」。\n", me, 0, 1);
			
			set("design/id", value, master);
			
			master->save();
			break;
		}
		case "delete":
		{
			string *productslist = query("productslist", master)||allocate(0);
			int num;
			
			if( !value || !value[0] || !to_int(value) )
				return tell(me, "請輸入正確的編號。\n");
			
			num = to_int(value) - 1;
				
			if( num < 0 || num > sizeof(productslist)-1 )
				return tell(me, "沒有這個編號的產品。\n");
			
			product = load_object(productslist[num]);
			
			productslist = productslist[0..num-1] + productslist[num+1..];
			
			set("productslist", productslist, master);
			
			msg("$ME將編號為 "+value+" 的產品「$YOU」從研發產品列表中刪除。\n", me, product, 1);
			break;
		}
		case "inlay":
		{
			object ob;
			
			if( !value || !value[0] )
				return tell(me, pnoun(2, me)+"想要將什麼物品鑲嵌在產品中？\n");
			
			if( !objectp(ob = present(value, me)) )
				return tell(me, pnoun(2, me)+"的身上沒有 "+value+" 這種物品。\n");
			
			if(me->is_equipping_object(ob) )
				return tell(me, pnoun(2, me)+"必須先卸除"+ob->query_idname()+"的裝備狀態。\n");

			addn("design/inlay/"+replace_string(base_name(ob), "/", "#"), 1, master);

			msg("$ME將$YOU鑲嵌到產品設計模型上進行測試，產品的表面隱隱發出"HIW"奇特"NOR"的"WHT"光芒"NOR"。\n", me, ob, 1);	
			
			destruct(ob, 1);
			master->save();
			me->save();
			break;
		}
		case "finish":
		{
			string *productslist = query("productslist", master)||allocate(0);
			string type = query("design/type", master);
			string id = query("design/id", master);
			string name = query("design/name", master);
			mapping inlay = query("design/inlay", master);
			int inlay_num;
			
			
			if( !type )
				return tell(me, "未設定生產產品種類。\n");

			if( !id )
				return tell(me, "未設定產品英文名稱。\n");

			if( !name )
				return tell(me, "未設定產品中文名稱。\n");
		
			product = load_object("/product/"+type+"/"+SERIAL_NUMBER_D->query_serial_number("product/"+type));
			
			product_info = product->query_product_info();
			
			product->set_idname(id, name);

			set("mass", product_info["mass"], product);
			set("value", product_info["value"], product);
			set("class", product_info["class"], product);
			set("design/owner", me->query_id(1), product);
			set("design/room", env->query_room_name(), product);
			set("design/time", time(), product);
			set("design/btype", env->query_building_type(), product);
			
			// 作鑲嵌物的設定
			if( mapp(inlay) )
			{
				inlay_num = implode(values(inlay), (: $1+$2 :));
				product->query_module_file()->setup_inlay(product, inlay);
				set("design/inlay", inlay_num, product);
			}

			product->save();			
			productslist = ({ base_name(product) }) | productslist;
			
			delete("design", master);

			set("productslist", productslist, master);
			master->save();

			CHANNEL_D->channel_broadcast("city", me->query_idname()+"的"+query("short", env)+"完成最新「"+product_info["name"]+"("+product_info["id"]+")」產品設計並命名為「"+product->query_idname()+"」，鑲嵌物品數 "HIW+inlay_num+NOR"，價值為 "HIY+NUMBER_D->number_symbol(product_info["value"])+NOR"。", me);

			break;
		}
		default:
			return tell(me, "無法開發 "+arg+" 這種產品。\n");
			break;
	}
}

void heart_beat(object room)
{
	int technologylevel;
	int researchmanage;
	int technology;
	int userinside;
	int npcinside;

	object npc, ob;
	object *npcs = allocate(0);
	string *slaves = room->query_slave();

	if( !query_temp("research_heart_beat", room) )
		set_temp("research_heart_beat", random(1024), room);
		
	if( !(addn_temp("research_heart_beat", 1, room)%240) )
	{
		room->save();
		npcs->save();
	}

	foreach(ob in all_inventory(room))
	{
		if( ob->is_module_npc() && query("job/cur", ob) == ENGINEER )
		{
			npcs += ({ ob });
			++npcinside;
		}
		
		if( userp(ob) )
			userinside = 1;
	}
	
	if( npcinside )
	{
		foreach(npc in npcs)
		{
			technologylevel += npc->query_skill_level("technology");
			researchmanage += npc->query_skill_level("researchmanage");
		}
		
		technologylevel /= npcinside;
		researchmanage /= 5;

		npc = npcs[random(sizeof(npcs))];
	}

	set("technologylevel", technologylevel, room);
	set("researchmanage", researchmanage, room);

	if( researchmanage < sizeof(slaves) + 1 )
	{
		if( userinside )
			broadcast(room, "研發管理的能力無法支撐過量的研發中心連鎖。\n");
		return;	
	}

	if( npcinside)
	{
		if( random(technologylevel) < 10 )
		{
			technology = to_int((-random(5)-1) * pow(sizeof(slaves)+1, 0.3));
			
			if( userinside )
			{
				if( !random(2) )
					msg("$ME打了個大呵欠，「呵∼碰！」口水滴到電路板上把設備給燒壞了！(科技值 "HIR+technology+NOR")\n", npc, 0, 1);
				else
					msg("$ME突發奇想把「"HIY+RANDOM_THING[random(sizeof(RANDOM_THING))]+NOR"」通通往化學原料裡倒，只見濃濃"WHT"黑煙"NOR"佈滿整個實驗室！(科技值 "HIR+technology+NOR")\n", npc, 0, 1);
			}
		}
		else
		{
			technology = random(to_int(pow(technologylevel / 6 * (sizeof(slaves)+1), 0.5)));
			
			if( userinside )
			{
				if( !random(2) )
					msg("$ME依循著標準的實驗程序，將編號 "+sprintf(HIG"%c%c"NOR GRN"%d%d%d%d%d"NOR, range_random(65,90),range_random(65,90),random(10),random(10),random(10),random(10),random(10))+" 的實項項目如期完成。(科技值 "HIG"+"+technology+NOR")\n", npc, 0, 1);
				else
					msg("$ME從失敗中獲取經驗，將原本錯誤的研究資料重新整理改寫。(科技值 "HIG"+"+technology+NOR")\n", npc, 0, 1);
			}
		}
	}
	
	addn("technology", technology, room);
	addn("total_technology", technology, room);
}

// 設定建築物內房間型態種類
nosave mapping action_info =
([
	"laboratory"	:
	([
		"short"	: HIC"研發"NOR CYN"實驗室"NOR,
		"heartbeat":60,	// 實際時間 1 秒為單位
		"job"	: ENGINEER,
		"master": 1,
		"help"	:
			([
"topics":
@HELP
    提供產品的製造與科技研發。
HELP,


"design":
@HELP
設計全新產品的指令，用法如下：[管理指令]
  design type gold		- 生產金(gold)類的產品，所有產品種類可用 plist 查詢
  design id gold wire		- 將產品的英文名稱設定為 gold wire (可使用色碼)
  design name 金線		- 將產品的中文名稱設定為 金線 (可使用色碼)
  design inlay '物品'		- 將某些特殊物品試著鑲嵌到產品模型上
  design delete 3		- 將研發產品列表中編號為 3 的產品資訊刪除
  design finish			- 完成產品設計，發表新產品
HELP,

"list":
@HELP
列出已經研發成功的產品列表，用法如下：
  list		 		- 列出已經研發成功的產品列表
HELP,
			]),
		"action":
			([
				"design"		: (: do_design_action($1, $2) :),
				"list"			: (: do_list_action($1, $2) :),
			]),
	]),
]);

string look_room(object env)
{
	string msg = "";
	object master = env->query_master();
		
	msg += "科技值 "HIC+query("technology", master)+NOR CYN"/"+query("total_technology", master)+NOR" ";
	msg += "平均研發力 "HIY+query("technologylevel", master)+NOR+" ";
	msg += "研發管理 "HIY+(sizeof(master->query_slave())+1)+"/"+query("researchmanage", master)+NOR+"\n";
	
	return msg;
}

// 設定建築物資料
nosave array building_info = ({
	
	// 建築物之中文名稱
	HIC"全球"NOR CYN"研發中心"NOR

	// 開張此建築物之最少房間限制
	,1

	// 城市中最大相同建築數量限制(0 代表不限制)
	,0

	// 建築物建築種類, GOVERNMENT(政府), ENTERPRISE(企業集團), INDIVIDUAL(私人)
	,INDIVIDUAL

	// 建築物可建築區域, AGRICULTURE_REGION(農業), INDUSTRY_REGION(工業), COMMERCE_REGION(商業)
	,COMMERCE_REGION

	// 開張儀式費用
	,"9000000"

	// 建築物關閉測試標記
	,1

	// 繁榮貢獻度
	,5
	
	// 最高可加蓋樓層
	,2
	
	// 最大相同建築物數量(0 代表不限制)
	,1
	
	// 建築物時代
	,2
});

