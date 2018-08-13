/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : antler.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : ³À¯ñ
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("antler", "³À¯ñ");
	
	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "²Ê§§°íµwªº³À¯ñ¡C\n");
	set("unit", "°¦");
	set("mass", 300);
	set("value", 25000);
}
