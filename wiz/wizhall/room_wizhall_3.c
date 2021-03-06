/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_wizhall_3.c
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

inherit STANDARD_ROOM;

string help = @HELP
在這個平凡無奇的房間內並沒有任何特殊的資訊。
HELP;

void create()
{
	set("short", HIW"巫師"NOR WHT"神殿 "NOR YEL"東北殿"NOR);
	set("long",@TEXT
    這裡的四周擺滿了古老的書籍，泛黃的紙張上書寫著前人在這個世界中旅行的
點點滴滴，包括各種收集完整的遊戲資料與他們的心得感言，這種由無數經驗累積
而來的知識寶庫是無價的...。
TEXT);

	set("exits", ([
		"west" : "/wiz/wizhall/room_wizhall_4",
	    ]));

	set("objects", ([
		"/obj/etc/lotto":1,
	    ]));

	::reset_objects();
}
