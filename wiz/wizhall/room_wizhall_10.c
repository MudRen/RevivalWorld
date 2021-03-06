/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_wizhall_10.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-01-10
 * Note   : 標準房間
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>

inherit STANDARD_ROOM;

string help = @HELP
在這個平凡無奇的房間內並沒有任何特殊的資訊。
HELP;

void create()
{
	set("short", HIW"設計"NOR WHT"研究室"NOR);
	set("long",@TEXT
    設計研究室上方懸掛著中古時代西方風格的水晶弔燈，屋外的陽光藉由五彩
繽紛的玻璃映射進來。
TEXT);

	set("exits", ([
		"south" : "/wiz/wizhall/room_wizhall_9",
		"north" : "/wiz/wizhall/room_wizhall_11",
	]));
	
	set("objects", ([
		"/obj/board/class_design" : 1,
	]));
	
	::reset_objects();
}
