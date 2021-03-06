/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : recycle.c
 * Author : Clode@RevivalWorld
 * Date   : 2003-05-03
 * Note   : 垃圾回收場動作物件
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

inherit ROOM_ACTION_MOD;

#define RECYCLE_MONEY	10

void do_recycle(object me, string arg)
{
	//mixed value;
	//string money = "0", moneyunit;
	string msg="", amount;
	object ob, env = environment(me);

	if( !arg )
		return tell(me, "目前回收總數："+NUMBER_D->number_symbol(query("numbers", env))+" 個。\n", CMDMSG);

	if( sscanf(arg, "%s %s", amount, arg) == 2 )
	{
		if( amount == "all" ) ;
		// 如果 amount 並不是數字單位
		else if( !big_number_check(amount) )
		{
			arg = amount + " " + arg;
			amount = "1";	
		}	
		else if( count(amount, "<", 1) ) amount = "1";
	}
	else amount = "1";
	
	//moneyunit = MONEY_D->city_to_money_unit(env->query_city());
	
	if( objectp(ob = present(arg, me)) )
	{
		if( amount != "all" && count(amount, ">", query_temp("amount", ob)||1) ) 
			return tell(me, pnoun(2, me)+"身上只有 "+(query_temp("amount",ob)||1)+" "+(query("unit",ob)||"個")+ob->query_idname()+"。\n", CMDMSG);
		
		if( ob->is_keeping() )
			return tell(me, pnoun(2, me)+"必須先解除"+ob->query_idname()+"的保留(keep)狀態。\n");

		if( amount == "all" )
			amount = (query_temp("amount", ob)||"1")+"";
		
		// 因匯差過大會造成買賣獲利, 暫時 mark
		//value = query("value", ob);
		//if( count(value, ">", RECYCLE_MONEY) || count(value, "<=", 0) )
		//	money = count(amount, "*", RECYCLE_MONEY);
		//else
		//	money = count(amount, "*", count(value, "/", 2));
		
		//me->earn_money(moneyunit, money);

		set("numbers", count(query("numbers", env), "+", amount), env);
		msg("$ME把"+QUANTITY_D->obj(ob, amount)+"丟進資源回收桶，目前回收總數："+NUMBER_D->number_symbol(query("numbers", env))+" 個。\n", me, 0, 1);
		
		destruct(ob, amount);
		return;
	}
	
	if( lower_case(arg) == "all" )
	{
		object *all_ob = all_inventory(me);
		
		if( sizeof(all_ob) )
		{
			foreach(ob in all_ob)
			{
				amount = query_temp("amount",ob)||"1";
				
				if( ob->is_keeping() || (count(query("value", ob),">",0) && query_temp("endurance", ob)>=0) ) continue;
			
				msg += HIG"．"NOR+QUANTITY_D->obj(ob, amount, 1)+"\n";
				
				//value = query("value", ob);

				//if( count(value, ">", RECYCLE_MONEY) || count(value, "<=", 0) )
				//	money = count(money, "+", count(amount, "*", RECYCLE_MONEY));
				//else
				//	money = count(money, "+", count(amount, "*", count(value, "/", 2)));
				
				set("numbers", count(query("numbers", env), "+", amount), env);
				destruct(ob);
			}

			//me->earn_money(moneyunit, money);

			return msg("$ME把身上能夠回收的東西全部丟進資源回收桶了。目前回收總數："+NUMBER_D->number_symbol(query("numbers", env))+" 個。\n"NOR, me, 0, 1);
		}
		return tell(me, pnoun(2, me)+"身上沒有東西可以回收！\n", CMDMSG);
	}
	
	return tell(me, pnoun(2, me)+"身上沒有 "+arg+" 這件物品。\n", CMDMSG);
}
	

// 設定建築物內房間型態種類
nosave mapping action_info =
([
	"recycle"	:
	([
		"short"	: NOR GRN"回收室"NOR,
		"help"	:
			([
"topics":
@HELP
    回收中心可以回收所有任何不具價值的物品，同時為了獎勵環保，每回收一件物品可得 10 元獎金。
HELP,

"recycle":
@HELP
回收資源的指令，用法如下：
  recycle		- 顯示目前已回收總數
  recycle all		- 回收身上所有不具價值的物品
  recycle garbage	- 回收 1 件 garbage 物品
  recycle 3 garbage	- 回收 3 件 garbage 物品
HELP,

			]),
		"action":
			([
				"recycle"	: (: do_recycle :),
			]),
	]),
]);


// 設定建築物資料
nosave array building_info = ({
	
	// 建築物之中文名稱
	HIG"垃圾回收場"NOR

	// 開張此建築物之最少房間限制
	,1

	// 城市中最大相同建築數量限制(0 代表不限制)
	,0

	// 建築物建築種類, GOVERNMENT(政府), ENTERPRISE(企業集團), INDIVIDUAL(私人)
	,GOVERNMENT

	// 建築物可建築區域, AGRICULTURE_REGION(農業), INDUSTRY_REGION(工業), COMMERCE_REGION(商業)
	,AGRICULTURE_REGION | INDUSTRY_REGION | COMMERCE_REGION

	// 開張儀式費用
	,"5000000"

	// 建築物關閉測試標記
	,0

	// 繁榮貢獻度
	,30
	
	// 最高可加蓋樓層
	,1
	
	// 最大相同建築物數量(0 代表不限制)
	,0
	
	// 建築物時代
	,1
});
