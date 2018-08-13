/* This	program	is a part of RW	mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File	  : description_d.c
 * Author : Clode@RevivalWorld
 * Date	  : 2006-02-08
 * Note	  : ±Ô­z÷כÆF
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <buff.h>

string *buff_list = ({
	BUFF_STR		,	HIY"¤O"NOR YEL"¶q"NOR,
	BUFF_PHY		,	HIY"Åי"NOR YEL"®ז"NOR,
	BUFF_INT		,	HIY"´¼"NOR YEL"°Ó"NOR,
	BUFF_AGI		,	HIY"±Ó"NOR YEL"±¶"NOR,
	BUFF_CHA		,	HIY"¾y"NOR YEL"¤O"NOR,
	BUFF_STAMINA_MAX	,	HIG"Åי¤O"NOR GRN"³Ì¤j­È"NOR,
	BUFF_HEALTH_MAX		,	HIG"¥Í©R"NOR GRN"³Ì¤j­È"NOR,
	BUFF_ENERGY_MAX		,	HIG"÷כ¯«"NOR GRN"³Ì¤j­È"NOR,
	BUFF_STAMINA_REGEN	,	HIC"Åי¤O"NOR CYN"«ל´_³t«×/2s"NOR,
	BUFF_HEALTH_REGEN	,	HIC"¥Í©R"NOR CYN"«ל´_³t«×/2s"NOR,
	BUFF_ENERGY_REGEN	,	HIC"÷כ¯«"NOR CYN"«ל´_³t«×/2s"NOR,
	BUFF_LOADING_MAX	,	HIM"­t­«"NOR MAG"¤W­­/kg"NOR,
	BUFF_FOOD_MAX		,	HIM"­¹×«"NOR MAG"¤W­­"NOR,
	BUFF_DRINK_MAX		,	HIM"¶¼¤פ"NOR MAG"¤W­­"NOR,
	BUFF_SOCIAL_EXP_BONUS	,	HIB"×À·|¸gÅח"NOR BLU"¥[¦¨/%"NOR,
	BUFF_MOVING_STAMINA	,	HIR"²¾°ÊÅי¤O"NOR RED"¯Ó¶O"NOR,
	BUFF_ARMOR_SLASH	,	HIW"´§¬ו"NOR WHT"¨¾¿m"NOR,
	BUFF_ARMOR_GORE		,	HIW"¬ן¨כ"NOR WHT"¨¾¿m"NOR,
	BUFF_ARMOR_EXPLODE	,	HIW"Ãz¬µ"NOR WHT"¨¾¿m"NOR,
	BUFF_ARMOR_INJURY	,	HIW"¤÷¶Ë"NOR WHT"¨¾¿m"NOR,
	BUFF_ARMOR_FIRE		,	HIW"¯P¤ץ"NOR WHT"©ט§Ü"NOR,
	BUFF_ARMOR_ICE		,	HIW"´H¦B"NOR WHT"©ט§Ü"NOR,
	BUFF_ARMOR_POISON	,	HIW"¼@¬r"NOR WHT"©ט§Ü"NOR,
	BUFF_ARMOR_HEART	,	HIW"¤‗ÆF"NOR WHT"©ט§Ü"NOR,
});

int buff_list_size;

string buff_description(object ob, string key, string chinese, int indent)
{
	int buff = query(key, ob);

	if( !buff ) return 0;
		
	if( buff > 0 )
		return sprintf(repeat_string(" ", indent)+NOR YEL"¡D%-15s "NOR CYN"+"HIC"%d\n"NOR, chinese, buff);
	else
		return sprintf(repeat_string(" ", indent)+NOR YEL"¡D%-15s "NOR RED"-"HIR"%d\n"NOR, chinese, -buff);
}

string query_object_buff_description(object ob, int indent)
{
	string description = "";
	
	for(int i=0;i<buff_list_size;i+=2)
		description += buff_description(ob, buff_list[i], buff_list[i+1], indent) || "";
	
	return description;
}

// ×««~±Ô­z
varargs string query_object_description(object ob, int need_quantity)
{
	string mylong = query("long", ob);
	string description = ob->short(need_quantity)+" ¢w\n";

	description += "שÝששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששש‗\n\n";	
	
	if( mylong )
		description += "  "+mylong+"\n";
		
	description += query_object_buff_description(ob, 2);

	description += "\nשדשששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששו\n";

	return description;
}

// ¥Í×«±Ô­z
varargs string query_living_description(object ob, int need_quantity)
{
	string long = query("long", ob);
	string description = ob->short(need_quantity)+" ¢w\n";

	description += "שÝששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששש‗\n\n";
	
	description += "  "+pnoun(3, ob)+"×÷¦~ÄÖ¬° "+query("age", ob)+" ·³¡C\n\n"+(long?long+"\n":"");

	if( ob->is_module_npc() )
	{
		string boss = query("boss", ob);
		object bossob;
		
		if( stringp(boss) )
			bossob = find_player(boss);
		
		if( objectp(bossob) )
			description += "  ¨ה¨­¥ק¬°¨ü¶±­û¤u¡A¶±¥D¬O "+bossob->query_idname()+"\n";
		else if( !boss )
			description += "  ¨ה¨­¥ק¬°¨ü¶±­û¤u¡A¦‎µL¶±¥D¸ך®Æ\n";
		else
			description += "  ¨ה¨­¥ק¬°¨ü¶±­û¤u¡A¶±¥D¬O "+capitalize(boss)+"\n";
	}

	description += "\n";
	
	foreach(object eq in ob->query_equipment_objects())
	{
		description += "  "+HIW"["NOR+eq->query_part_name()+HIW"] "NOR"¸Ë³Æ " + eq->short()+"\n";
		description += query_object_buff_description(eq, 9)+"\n";
	}

	
	description += "\nשדשששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששו\n";
	
	return description;
}

void create()
{
	buff_list_size = sizeof(buff_list);
}

string query_name()
{
	return "±Ô­z¨t²Î(DESCRIPTION_D)";
}
