/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : beef.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : ¤û¦×
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("beef","¤û¦×");
	
	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "ªþº¡¤ûµ¬ªº¤û¦×¡C\n");
	set("unit", "¶ô");
	set("mass", 600);
	set("value", 18000);
}
