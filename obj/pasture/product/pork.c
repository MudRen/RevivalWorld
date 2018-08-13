/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : pork.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : ½Þ¦×
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("pork","½Þ¦×");
	
	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "¦×½èÂ×º¡ªº½Þ¦×¡C\n");
	set("unit", "¶ô");
	set("mass", 600);
	set("value", 7000);
}
