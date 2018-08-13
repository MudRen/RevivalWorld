/* This	program	is a part of RW	mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File	  : Rod.c
 * Author :
 * Date	  : 2003-5-3
 * Note	  : Rod
 * Update :
 *  o 2000-00-00  

 -----------------------------------------
 */

#include <ansi.h>

inherit	__DIR__"standard_rod";

void create()
{
	set_idname("carbonfiber rod", HIW"ºÒÅÖºû"NOR WHT"³¨¬ñ"NOR );

	set_temp("endurance", 1800);

	if( this_object()->set_shadow_ob() ) return;
	
	set("unit", "®Ú");
	set("value", 80000);
	set("mass", 200);
	set("rod_level", 80);
	set("level", 50);
	set("flag/no_amount", 1);
	set("badsell", 1);
}