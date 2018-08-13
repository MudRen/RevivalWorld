/* This	program	is a part of RW	mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File	  : worm.c
 * Author :
 * Date	  : 2003-5-27
 * Note	  : ³½»ç
 * Update :
 *  o 2000-00-00  

 -----------------------------------------
 */

#include <ansi.h>
#include <message.h>
#include <inherit.h>

inherit	STANDARD_OBJECT;

int is_bait()
{
	return 1;
}
void create()
{
	set_idname("worm", "³L°C");
	set_temp("status", HIY"³½»ç"NOR);

	if( this_object()->set_shadow_database() ) return;

	set("unit", "±ø");
	set("value", 2);
	set("mass", 2);
	set("bait", 30);
	set("badsell", 1);

}