/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : terrain.c
 * Author : Clode@RevivalWorld
 * Date   : 2006-09-07
 * Note   : terrain «ü¥O¡C
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <feature.h>
#include <message.h>
#include <map.h>
#include <daemon.h>
#include <terrain.h>

inherit COMMAND;

string help = @HELP
¡@¡@¤â°Ê«Ø¥ß¦a§Îªº«ü¥O

¥i¥H¨Ï¥Îªº°Ñ¼Æ¦p¤U¡G

clear			- ±N¥Ø«e¦ì¸mªº®y¼Ð¸ê®Æ§¹¥þ²M°£¦¨ªÅ¦a
forest			- «Ø¥ß´ËªL¦a§Î([1;32m¡¯[m)
mountain1		- «Ø¥ß¤s¯ß¦a§Î([0;33m¢¨[m)
mountain2		- «Ø¥ß¤s¯ß¦a§Î([0;33m¢©[m)
river1			- «Ø¥ßªe¬y([0;44;1;34m¡ã[m¬y¦V©¹ªF)
river2			- «Ø¥ßªe¬y([0;44;1;34m¡ã[m¬y¦V©¹¦è)
river3			- «Ø¥ßªe¬y([0;44;1;34m¡ã[m¬y¦V©¹«n)
river4			- «Ø¥ßªe¬y([0;44;1;34m¡ã[m¬y¦V©¹¥_)
road			- «Ø¥ß¹D¸ô
road '¦WºÙ'		- «Ø¥ß¹D¸ô»P¹D¸ô¦WºÙ
bridge			- «Ø¥ß¾ô¼Ù([0;41;1;31m¤«[m)
bridge '¦WºÙ'		- «Ø¥ß¾ô¼Ù»P¾ô¼Ù¦WºÙ
wall			- «Ø¥ßÀð¾ÀÄÝ©Ê
farm			- «Ø¥ß¹A¥Ð([0;42;1;32m¡²[m)
pasture			- «Ø¥ßªª³õ([0;43;1;33m¡²[m)
fishfarm		- «Ø¥ß¾i´Þ³õ([0;44;1;34m¡²[m)
light			- «Ø¥ß¸ô¿O([1;33m£F[m)
pool			- «Ø¥ß¤ô¦À([1;36m¡ó[m)
pavilion		- «Ø¥ß²D«F([1;37m¡¸[m)
tree			- «Ø¥ß¤j¾ð([1;32m¢D[m)
grass			- «Ø¥ß¯ó¥Ö([0;32m£s[m)
statue			- «Ø¥ßÀJ¹³([1;35m¢Ç[m)
icon '¹Ï§Î'		- ³æ¯Â¦b¥Ø«e®y¼Ð¤WÃ¸¹Ï(µLÄÝ©Ê¸ê®Æ)
icon -d			- §R°£¥Ø«e®y¼Ð¤Wªº¹Ï§Î
room '©Ð¶¡¦ì¸m'		- ³]©w¥Ø«e®y¼Ð³sµ²¤§©Ð¶¡ÀÉ®×
room -d			- §R°£©Ð¶¡³sµ²³]©w
room broken		- ³]©w¦¨¤@½ñ½k¶îªº©Ð¶¡
name '®y¼Ð¦WºÙ'		- ³]©w¥Ø«e®y¼Ð¹ïÀ³¤§¦WºÙ
name -d			- §R°£¦WºÙ³]©w

HELP;

private void command(object me, string arg)
{
	string arg2;
	array loc = query_temp("location", me);

	if( !is_command() ) return;

	if( !arg )
		return tell(me, help);

	if( !arrayp(loc) || !AREA_D->is_area_location(loc) )
		return tell(me, pnoun(2, me)+"¥u¯à¦b­¥°Ï³]©w¦a§Î¡C\n");
		
	sscanf(arg, "%s %s", arg, arg2);

	switch(arg)
	{
		// ²M°£¥»¦a©Ò¦³¸ê®Æ
		case "clear":
		{
			// ²M°£®y¼Ð¸ê®Æ
			AREA_D->delete_coor_data(loc);
			
			// ²M°£®y¼Ð¹Ï§Î
			AREA_D->delete_coor_icon(loc);
			
			msg("$ME±N³o¶ô¤g¦a¦i¬°¥­¦a¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß´ËªL¦a§Î
		case "forest":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, FOREST);
			AREA_D->set_coor_icon(loc, HIG"¡¯"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F´ËªL¡u"HIG"¡¯"NOR"¡vªº¦a§Î¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¤s¯ß¦a§Î(¥ª)
		case "mountain1":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, MOUNTAIN);
			AREA_D->set_coor_icon(loc, YEL"¢¨"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¤s¯ß¡u"YEL"¢¨"NOR"¡vªº¦a§Î¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¤s¯ß¦a§Î(¥k)
		case "mountain2":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, MOUNTAIN);
			AREA_D->set_coor_icon(loc, YEL"¢©"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¤s¯ß¡u"YEL"¢©"NOR"¡vªº¦a§Î¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ßªe¬y¦a§Î(ªF)
		case "river1":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, RIVER);
			AREA_D->set_coor_icon(loc, BBLU HIB"¡ã"NOR);
			AREA_D->set_coor_data(loc, FLAGS, FLOW_EAST);

			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤Fªe¬y¡u"BBLU HIB"¡ã"NOR"¡v(ªF¦V)ªº¦a§Î¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ßªe¬y¦a§Î(¦è)
		case "river2":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, RIVER);
			AREA_D->set_coor_icon(loc, BBLU HIB"¡ã"NOR);
			AREA_D->set_coor_data(loc, FLAGS, FLOW_WEST);

			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤Fªe¬y¡u"BBLU HIB"¡ã"NOR"¡v(¦è¦V)ªº¦a§Î¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ßªe¬y¦a§Î(«n)
		case "river3":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, RIVER);
			AREA_D->set_coor_icon(loc, BBLU HIB"¡ã"NOR);
			AREA_D->set_coor_data(loc, FLAGS, FLOW_SOUTH);

			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤Fªe¬y¡u"BBLU HIB"¡ã"NOR"¡v(«n¦V)ªº¦a§Î¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ßªe¬y¦a§Î(¥_)
		case "river4":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, RIVER);
			AREA_D->set_coor_icon(loc, BBLU HIB"¡ã"NOR);
			AREA_D->set_coor_data(loc, FLAGS, FLOW_NORTH);

			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤Fªe¬y¡u"BBLU HIB"¡ã"NOR"¡v(¥_¦V)ªº¦a§Î¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¹D¸ô¦a§Î
		case "road":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, ROAD);
			AREA_D->set_coor_icon(loc, "¡@");

			if( !arg2 )
				msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¹D¸ôªº¦a§Î¡C\n", me, 0, 1);
			else
			{
				msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¹D¸ô¨Ã¨ú¦W¬°¡u"+(arg2+NOR)+"¡v¡C\n", me, 0, 1);
				AREA_D->set_coor_data(loc, "short", kill_repeat_ansi(arg2+NOR));				
			}
			break;
		}
		// «Ø¥ß¾ô¼Ù¦a§Î
		case "bridge":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, BRIDGE);
			AREA_D->set_coor_icon(loc, BRED HIR"¤«"NOR);

			if( !arg2 )
				msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¾ô¼Ù¡u"+BRED HIR"¤«"NOR+"¡vªº¦a§Î¡C\n", me, 0, 1);
			else
			{
				msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¾ô¼Ù¡u"+BRED HIR"¤«"NOR+"¡v¨Ã¨ú¦W¬°¡u"+(arg2+NOR)+"¡v¡C\n", me, 0, 1);
				AREA_D->set_coor_data(loc, "short", kill_repeat_ansi(arg2+NOR));				
			}
			break;
		}
		// «Ø¥ßÀð¾ÀÄÝ©Ê
		case "wall":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, WALL);
			AREA_D->set_coor_data(loc, FLAGS, NO_MOVE);

			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤FÀð¾ÀªºÄÝ©Ê¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¹A¥Ð
		case "farm":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, FARM);
			AREA_D->set_coor_icon(loc, HIG BGRN"¡²"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¹A¥Ð¡u"HIG BGRN"¡²"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ßªª³õ
		case "pasture":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, PASTURE);
			AREA_D->set_coor_icon(loc, HIY BYEL"¡²"NOR);

			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤Fªª³õ¡u"HIY BYEL"¡²"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¸ô¿O
		case "light":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, LIGHT);
			AREA_D->set_coor_icon(loc, HIY"£F"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¸ô¿O¡u"HIY"£F"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¤ô¦À
		case "pool":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, POOL);
			AREA_D->set_coor_icon(loc, HIC"¡ó"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¤ô¦À¡u"HIC"¡ó"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß²D«F
		case "pavilion":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, PAVILION);
			AREA_D->set_coor_icon(loc, HIW"¡¸"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F²D«F¡u"HIW"¡¸"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¤j¾ð
		case "tree":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, TREE);
			AREA_D->set_coor_icon(loc, HIG"¢D"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¤j¾ð¡u"HIG"¢D"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¯ó¥Ö
		case "grass":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, GRASS);
			AREA_D->set_coor_icon(loc, NOR GRN"£s"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¯ó¥Ö¡u"NOR GRN"£s"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ßÀJ¹³
		case "statue":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, STATUE);
			AREA_D->set_coor_icon(loc, HIM"¢Ç"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤FÀJ¹³¡u"HIM"¢Ç"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// «Ø¥ß¾i´Þ³õ
		case "fishfarm":
		{
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, TYPE, FISHFARM);
			AREA_D->set_coor_icon(loc, HIB BBLU"¡²"NOR);
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¾i´Þ³õ¡u"HIB BBLU"¡²"NOR"¡v¡C\n", me, 0, 1);
			
			break;
		}	
		// ³æ¯ÂÃ¸¹Ï(¤£³B²zÄÝ©Êªº³¡¥÷)
		case "icon":
		{
			if( !arg2 )
				return tell(me, "½Ð¿é¤J¥¿½Tªº«ü¥O®æ¦¡¡C\n");
	
			if( arg2 == "-d" )
			{
				AREA_D->delete_coor_icon(loc);
				
				msg("$ME§R°£¤F³o¶ô¤g¦aªº¹Ï§Î¡C\n", me, 0, 1);
				
				break;
			}
			AREA_D->set_coor_icon(loc, kill_repeat_ansi(arg2+NOR));
			
			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¡u"+arg2+NOR+"¡vªº¹Ï§Î¡C\n", me, 0, 1);
		
			break;
		}
		// «Ø¥ß¹ïÀ³ªº©Ð¶¡¸ê®Æ
		case "room":
		{
			if( !arg2 )
				return tell(me, "½Ð¿é¤J¥¿½Tªº«ü¥O®æ¦¡¡C\n");

			if( arg2 == "-d" )
			{
				AREA_D->delete_coor_data(loc, ROOM);
				AREA_D->delete_coor_data(loc, SPECIAL_EXIT);
				
				msg("$ME§R°£¤F³o¶ô¤g¦aªº©Ð¶¡³sµ²¸ê®Æ¡C\n", me, 0, 1);
				
				break;
			}
			else if( arg2 == "broken" )
			{
				AREA_D->delete_coor_data(loc);	
				AREA_D->set_coor_data(loc, ROOM, "room");
				msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F¤@¶¡µLªk¶i¤Jªº©Ð¶¡¡C\n", me, 0, 1);
				return;
			}
			AREA_D->delete_coor_data(loc);
			AREA_D->set_coor_data(loc, SPECIAL_EXIT, arg2);
			AREA_D->set_coor_data(loc, ROOM, "room");

			msg("$ME¦b³o¶ô¤g¦a¤W«Ø¥ß¤F»P©Ð¶¡¡u"+arg2+"¡vªº³s±µ¡C\n", me, 0, 1);
		
			break;
		}
		// «Ø¥ß¤g¦aªº¦WºÙ
		case "name":
		{			
			if( !arg2 )
				return tell(me, "½Ð¿é¤J¥¿½Tªº«ü¥O®æ¦¡¡C\n");
			
			if( arg2 == "-d" )
			{
				AREA_D->delete_coor_data(loc, "short");
				
				msg("$ME§R°£¤F³o¶ô¤g¦aªº©R¦W¸ê®Æ¡C\n", me, 0, 1);
				
				break;
			}

			AREA_D->set_coor_data(loc, "short", kill_repeat_ansi(arg2+NOR));
				
			msg("$ME±N³o¶ô¤g¦a©R¦W¬°¡u"+arg2+NOR+"¡v¡C\n", me, 0, 1);
			
			break;
		}
		// ¨ä¥Lª¬ªp
		default:
		{
			tell(me, "½Ð¿é¤J¥¿½Tªº°Ñ¼Æ¡C\n"+help);
			break;
		}
	}
}
