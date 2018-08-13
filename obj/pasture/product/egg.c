/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : egg.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : Âû³J
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("egg","Âû³J");
	
	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "²¤·L³z©úªº¥Õ¶À¦âÂû³J¡C\n");
	set("unit", "Áû");
	set("mass", 50);
	set("value", 100);
}
