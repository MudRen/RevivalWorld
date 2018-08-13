/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : justice.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-12-20
 * Note   : ¼f§PªÌ
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>
#include <feature.h>
#include <equipment.h>
#include <buff.h>

inherit STANDARD_OBJECT;
inherit EQUIPMENT;

void create()
{
	set_idname(HIW"jus"NOR WHT"tice"NOR, HIW"¼f"NOR WHT"§P"HIW"ªÌ"NOR);
	set_temp("status", HIW"¥v"NOR WHT"¸Ö");

	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "¾Ö¦³·¥­PÅv¤Oªº«Ò¤ý®yÃM¡C\n");
	set("unit", "§â");
	set("mass", 0);
	set("value", 100000000);
	set("flag/no_amount", 1);
	set(BUFF_STR, 60);
	set(BUFF_STAMINA_REGEN, 10);
	set("buff/status", HIW"¼f"NOR WHT"§P"HIW"ªÌ"NOR);
	
	::setup_equipment(EQ_MOUNT, HIG"®y"NOR GRN"ÃM"NOR);
}
