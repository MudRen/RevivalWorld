/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : clode.c
 * Author : Clode@RevivalWorld
 * Date   : 2002-3-27
 * Note   : Clode的個人板
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>

inherit BULLETIN_BOARD;

void create()
{
	set_idname("cookys board", HIC"餅乾"NOR  BYEL"的"BCYN"留"BGRN"言"BRED"板"NOR);

	// 利用 shadow_ob 技術來做分散式公佈欄, 即時資料皆儲存於 shadow_ob 上
	if( clonep() ) 
		set("shadow_ob", find_object(base_name(this_object())));

	else
	{
		set("boardid", "cookys");
		set("capacity", 2000);

		initialize_board();
	}
	startup_action();
}
