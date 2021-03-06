/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : fuel.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-04-06
 * Note   : 化石燃料
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <material.h>
#include <ansi.h>
#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("fuel",HIM"燃料"NOR);

	if( this_object()->set_shadow_ob() ) return;
	
	set("material/"+FUEL, 1);
	set("unit","單位");
	set("mass", 1000);
	set("value", 10);
}