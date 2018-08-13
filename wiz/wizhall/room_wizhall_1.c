/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_wizhall_1.c
 * Author : Clode@RevivalWorld
 * Date   : 2003-08-23
 * Note   : ¼Ð·Ç©Ð¶¡
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>
#include <message.h>
#include <daemon.h>

inherit STANDARD_ROOM;

string help = @HELP
¦b³o­Ó¥­¤ZµL©_ªº©Ð¶¡¤º¨Ã¨S¦³¥ô¦ó¯S®íªº¸ê°T¡C
HELP;

// ¹w³]¥X¤f
#define DEFAULT_CITY_EXIT(city, num)	({ 49, 49, 0, city, num, 0, "49/49/0/"+city+"/"+num+"/0" })

mapping actions;

array south_exit(object ob)
{
	string city = query("city", ob);
	int num = query("section_num", ob);

	if( !sizeof(CITY_D->query_cities()) )
		return 0;

	if( !CITY_D->city_exist(city) )
	{
		string *cities = CITY_D->query_cities() - ({ "wizard" });
		
		if( sizeof(cities) )
		{	
			do
			{
				city = cities[random(sizeof(cities))];
			}
			while( CITY_D->query_city_info(city, "no_occupy") );
		}
		else
			return 0;
	}
	
	if( CITY_D->city_exist(city, num) )
		return CITY_D->query_section_info(city, num, "wizhall") || DEFAULT_CITY_EXIT(city, num);
	else
		return CITY_D->query_section_info(city, 0, "wizhall") || DEFAULT_CITY_EXIT(city, 0);
}

void do_gocity(object me, string arg)
{
	int num;
	string my_city = query("city", me);
	string *lines;

	if( !arg )
		return tell(me, pnoun(2, me)+"·Q­n¥h­þ®y«°¥«¡H½Ð help gocity °Ñ¦Ò«ü¥O¥Îªk¨Ã¨Ï¥Î mayor «ü¥O¬d¸ß©Ò¦³«°¥«¸ê®Æ¡C\n");
	
	arg = remove_ansi(lower_case(arg));
	
	lines = explode(arg, " ");
	if(undefinedp(num = to_int(lines[<1]))) {
		num = 1;
		arg = implode(lines, " ");
	}
	else {
		arg = implode(lines[0..<2], " ");
	}
	

	if( !num ) num = 1;

	if( !CITY_D->city_exist(arg, num-1) )
		return tell(me, "³o­Ó¥@¬É¨Ã¨S¦³³o®y«°¥«¡C\n");

	if( !wizardp(me) )
	{
		if( CITY_D->query_city_info(arg, "no_occupy") )
			return tell(me, "³o®y«°¥«µLªk±q³o¸Ì¶i¤J¡C\n");
			
		if( my_city && my_city != arg )
			return tell(me, pnoun(2, me)+"¬O"+CITY_D->query_city_idname(my_city)+"ªº¥«¥Á¡AµLªk¦A¦Û¥Ñ¶i¤J¨ä¥L«°¥«¡C\n");
		
		if( arg == "wizard" )
			return tell(me, CITY_D->query_city_idname(arg, num)+"¬O§Å®v«°¥«¡A¥u¦³§Å®v¯à°÷¶i¤J¡C\n");
	}
	
	msg("$ME¬ï¹L§Å®v¯«·µ¤¤¤ß¶×»E¯à¶q«á©Ò¶}±Òªº³q¹D¡A«e©¹"+CITY_D->query_city_idname(arg, num-1)+"¡C\n", me, 0, 1);
	me->move(CITY_D->query_section_info(arg, num-1, "wizhall") || DEFAULT_CITY_EXIT(arg, (num-1)));
	msg("$ME¬ï¹L§Å®v¯«·µ³q¹D¨Ó¨ì¤F"+CITY_D->query_city_idname(arg, num-1)+"¡C\n", me, 0, 1);
}

