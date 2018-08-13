/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : wool.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : ¦Ï¤ò
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("wool","¦Ï¤ò");
	
	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "¯Â¥Õ¦âªº¦Ï¤ò¡C\n");
	set("unit", "¶ô");
	set("mass", 100);
	set("value", 15000);
}
