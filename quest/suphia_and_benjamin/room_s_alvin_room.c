/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_s_alvin_room.c
 * Author : tzj@RevivalWorld
 * Date   : 2006-09-10
 * Note   : 蘇菲亞的弟弟－阿爾文的臥室
 * Update :
 *  
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
	set("short", HIC"臥室"NOR);
	set("long",@TEXT
　　這裡是蘇菲亞弟弟－阿爾文的臥室，反正就是一個十二歲頑皮小男孩的房間！
TEXT);


	set("exits", ([
		//往東走是牆
		//"east"    : ,
		
		//往南走是牆
		//"south" : ,
		
		//往西回到客廳
		"west"    : "/quest/suphia_and_benjamin/room_s_frontroom",
		
		//往北走是牆
		//"north" : ,
		
	]));

	set("lock/west", 1);
/*	預留放NPC或物品的...
	set("objects", ([
		"/quest/suphia_and_benjamin/npc_suphia" : 1 ,
	]));
*/
	
	::reset_objects();
	replace_program(STANDARD_ROOM);
}
