/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_wizhall_6.c
 * Author : Clode@RevivalWorld
 * Date   : 2003-08-23
 * Note   : 標準房間
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>
#include <daemon.h>

inherit STANDARD_ROOM;

string help = @HELP
在這個平凡無奇的房間內並沒有任何特殊的資訊。
HELP;

mapping actions;

void init(object ob);

void do_join(object me, string arg)
{
	if( query("newbiemaster", me) )
		return tell(me, pnoun(2, me)+"已經是新手指導員了。\n");

	if( query("total_online_time", me) < 6*30*24*60*60 )
		return tell(me, pnoun(2, me)+"的遊戲時間未超過六個月，無法擔任新手指導員。\n");

	if( wizardp(me) )
		return tell(me, "巫師無法擔任新手指導員。\n");

	me->add_title(HIY"新手"NOR YEL"指導員"NOR);
	set("newbiemaster", 1, me);

	CHANNEL_D->channel_broadcast("news", me->query_idname()+"自願擔任義務性的"HIY"新手"NOR YEL"指導員"NOR"，請大家鼓掌，新手有任何問題皆可向"+pnoun(3, me)+"詢問。\n");

	me->save();

	init(0);
}

void do_leave(object me, string arg)
{
	if( !query("newbiemaster", me) )
		return tell(me, pnoun(2, me)+"原本就不是新手指導員。\n");

	me->remove_title(HIY"新手"NOR YEL"指導員");
	delete("newbiemaster", me);

	CHANNEL_D->channel_broadcast("news", me->query_idname()+"卸除新手指導員的職務，請大家為"+pnoun(3, me)+"之前的貢獻鼓掌。\n");

	me->save();

	init(0);
}

void create()
{
	set("short", HIW"巫師"NOR WHT"神殿 "NOR YEL"西南殿"NOR);

	set("exits", ([
		"east" : "/wiz/wizhall/room_wizhall_1",
	    ]));

	set("objects", ([
	    ]));

	init(0);

	actions = ([
	    "join" : (: do_join :),
	    "leave": (: do_leave :),
	]);

	::reset_objects();
}

void init(object ob)
{
	object master_player;

	string roomlong = @TEXT
    這裡是新手的指導員休息室，到處擺滿了各種詭異的教學道具，看來每位指導
員都很辛苦的指導新手進入這個廣大的世界，但儘管辛苦，指導員們卻是樂此不疲
，同時更是結交了許多好友，只見牆壁上的電子看板正列出目前的線上新手指導員
名單，有任何遊戲上的問題問他們就對了，下達指令「tell "id" XXXX」便可以與
他們溝通談話，當然他們大多數也是大忙人，不一定會回答你的談話，可以多試幾
位指導員或是直接輸入「chat XXXX」在公共頻道上發問。
TEXT;

	roomlong += HIY"\n城市                     線上新手指導員 ID\n"NOR;

	foreach( master_player in users() )
	{
		if( query("newbiemaster", master_player) )
			roomlong += sprintf(HIY"%-24s"NOR" %-30s\n", CITY_D->query_city_idname(query("city", master_player))||"無國籍", master_player->query_idname());
	}

	set("long", roomlong);
}
