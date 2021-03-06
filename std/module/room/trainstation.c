/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : trainstation.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-04-11
 * Note   : 火車站
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
#include <condition.h>
#include <delay.h>

inherit ROOM_ACTION_MOD;

// OGC
void do_ogc(object me, string arg)
{
	//object env = environment(me);

	if( me->is_delaying() )
		return tell(me, me->query_delay_msg());

        msg("$ME從口袋拿出奇怪的道具，開始做起奇怪的動作...喔...哦...哇...呦...耶。\n", me, 0, 1);
        
        me->faint();
}

// 購買車票
void do_buy(object me, string arg)
{
	
	
	
	
}

// 設定建築物內房間型態種類
nosave mapping action_info =
([
	"toilet"	:
	([
		"short"	: HIY"公共廁所"NOR,
		"help"	:
			([
"topics":
@HELP
    車站內的公共廁所。
read			閱讀書籍
HELP,
			]),
		"heartbeat":0,	// 實際時間 1 秒為單位
		"job": 0,
		"action":
			([
				"ogc"	:	(: do_ogc :),
			]),
	
	]),	
	"platform"	:
	([
		"short"	: HIY"月台"NOR,
		"help"	:
			([
"topics":
@HELP
    旅客搭車的月台。
HELP,
			]),
		"heartbeat":0,	// 實際時間 1 秒為單位
		"job": 0,
		"action":
			([

			]),
	
	]),	
	"lobby"	:
	([
		"short"	: HIY"車站"NOR YEL"大廳"NOR,
		"help"	:
			([
"topics":
@HELP
    購買車票的大廳。
HELP,
			]),
		"heartbeat":0,	// 實際時間 1 秒為單位
		"job": 0,
		"action":
			([
				"buy"	:	(: do_buy :),
			]),
	]),
]);

// 設定建築物資料
nosave array building_info = ({
	
	// 建築物之中文名稱
	HIY"火車站"NOR

	// 開張此建築物之最少房間限制
	,6

	// 城市中最大相同建築數量限制(0 代表不限制)
	,0

	// 建築物建築種類, GOVERNMENT(政府), ENTERPRISE(企業集團), INDIVIDUAL(私人)
	,GOVERNMENT

	// 建築物可建築區域, AGRICULTURE_REGION(農業), INDUSTRY_REGION(工業), COMMERCE_REGION(商業)
	,COMMERCE_REGION

	// 開張儀式費用
	,"50000000"
	
	// 建築物關閉測試標記
	,1

	// 繁榮貢獻度
	,40
	
	// 最高可加蓋樓層
	,1
	
	// 最大相同建築物數量(0 代表不限制)
	,0
	
	// 建築物時代
	,2
});
