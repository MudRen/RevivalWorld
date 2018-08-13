/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_5.c
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
µÛªº[1;33m¶À¥É¥Û¬W[mª½ª½´¡¦b¦a¤W¡A§¹¬üµL·vªº¥É¥ÛÅý¤H¬Ý±o¥ØÀü¤f§b¡C
TEXT);

	set("exits", ([
		"south" 	: "/quest/yin_ling_yu/room_6",
		"north" 	: "/quest/yin_ling_yu/room_4",
	]));
	
	::reset_objects();
}

void do_push(object me, string arg)
{
	if( arg != "¥ª" && arg != "¥k" )
		return tell(me, pnoun(2, me)+"·Q­n§â¥Û¬W©¹¥ª¥k­þ­Ó¤è¦V±À(¥ª, ¥k)¡H\n");
		
	if( !query_temp("/quest/yin_ling_yu/stone/green", me) )
		return tell(me, pnoun(2, me)+"¨Ï¥X¦Y¥¤ªº¤O¶q¤]±À¤£°Ê³o­Ó¥Û¬W¡C\n");

	if( lower_case(arg) == "¥ª" )
	{
		set_temp("/quest/yin_ling_yu/stone/yellow", 1, me);
		msg("$ME¥Î¤O±N¥Û¬W©¹¥ªÃä±À¡A¥u·PÄ±¨ì¦aªO¤U¦ü¥G¦³ªF¦è¦b¾_°Ê¡C\n", me, 0, 1);
		return;
	}
	else if( lower_case(arg) == "¥k" )
	{
		set_temp("/quest/yin_ling_yu/stone/yellow", 2, me);
		msg("$ME¥Î¤O±N¥Û¬W©¹¥kÃä±À¡A¥u·PÄ±¨ì¦aªO¤U¦ü¥G¦³ªF¦è¦b¾_°Ê...¡C\n", me, 0, 1);
		return;
	}
}

mapping actions = 
([
	"push" : (: do_push :),
]);