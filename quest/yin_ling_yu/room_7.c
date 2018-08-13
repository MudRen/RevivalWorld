/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_7.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-12-19
 * Note   : ¼Ð·Ç©Ð¶¡
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>
#include <quest.h>

inherit STANDARD_ROOM;

string help = @HELP
¦b³o­Ó¥­¤ZµL©_ªº©Ð¶¡¤º¨Ã¨S¦³¥ô¦ó¯S®íªº¸ê°T¡C
HELP;

void create()
{
	set("short", HIW"Áô±K"NOR WHT"¤s¬}"NOR);
	set("long",@TEXT
    ³o¸Ì¬O¤@­Ó·¥¬°Áô±Kªº¤s¬}¡A¸Ì­±¤@¤ùº£¶Â¡A©¹¤âÃäºN¥h³£¬O§N¦B¦B¥B¼éÀãªº
¥ÛÂz¡AÀY³»¤W¤]¤£®É¦aºw¤U¤ô¨Ó¡A¤£¹L©¹¸ÌÀY¤@¬Ý¡A¦ü¥G®æ§½ÁÙ®¼¤è¥¿ªº¡A¦a¤W¤]
¥i¥H°¸º¸¨£¨ì´X®è¥¿¦b¥Íªøªº³¥¤s¤H°Ñ¡A¦Ó¦b³o­Ó¤è¥¿ªº¤s¬}¥¿¤¤¥¡«h¦³¤@­Ó«ÜÅã
µÛªº[1;34mÂÅ¥É¥Û¬W[mª½ª½´¡¦b¦a¤W¡A§¹¬üµL·vªº¥É¥ÛÅý¤H¬Ý±o¥ØÀü¤f§b¡C
TEXT);
	
	set("exits", ([
		"north" 	: "/quest/yin_ling_yu/room_6",
	]));

	::reset_objects();
}

void do_push(object me, string arg)
{
	mapping stone;

	if( arg != "¥ª" && arg != "¥k" )
		return tell(me, pnoun(2, me)+"·Q­n§â¥Û¬W©¹¥ª¥k­þ­Ó¤è¦V±À(¥ª, ¥k)¡H\n");
		
	if( !query_temp("/quest/yin_ling_yu/stone/red", me) )
		return tell(me, pnoun(2, me)+"¨Ï¥X¦Y¥¤ªº¤O¶q¤]±À¤£°Ê³o­Ó¥Û¬W¡C\n");

	if( lower_case(arg) == "¥ª" )
	{
		set_temp("/quest/yin_ling_yu/stone/blue", 1, me);
		msg("$ME¥Î¤O±N¥Û¬W©¹¥ªÃä±À¡A¥u·PÄ±¨ì¦aªO¤U¦ü¥G¦³ªF¦è¦b¾_°Ê¡C\n", me, 0, 1);
	}
	else if( lower_case(arg) == "¥k" )
	{
		set_temp("/quest/yin_ling_yu/stone/blue", 2, me);
		msg("$ME¥Î¤O±N¥Û¬W©¹¥kÃä±À¡A¥u·PÄ±¨ì¦aªO¤U¦ü¥G¦³ªF¦è¦b¾_°Ê...¡C\n", me, 0, 1);
	}

	stone = query_temp("/quest/yin_ling_yu/stone", me);
	
	if( stone["green"] == 1 && stone["yellow"] == 2 && stone["red"] == 2 && stone["blue"] == 2 )
	{
		msg("$ME¸}©³¤Uªº¥ÛªO¬ðµMÃP¶}¡A$ME´N³o¼Ë±¼¤F¤U¥h¡A¥ÛªOÀH§Y¤SÃö¤F°_¨Ó¡C\n", me, 0, 1);
		me->move("/quest/yin_ling_yu/room_8");
		me->set_quest_note(QUEST_YIN_LING_YU_2, QUEST_YIN_LING_YU_2_NAME, "¯}¸Ñ¤F¤s¬}¤¤ªº¾÷Ãö¡A¶i¤J¨ì¥Û¬}©³³¡¡C");
		me->set_quest_step(QUEST_YIN_LING_YU_2, 4);
		delete_temp("/quest/yin_ling_yu/stone", me);
	}
	else
	{
		delete_temp("/quest/yin_ling_yu/stone", me);
		msg("$MEªº²´«e¬ðµM¤@°}¼Ò½k¡A®ø¥¢¤F¡C\n", me, 0, 1);
		me->move(({ 81, 71, 0, "lightforest", 8, 0, "81/71/0/lightforest/8/0" }));
		msg("$MEªº²´«e¬ðµM¤@°}¼Ò½k¡A²´·ú¤@«G´N¶]¨ì¤F³o¸Ì¡C\n", me, 0, 1);
		
		if( !random(5) )
			me->faint();
	}
}

mapping actions = 
([
	"push" : (: do_push :),
]);