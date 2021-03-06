/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : buddha_wood.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-12-19
 * Note   : 御神木
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
	set_idname(HIY"buddha "NOR YEL"wood"NOR, HIY"御"NOR YEL"神"NOR HIY"木"NOR);
	set_temp("status", HIC"稀"NOR CYN"有");

	if( this_object()->set_shadow_ob() ) return;

	set("long", "一個巨大神木上的碎片。」\n");
	set("unit", "株");
	set("mass", 0);
	set("value", 100000000);
	set("flag/no_amount", 1);
	set(BUFF_CHA, 65);
	set(BUFF_SOCIAL_EXP_BONUS, 50);
	set("buff/status", HIY"參"NOR YEL"神"NOR HIY"木"NOR);
	
	::setup_equipment(EQ_BROOCH, HIG"胸"NOR GRN"針"NOR);
}
