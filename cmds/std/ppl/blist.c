/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : blist.c
 * Author : Clode@RevivalWorld
 * Date   : 2002-09-14
 * Note   : ª±®a«ü¥Oµ{¦¡
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <map.h>
#include <ansi.h>
#include <feature.h>
#include <daemon.h>
#include <message.h>
#include <roommodule.h>

inherit COMMAND;

string generate_building_list();

string help = @HELP
 «Ø¿vª«¦Cªí                                                           [blist]
ùÝùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùß
      ³o­Ó«ü¥O¥i¥HÅý§A¬Ý¨ì¥Ø«eRW¸Ì¶}©ñªº«Ø¿vª«¡A¥H¤Î­n¶}±i³o«Ø¿v©Ò»Ýªº³Ì§C±ø
  ¥ó¡C¦ý§A¶·­n¥ý«Ø³y([1;33mbuild[m) ±K¦XªºÀð¾À¡A¦Ó¥B¥²¶·­n¦³¤@®°¥H¤Wªºªù¡C

      ·í§A¥´¤U[1;33mblist[m ®É¡A·|¥X²{¦p¤Uµe­±¡G
HELP + generate_building_list()+ @HELP

  ¡DºØÃþ¡B¦WºÙ¡G
          ´N¬O³o«Ø¿vªº¥D­n¥\¥Î¡A­Y¬O¬Ý¤£À´­^¤å... ¬Ý¥Lªº¤¤¤å¦WºÙ¤]¤j·§¥i¥H¤F
      ¸Ñ¥L¥D­nªº¯à¤O§a¡H

  ¡D³Ì¤Ö©Ð¶¡­­¨î¡G
          ¤£¥]¬AÀð¾À¦b¤ºªº³Ì¤Ö®æ¼Æ­­¨î¡A¨Ò¦p[1;36m¤p«¬[m°Ó©±¦n¤F... ¥¦ªº³Ì¤Ö©Ð¶¡­­¨î
      ¬O¤@¡A»¡¥Õ¤@ÂI´N¬O§A±o¶R¤E®æ¦a¡C¦b¤K¶ô¦a¤W»\¤W[1mÀð¾À[m¡A³Ñ¤U¤¤¶¡¨º¥Õ¦âªº¤@
      ®æ¡A¤~¥i¥H¶}±i([1;33mopen[m)§Aªº[1;36m¤p«¬[m°Ó©±¡C

          ¥H¹Ï¥ÜÁ|¨Òªº¸Ü¡G
        
        ¡½¡ö¡u³Ì¤Ö©Ð¶¡­­¨î¡v©Òºâªº¼Æ¶q
        ¡¼¡ö¥²¶·­n®³¨Ó»\Àð¾À¥Îªº¦a¡C

          ³Ì¤Ö©Ð¶¡­­¨î = 3

      ¡@¡¼¡¼¡¼¡¼    ¡½ = 4    ¤j©ó³Ì¤Ö©Ð¶¡­­¨î¡C
        ¡¼¡½¡½¡¼
        ¡¼¡½¡½¡¼    ¡¼ = 12   ³æ¯Â®³¨Ó»\±K¦XÀð¾Àªº¦a¡C
      ¡@¡¼¡¼¡¼¡¼

             ·íµM§A°ª¿³ªº¸Ü¤]¥i¥H»\¦¨¡G
                                                        ¡¼¡¼¡¼
        ¡¼¡¼¡¼¡¼    ¡¼¡¼¡¼¡¼    ¡¼¡¼¡¼        ¡¼¡¼¡¼    ¡¼¡½¡¼
        ¡¼¡½¡½¡¼    ¡¼¡½¡½¡¼    ¡¼¡½¡¼¡¼    ¡¼¡¼¡½¡¼    ¡¼¡½¡¼    ¡¼¡¼¡¼¡¼¡¼
        ¡¼¡¼¡½¡¼    ¡¼¡½¡¼¡¼    ¡¼¡½¡½¡¼    ¡¼¡½¡½¡¼    ¡¼¡½¡¼    ¡¼¡½¡½¡½¡¼
          ¡¼¡¼¡¼    ¡¼¡¼¡¼      ¡¼¡¼¡¼¡¼    ¡¼¡¼¡¼¡¼    ¡¼¡¼¡¼    ¡¼¡¼¡¼¡¼¡¼

          ³o¼ËÁöµM»Ý­n¶Rªº¦a¥i¥H¤Ö¤@®æ¡A¦ý¨Æ¹ê¤WÀð¾À¦ûªº®æ¼ÆÁÙ¬O¸ò¥¿¤è§Î¤@¼Ë¡C

  ¡DÄÝ©Ê¡G
          Â²³æªº¨ÓÁ¿´N¬O§A©ÒÄÝªº¨­¥÷¡A¤@¶}©l³£¬O¥Ñ[36m¨p¤H[m¶}©l¡C¦Ó«á¥i¯àª÷¿ú©Î¾Ö
      ¦³ªº©Ð¦a²£¦³¤@©wµ{«×¤§«á¥i¥H¶}¤½¥q¡][1;30m¥ø·~[m¡^¡A©ÎªÌ¬O¸g¥Ñ§ë²¼¿ïÁ|¦Ó¦¨¬°­º
      ªø¡][35m¬F©²[m¡^¡C

          ¦ý¥Ø«eÁÙ¥u¦³[36m¨p¤H[mÄÝ©Ê¡A[1;30m¥ø·~[m©M[35m¬F©²[mÄÝ©Ê¥¿¦b¶}µo¤¤¡A©Ò¥HµLªk¸Ô­z¡C

  ¡D°Ï°ì¡G
          ¦b¤@¶}©lªº®É­Ô¡A¯î¦a¤w¸g³Q¬F©²¹º¤À¦n¤F¦UºØ¥Î¦a¡C©Ò¦³ªº«Ø¿vª«³£¥²¶·
      «Ø¿v¬F©²³W¹º¦nªº¥Î¦a¤§¤W¡A¦³¨Ç¥u¯à³Q«Ø¿v¦b¬Y¨Ç¥Î¦a¤W¡C¦p¡G[1;33m»È¦æ[m¡A¥u¯à¶}
      ±i©ó[1;36;46m°Ó·~°Ï[m¤§¤W¡F[1;36m¤p«¬[m°Ó©±«h¬O¤TºØ¥Î¦a³£¥i¥H¶}±i¡C¨CºØ¥Î¦aªº¦a»ù³£¤£¦P¡A
      ¦b«Ø³y®É¶·­nª`·N¡C

  ¡D¶}±iªá¶O¡G
          ·í§A¤w¸g±N¥H¤W±ø¥ó¤@¤@¹F¦¨¤§®É¡A¦b¶}±i¤§«eªº³Ì«á¤@­Ó­­¨î¡A´N¬O¶}±i
      ªá¶O¡C°²³]§A­n»\ªº¬O¤@¶¡[1;36m¤p«¬[m°Ó©±¡A¤w¦b¥Î¦a¤W¶R¤F¨¬°÷ªº®æ¼Æ¡A¨Ã¤@¤@«Ø³y
      ¥X±K¦XªºÀð¾À¡]¥]¬Aªù¡^¡C§A¨­¤W¥²¶·­n¦³¨¬°÷ªºª÷¿ú¡A¤~¯à[1;33mopen store[m¡A¶}±i
      §Aªº[1;36m¤p«¬[m°Ó©±¡C

[33m    ¬ÛÃö«ü¥O: build, open
[mùãùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùå
                                                            ¤å¥ó«ùÄò§ó·sºûÅ@¤¤
HELP;



string generate_building_list()
{
        array data;
        string msg, buildingtype, buildingregion, *sortid;
        mapping building_table = BUILDING_D->query_building_table();
        string age;
	string *manual_sort = ({
		"cityhall",
		"recycle",
		"labor",
		"trading_post",
		"bank",
		"postoffice",
		"jail",
		"auction",
		"trainstation",
		"airport",
		"space",
		"nuclear",
		"prodigy",

		0,
		"enterprise",
		"stock",
		"university",
		0,
		"store",
		"warehouse",
		"house",
		"fence",
		"cabin",
		"expedition",
		"research",
		"resource",
		0,
		
		"metal",
		"stone",
		"water",
		"wood",
		"fuel",
		
		0,
		"food",
		"drink",
		"clothing",
		"instrument",
		"furniture",
		"hardware",
		"chemical",
		"machinery",
		"electrics",
		"transportation",
		"entertainment",
		"medicine",
		"adventure",
		"shortrange",
		"longrange",
		"armor",
		"heavyarmor",
		"magic",
	});

        sortid = manual_sort | keys(building_table);
       
       	msg = "«Ø¿v¦Cªí¡A¥Ø«e¦@¥i«Ø³y "+sizeof(manual_sort-({0}))+" ºØ«Ø¿v¡G\n";
        msg += NOR WHT"¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n"NOR;
        msg +=        "«Ø¿vºØÃþ       ¦WºÙ   ³Ì¤Ö©Ð¶¡ ÄÝ ³W¹º°Ï Ácºa ¼Ó¼h     ªá¶O/¨C©Ð ­Ó­­ «°­­ ®É¥N ¶}\n";
        msg += NOR WHT"¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n"NOR;
        
        
        foreach( string id in sortid )
        {
        	if( !stringp(id) )
        	{
        		msg += "\n";
        		continue;
        	}

                data = building_table[id];
                
                if( !data || !data[ROOMMODULE_OPENCOST] ) continue;
                
                if( data[ROOMMODULE_BUILDINGTYPE] & GOVERNMENT )
                        buildingtype = MAG"¬F"NOR;
                else if( data[ROOMMODULE_BUILDINGTYPE] & ENTERPRISE )
                        buildingtype = WHT"¥ø"NOR;
                else if( data[ROOMMODULE_BUILDINGTYPE] & INDIVIDUAL )
                        buildingtype = CYN"­Ó"NOR;
		
		switch(data[ROOMMODULE_AGE])
		{
			case 0: age = WHT"¥v«e"NOR; break;
			case 1: age = HIG"¹A"NOR GRN"·~"NOR; break;
			case 2: age = HIY"¤u"NOR YEL"·~"NOR; break;
			case 3:	age = HIC"ª¾"NOR CYN"ÃÑ"NOR; break;
			case 4: age = HIB"¦t"NOR BLU"©z"NOR; break;
			case 5: age = HIR"¥½"NOR RED"¤é"NOR; break;
		}

		if( data[ROOMMODULE_REGION] & AREA_REGION )
			buildingregion = HIW BGRN" ­¥°Ï "NOR;
		else
                	buildingregion = ( data[ROOMMODULE_REGION] & AGRICULTURE_REGION ? HIG BGRN"¹A"NOR : "  ")+
					 ( data[ROOMMODULE_REGION] & INDUSTRY_REGION ? HIY BYEL"¤u"NOR : "  ")+
					 ( data[ROOMMODULE_REGION] & COMMERCE_REGION ? HIC BCYN"°Ó"NOR : "  ");

                msg += sprintf("%-15s%-13s%2d %-3s%-7s%-5d%-4d%14s %|4s %|4s %4s %s\n", 
                        HIY+capitalize(id)+NOR, 
                        data[ROOMMODULE_SHORT],
                        data[ROOMMODULE_ROOMLIMIT],
                        buildingtype,
                        buildingregion,
                        data[ROOMMODULE_FLOURISH],
                        data[ROOMMODULE_MAXFLOOR],
                        HIW+NUMBER_D->number_symbol(data[ROOMMODULE_OPENCOST])+NOR,
                        NOR WHT+(data[ROOMMODULE_MAXLIMIT]||""),
                        NOR WHT+(data[ROOMMODULE_MAXBUILDINGLIMIT]||""),
                       	age,
                        data[ROOMMODULE_TESTING] ? HIR"¢®"NOR : HIG"¡³"NOR,
                        );
        }

        msg += NOR WHT"¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n"NOR;
        
        
        return msg;
}


private void do_command(object me, string arg)
{
	me->more(generate_building_list());
}
