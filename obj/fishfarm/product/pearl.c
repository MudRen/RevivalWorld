/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : pearl.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-10
 * Note   : ¬Ã¯]
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("pearl","¬Ã¯]");
	
	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "¯Â¥ÕµL·åªº¬Ã¯]¡C\n");
	set("unit", "Áû");
	set("mass", 50);
	set("value", 60000);
}
