/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : red_envelope_2006_no_function.c
 * Author : Clode@RevivalWorld
 * Date   : 2006-01-28
 * Note   : ¤þ¦¦ª¯¦~¬õ¥]
 * Update :
 *  o 2003-00-00  

 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname(HIR"red envelope 2006"NOR, HIY"¤þ¦¦"NOR YEL"ª¯¦~"HIC"¬ö"NOR CYN"©À"HIR"¬õ"NOR RED"¥]"NOR);
	
	if( this_object()->set_shadow_database() ) return;
	
	set("unit", "­Ó");
	set("long", "2006 ¤þ¦¦ª¯¦~¬ö©À¬õ¥]");
	set("mass", 100);
	set("value", 100);
	set("flag/no_amount", 1);
}