void create()
{
	set("short", HIW"§Å®v"NOR WHT"¯«·µ"NOR);
	set("long",@TEXT
    ¥¨¤jªº§Å®v¯«·µ¨â°¼¦U½Ý¥ßµÛ¥|¤ä¥¨«¬¥Û¬W¡A¤ä¼µµÛ¼Æ¤Q¤Ø°ª«Î³»¡A¯«·µªº¥ª
¥k§ó¬O¼e¹F¼Æ¦Ê¤Ø¡A¦b³o´É¥j¦Ñªº¥Û³y«Ø¿v¤¤¡A¥i¥H·PÄ±¨ì¤@ªÑ[1;37m¯«¸tªº¯à¶q[m¥¿½w½w
ªº¶i¤J¨­Åé¡A¦P®É«o¤]¥i¥H·P¨ü¨ì«Ø¿v²`³B½w½wÅ§¨Óªº[0;1;30m³±§N[m¤§·P¡A¦ü¥G¦b³o®y¯«·µ
¸Ì¡A¦³µÛ³\¦h¤£¬°¤Hª¾ªº¯µ±K¡A¥Ñ¦¹©¹[1;33m South [m¤è¦V¥i¥H¨«¦V¦Û¤v©ÒÄÝªº«°¥«¡A©|
¥¼¤JÄy¥ô¦ó«°¥«ªÌ©¹«n¨««h·|ÀH·N¨«¨ì¥ô¤@­Ó«°¥«¡A©Î¬O§Q¥Î[1;33m gocity [m«ü¥O«e©¹±z
©Ò«ü©wªº«°¥«¡C¨Ï¥Î [1;33mmayor [m«ü¥O¥i¥H¬d¸ß¦U­Ó«°¥«ªº¸Ô²Ó¸ê®Æ¡A§@¬°¤JÄy®Éªº°Ñ
¦Ò¡C
TEXT);

	set("exits", ([
		"east" : "/wiz/wizhall/room_wizhall_2",
		"west" : "/wiz/wizhall/room_wizhall_6",
		"north" : "/wiz/wizhall/room_wizhall_4",
		"south" : (: south_exit($1) :),
		
	]));
	

	set("objects", ([
		"/obj/board/player" : 1,
	]));
	
	set_heart_beat(100);

	actions = ([ "gocity" : (: do_gocity :) ]);
	
	set("help/gocity", 
@HELP
µL°êÄyªÌ¥i¥H¨Ï¥Î¦¹«ü¥O¦Û¥Ñ«e©¹¥ô¤@®y«°¥«¡A«ü¥O¥Îªk¦p¤U
    
    gocity '«°¥«ID'	- «e©¹¬Y«°¥«
    
    ¨Ò¦p
    gocity center	- «e©¹ center «°¥«
    
«°¥« ID ¥i¥Ñ mayor «ü¥O¬d¸ß
HELP,
	);

	::reset_objects();
}

void heart_beat()
{
	int heal;
	string roomshort = query("short");
	
	foreach( object ob in all_inventory(this_object()) )
	{
		if( !ob->is_living() ) return;

		heal = 0;
		
		if( !ob->is_stamina_full() )
		{
			heal = 1;
			ob->earn_stamina(20+random(21));
		}

		if( !ob->is_health_full() )
		{
			heal = 1;
			ob->earn_health(20+random(21));
		}

		if( !ob->is_energy_full() )
		{
			heal = 1;
			ob->earn_energy(20+random(21));
		}
		
		if( heal )
			msg(roomshort+"¸Ì¯«¸tªº¯à¶q¥¿½w½w¦aª`¤JµÛ$MEªº¨­Åé¡C\n"NOR, ob, 0, 1);
	}
}

void init(object ob)
{
	if( !ob->is_living() ) return;

	if( query("total_online_time", ob) < 24*60*60 )
	{
		string msg = HIY"\n·s¤â´£¥Ü¢w¢w¢w¢w¢w¢w\n"
			NOR YEL"Åwªï"+pnoun(2, ob)+"¶i¤J­«¥Íªº¥@¬É½u¤W Mud ¹CÀ¸¡C\n"
			"·s¤â½Ð¥ý¸Ô¥[¾\Åª http://www.revivalworld.org/rw/documents/newbie ¤§©xºô±Ð¾Ç¤å¥ó\n"
			"¬Ý§¹±Ð¾Ç¤å¥ó«á­Y¦³¥ô¦ó¨ä¥L°ÝÃDÅwªï§Q¥Î¡uchat xxx¡v²á¤Ñ«ü¥O¦V½u¤W¨ä¥Lª±®a¸ß°Ý\n"
			"§Y®É¦a¹Ï½Ð°Ñ¦Ò http://www.revivalworld.org/rw/online\n"
			HIY"¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n\n"NOR;
			
		tell(ob, msg);
	}
}

