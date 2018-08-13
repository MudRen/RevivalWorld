/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : pack_animal.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : 工脋
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
	set_idname("pack animal", HIY"工"NOR YEL"脋"NOR);
	set_temp("status", HIC"祡"NOR CYN"Τ");

	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "でノㄓ更珇笆\n");
	set("unit", "で");
	set("mass", 0);
	set("value", 3000000);
	set("flag/no_amount", 1);
	set(BUFF_STR, 20);
	set("buff/status", HIY"工"NOR YEL"脋"NOR);

	::setup_equipment(EQ_MOUNT, HIG"畒"NOR GRN"肕"NOR);
}
