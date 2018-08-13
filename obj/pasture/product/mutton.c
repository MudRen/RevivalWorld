/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : mutton.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : ¦Ï¦×
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("mutton","¦Ï¦×");
	
	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "±aµÛ¤@¼h«p¥Öªº¦Ï¦×¡C\n");
	set("unit", "¶ô");
	set("mass", 600);
	set("value", 12000);
}
