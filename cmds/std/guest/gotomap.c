/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : gotomap.c
 * Author : Cookys@RevivalWorld
 * Date   : 2002-3-18
 * Note   : 直接進入地圖指令。
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <daemon.h>
#include <feature.h>
#include <location.h>
#include <map.h>
#include <message.h>

inherit COMMAND;

string help = @HELP
	標準 gotomap 指令。
HELP;

private void do_command(object me, string arg)
{
	string city;
	int num, x, y;
	array loc;
	
	if( !is_command() ) return;
	
	if( !arg )
		return tell(me, "請輸入正確的地圖名稱, 編號, 座標。(例: gotomap center 1 10,10)\n");
	
	if( sscanf(arg, "'%s' %d %d,%d", city, num, x, y) ==4 || sscanf(arg, "%s %d %d,%d", city, num, x, y) == 4 )
	{
		loc = arrange_city_location(x-1, y-1, city, num-1);
		
		if( !MAP_D->query_map_system(loc) )
			return tell(me, "這是不合理的地圖座標。\n");
				
		msg(HIW"$ME走進通往地圖座標 "+NOR WHT+arg+HIW" 的空間傳送閘門。\n"NOR, me, 0, 1);
	
		me->move(loc);
		
		msg(HIW"$ME突然從空間傳送閘門中走了出來。\n"NOR, me, 0, 1);
	}
	else if( sscanf(arg, "'%s' %d", city, num) == 2 || sscanf(arg, "%s %d", city, num) == 2 )
	{
		loc = CITY_D->query_section_info(city, num-1, "wizhall");

		if( !MAP_D->query_map_system(loc) )
			return tell(me, "這是不合理的地圖座標。\n");	
		
		msg(HIW"$ME走進通往地圖座標 "+NOR WHT+arg+HIW" 的空間傳送閘門。\n"NOR, me, 0, 1);
		
		me->move(loc);
		
		msg(HIW"$ME突然從空間傳送閘門中走了出來。\n"NOR, me, 0, 1);
	}
	else
		return tell(me, "請輸入正確的地圖名稱, 編號, 座標。(例: gotomap center 1 10,10)\n");
}

