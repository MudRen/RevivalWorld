/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : land_dominium.c
 * Author : Clode@RevivalWorld
 * Date   : 2002-1-21
 * Note   : ¤g¦a©Ò¦³Åvª¬
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <map.h>
#include <ansi.h>
#include <inherit.h>
#include <daemon.h>
#include <message.h>
#include <location.h>
#include <roommodule.h>

inherit STANDARD_OBJECT;

string DECLARATION = @TEXT


	             [1;37;43m ¤g ¦a ©Ò ¦³ Åv ª¬ [m
    §Q¥Î³o±i¤g¦a©Ò¦³Åvª¬¥i¦Û¥Ñ»{»â¤@¶ôµL¤H¾Ö¦³ªº¤g¦a¡A»{»â«á
ªº¤g¦a«K¥Ñ%^GENDER%^©Ò¾Ö¦³¡A»{»â¤g¦a«á%^GENDER%^«K¥i¥H¶}©l§Q¥Î¦¹¤g¦a¨Ó³Ð³y°]
ÄÝ©ó¦Û¤vªº°]´I¡A¿ï¾Ü¤@¶ô¯î¦a«á claim §Y¥i»{»â¡C      [1;31m¢~¢w¢¡[m
                                                     [1;31m¢x®Ö¢x[m
    ¾Ö¦³ªÌ¡G%^ID%^                             [1;31m¢x­ã¢x[m
    ¦³®Ä´Á­­¡G¥Ã»·¦³®Ä                               [1;31m¢¢¢w¢£[m
    

TEXT;

void do_claim(object me, string arg);

mapping actions = 	
([
	"claim"			:(: do_claim :),
]);

void do_claim(object me, string arg)
{
	object env = environment(me);
	mapping data;
	string owner;
	array loc = query_temp("location", me);
	
	if( !(owner = query_temp("owner")) )
		return tell(me, "³o¬O¤@±i¼o±óªº¤g¦a©Ò¦³Åvª¬¡A"+pnoun(2, me)+"µLªk¨Ï¥Î¡C\n", CMDMSG);
		
	if( owner != me->query_id(1) )
		return tell(me, "³o±i¤g¦a©Ò¦³Åvª¬¬O "+capitalize(owner)+" ªº¡A"+pnoun(2, me)+"µLÅv¨Ï¥Î¡C\n", CMDMSG);
	
	if( !arrayp(loc) || !env || !env->is_maproom() ) 
		return tell(me, pnoun(2, me)+"µLªk»{»â³o¶ô¤g¦a¡C\n", CMDMSG);

	if( !CITY_D->is_city_location(loc) )
		return tell(me, pnoun(2, me)+"¥u¯à¦b«°¥«°Ï°ì¤º»{»â¤g¦a¡C\n", CMDMSG);

	if( loc[CITY] != query("city", me) )
		return tell(me, pnoun(2, me)+"¥u¯à¦b¦Û¤vªº«°¥«¸Ì»{»â¤g¦a¡C\n", CMDMSG);

	if( !(CITY_D->query_coor_data(loc, "region") & AGRICULTURE_REGION) )
		return tell(me, pnoun(2, me)+"¥u¯à»{»â¤w¸g¸g¹L¥«¬F©²³W¹ºªº¹A·~°Ï¡C\n", CMDMSG);
	
	if( !mapp(data = CITY_D->query_coor_data(loc)) )
		return tell(me, "¤g¦a¸ê®Æ¿ù»~¡A½Ð³qª¾§Å®v³B²z¡C\n", CMDMSG);
	
	if( nullp(owner = data["owner"]) && nullp(data["ownership"]) )
	{
		if( CITY_D->set_coor_data(loc, "owner", me->query_id(1)) )
		{
			CITY_D->set_coor_icon(loc, BWHT"¡¼"NOR);
			CITY_D->set_coor_data(loc, "claimed", 1);
			tell(me, pnoun(2, me)+"§Q¥Î¤g¦a©Ò¦³Åvª¬»{»â¤F³o¶ô¤g¦a¡C\n", CMDMSG);
			
			// ³]©w©Ð¦a²£¸ê°T
			ESTATE_D->set_land_estate(me->query_id(1), loc);

			delete("flag/land_dominium", me);
			me->save();
			destruct(this_object());
		}
		else if( owner == me->query_id(1) )
			return tell(me, "³o¶ô¦a¤w¸g¬O"+pnoun(2, me)+"ªº¤F¡C\n", CMDMSG);
	}
	else tell(me, "³o¶ô¦a¤w¸g¬O§O¤Hªº¤F¡A"+pnoun(2, me)+"µLªk»{»â¡C\n", CMDMSG);
}

// ¦b½Ö¤â¤W´N¬O½Öªº
void set_owner()
{
	object env = environment(this_object());

	if( env && userp(env) )
	{
		set_idname(env->query_id()+"'s land dominium", env->query_name()+"ªº¤g¦a©Ò¦³Åvª¬");
		set("long", terminal_colour(DECLARATION, (["ID":sprintf("%-12s",ansi_capitalize(env->query_id())), "GENDER":(query("gender", env)=="¨k"?"§A":"©p")])));
		set_temp("owner", env->query_id(1));
	}
}

void create()
{
	set_idname("droped land dominium", "¼o±óªº¤g¦a©Ò¦³Åvª¬");
	set_temp("keep", 2);
	set("long", terminal_colour(DECLARATION, (["ID":sprintf("%-12s","¤w¼o±ó"), "GENDER":"µL"])));
	
	call_out( (: set_owner :), 1 );
	
        if( this_object()->set_shadow_ob() ) return;
	
	set("unit","±i");
	set("mass",10);
	set("value", -1);
	set("flag/no_amount", 1);
        set("flag/no_drop", 1);
        set("flag/no_give", 1);
}
