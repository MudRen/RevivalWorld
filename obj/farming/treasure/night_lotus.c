/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : night_lotus.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-12-19
 * Note   : ©]µÎ²ü
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
	set_idname(HIB"night "NOR BLU"lotus"NOR, HIB"©]µÎ"NOR BLU"²ü"NOR);
	set_temp("status", HIC"µ}"NOR CYN"¦³");

	if( this_object()->set_shadow_ob() ) return;

	set("long", "®Ê¤H¤ý¹Å¡u¬B¿ò°O¡v¤ª¡G¡uº~ÆF«Ò¦è¶é´ë¤¤´Ó½¬¡A¤j¦p»\¡A\nªø¤@¤V¡A¨ä¸­©]µÎ®Ñ¨÷¡A¦W¤ê©]µÎ²ü¡C¡v\n");
	set("unit", "®è");
	set("mass", 0);
	set("value", 6000000);
	set("flag/no_amount", 1);
	set(BUFF_CHA, 30);
	set(BUFF_SOCIAL_EXP_BONUS, 5);
	set("buff/status", HIB"©]µÎ"NOR BLU"²ü"NOR);
	
	::setup_equipment(EQ_BROOCH, HIG"¯Ý"NOR GRN"°w"NOR);
}
