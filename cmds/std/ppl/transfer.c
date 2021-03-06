/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : transfer.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-03-03
 * Note   : transfer 指令
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <feature.h>
#include <daemon.h>
#include <location.h>
#include <map.h>
#include <roommodule.h>

inherit COMMAND;

string help = @HELP
    房地產產權轉移指令，除了員工轉移時所有房間設定與內容物將一併
轉移，景觀、農田等非建築物則無法轉移。

transfer here to 'ID'	- 將此地房地產轉移給另一個玩家
HELP;


private void do_command(object me, string arg)
{
	string targetid;
	object targetob;
	array loc = query_temp("location", me);
	mapping estdata;
	array building_info;
	array loctemp;
	int target_architectonic_level;

	if( !arrayp(loc) || !environment(me)->is_maproom() )
		return tell(me, pnoun(2, me)+"必須站在建築門口進行房地產移轉。\n");
		
	if( ESTATE_D->whose_estate(loc) != me->query_id(1) )
		return tell(me, "這棟建築物並不是屬於"+pnoun(2, me)+"的。\n");

	estdata = ESTATE_D->query_loc_estate(loc);

	if( CITY_D->query_coor_data(loc, TYPE) != DOOR )
		return tell(me, pnoun(2, me)+"只能轉移建築物的房地產。\n");
	
	if( !arg || !sscanf(arg, "here to %s", targetid) )
		return tell(me, help);
	
	if( !objectp(targetob = find_player(targetid)) )
		return tell(me, "目前線上沒有 "+targetid+" 這位玩家。\n");
	
	if( me == targetob )
		return tell(me, "無法轉移房地產給自己。\n");

	if( query("city", targetob) != query("city", me) )
		return tell(me, "只能將房地產轉移給同一座城市的市民。\n");

	if( !same_environment(me, targetob) )
		return tell(me, targetob->query_idname()+"必須來到這裡才能進行房地產轉移。\n");

	target_architectonic_level = targetob->query_skill_level("architectonic") + targetob->query_skill_level("architectonic-adv");
	
	foreach(string sloc in estdata["roomtable"])
	{
		loctemp = restore_variable(sloc);	
		
		if( target_architectonic_level < sizeof(city_roomfiles(loctemp))-1 )
			return tell(me, targetob->query_idname()+"的建築技術技能等級不足以承受這樣的建築物。\n");
	}
	
	building_info = BUILDING_D->query_building(estdata["type"]);
	
	if( building_info[ROOMMODULE_MAXLIMIT] > 0 && ESTATE_D->query_owner_amount(targetid, estdata["type"]) >= building_info[ROOMMODULE_MAXLIMIT] )
		return tell(me, targetob->query_idname()+"的此種建築物數量已經到達上限。\n");

		
	if( !ESTATE_D->transfer_estate(me->query_id(1), targetob->query_id(1), loc) )
		return tell(me, "房地產轉移發生錯誤，請通知巫師處理。\n");
	
	CHANNEL_D->channel_broadcast("city", me->query_idname()+"將位於"+CITY_D->query_city_idname(loc[CITY], loc[NUM])+"("+(loc[X]+1)+","+(loc[Y]+1)+")的房地產轉移給"+targetob->query_idname()+"。", me);
	msg("$ME正式將此建築物的房地產轉移給$YOU。\n", me, targetob, 1);
}
