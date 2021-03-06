/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_wizhall_2.c
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
	set("short", HIW"巫師"NOR WHT"神殿 "NOR YEL"東南殿"NOR);
	set("long",@TEXT
    這間房間的四周圍著一群身穿白袍的理學家、數學家、哲學家、這些奇怪的人
皆朝房間的正中央舉起雙手，只見高速切換的影像在房間中央劇烈地閃爍著，原來
這些影像的內容竟是這些人所創造出來的，這些色彩繽紛的畫面中似乎隱含著各種
從未想到的構想，但見四周的這些人仍靜靜地往房間中央望著，完全不受旁人的影
響。
TEXT);

	set("exits", ([
		"west" : "/wiz/wizhall/room_wizhall_1",
	    ]));

	set("objects", ([
		"/obj/etc/mine.old" : 1,
	    ]));

	::reset_objects();
}
