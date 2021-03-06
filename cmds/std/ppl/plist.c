/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : plist.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-04-06
 * Note   : 玩家指令程式
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <skill.h>
#include <feature.h>
#include <daemon.h>

#define PRODUCT_MODULE_PATH "/std/module/product/"

inherit COMMAND;

private void do_command(object me, string arg)
{
	mapping info, subinfo;
	object materialob;
	string msg;
	string *products = get_dir(PRODUCT_MODULE_PATH);
	string *learned_products = query("learned_products", me) || allocate(0);
	if( !arg )
	{
		msg = "產品列表，目前共可生產 "+sizeof(products)+" 種產品\n";
		msg += WHT"─────────────────────────────────────\n"NOR;
		msg +=    "名稱                    生產工廠      設計書 製造耗時 最低價值\n"NOR;
		msg += WHT"─────────────────────────────────────\n"NOR;
		
		foreach(string product in products)
		{
			info = (PRODUCT_MODULE_PATH+product+"/module.c")->query_product_info();
			
			msg += sprintf("%-24s%-14s%-7s%-9d%s\n",
				info["name"]+"("+info["id"]+")",
				BUILDING_D->query_building(info["factory"])[0],
				member_array(product, learned_products) == -1 ? HIR"無"NOR:HIG"有"NOR,
				info["timecost"],
				info["value"],
				);
		}
		
		msg += WHT"─────────────────────────────────────\n"NOR;
		msg += "輸入 plist '產品ID' 可查詢細節資料\n\n";
	}
	else if( member_array(arg, products) != -1 )
	{
		info = (PRODUCT_MODULE_PATH+arg+"/module.c")->query_product_info();
		
		msg = info["name"]+"("+capitalize(info["id"])+")的詳細產品資料如下：\n";
		msg += WHT"─────────────────────────────────────\n"NOR;
		msg += WHT"產品名稱"NOR" "+info["name"]+"("+capitalize(info["id"])+")\n";
		msg += WHT"生產工廠"NOR" "+BUILDING_D->query_building(info["factory"])[0]+"\n";
		msg += WHT"產品價值"NOR" $"+info["value"]+"\n";
		msg += WHT"產品重量"NOR" "+info["mass"]+" g\n";
		msg += WHT"製造耗時"NOR" "+info["timecost"]+" 秒/單位\n";
		msg += WHT"科技耗費"NOR" "+info["technology"]+" 科技值\n";
		msg += WHT"研發費用"NOR" $"+NUMBER_D->number_symbol(info["cost"])+"\n";

		msg += WHT"製造原料\n"NOR;
		foreach( string material, int amount in info["material"] )
		{
			if( !objectp(materialob = load_object(material)) )
			{
				subinfo = (PRODUCT_MODULE_PATH+material+"/module.c")->query_product_info();
				msg += sprintf("         %-30s %d\n", subinfo["name"]+"("+capitalize(subinfo["id"])+")", amount);
			}
			else
				msg += sprintf("         %-30s %d\n", materialob->query_idname(), amount);
		}

		msg += WHT"技能需求\n"NOR;
		foreach( string skill, int level in info["skill"] )
			msg += sprintf("         %-30s 至少 %-3d 級\n", (SKILL(skill))->query_idname(), level);
		
		msg += WHT"─────────────────────────────────────\n"NOR;
	}
	tell(me, msg);
}