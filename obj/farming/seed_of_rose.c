/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : seed_of_rose.c
 * Author : Tzj@RevivalWorld
 * Date   : 2003-5-22
 * Note   : ª´ºÀºØ¤l
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
        set_idname("seed of rose",HIR"ª´ºÀ"NOR+RED"ºØ¤l"NOR);
        
        if( this_object()->set_shadow_ob() ) return;
        
        set("unit", "²É");
        set("mass", 2);
        set("value", 100);
        set("long","»Ý­n¤p¤ß¨þÅ@¤~¯àªø¦¨[0m[31;1mª´ºÀ[0mªá¦·¡C\n");
        set("badsell", 1);
 
        // ºØ¤l¸ê°T
        set("seed_data",
                ([
                        //´¡¯±¼½ºØ, Äéµ@, ¦¬³Î©Ò¯ÓÅé¤O³]©w
                        "str_cost": ([
                                "sow"           :3, //´¡¯±©Î¼½ºØ®É»Ý­nªºÅé¤O
                                "irrigate"      :7, //Äéµ@¨C¤É¤ô»Ý­nªºÅé¤O 
                                "reap"          :10 //¦¬³Î®É»Ý­nªºÅé¤O
                                ]),
                        
                        //ºØ¤lºØÃþ
                        "seed":"ª´ºÀºØ¤l",
                        
                        //³]©w´¡¯±©Î¬O¼½ºØ
                        "sow_type":"¼½ºØ",
                        
                        //¦¬³Î²£«~ªº¸ô®|»P¼Æ¶q³]©w
                        "reap":({ 5, "/obj/farming/rose.c"}),
                        
                        //¦U­Ó¨BÆJªº¹A§@°T®§
                        "msg":
                        ([
                                // ´¡¯±¼½ºØ®Éªº°T®§
                                "sow":
                                        "ª´ºÀºØ¤l´²¼½¦b¥Ð¸Ì¡AÁÙ¬Ý¤£¥X¥®Ðt¡C\n" ,
                                
                                // Äéµ@®Éªº°T®§
                                "irrigate":
                                ({
                                        2,"ª´ºÀºØ¤lµÞ¥X¤@®Ú®Ú¹àªÞº¥º¥¥Íªø¡C\n",
                                        3,"ª´ºÀ¥®ÐtºCºC¥Íªø¥X¦³¨ëÃÃ½¯¡A¤W­±ªººñ¸­¤@¤@µÎ®i¶}¨Ó¡C\n",
                                        5,"ª´ºÀ¥Ð«_¥X¤F³\¦hª´ºÀªá­c¡A¦A¹L¤£¤[´N·|¶}ªá¤F¡C\n",
                                        7,"¥u¨£¤@¦·¤S¤@¦·ºì¶}ªºÂA¬õ¦âª´ºÀ¦bºñ¸­ªº¬MÅ¨¤§¤U©úÆA°Ê¤H¡A¦Aµ¥¤@¤U¤l´N¥i¥H±Ä¦¬¤F¡C\n",
                                }),
                                
                                // ¦¨¼ô¦¬³Î®Éªº°T®§
                                "reap":
                                ({
                                        5,
                                        "ª´ºÀ¥Ð¤Wªºª´ºÀªá¤w¥þ³¡ºì©ñ¡A¤w¸g¥i¥H±Ä¦¬¤F¡C\n",
                                        "³o¤ùª´ºÀ¥Ð¦b²Ó¤ß¨þÅ@¤§¤U¡Aºì©ñ¤F³\¦hª´ºÀ¡C\n¦@±Ä¦¬¤F$NUM¦·ªºª´ºÀ¡C\n"
                                }),
                                
                                // ¯î¼o®Éªº°T®§
                                "neglect":
                                ({      
                                        50,
                                        "³o¤ùª´ºÀ¥Ð¦]¬°ªø¤[¨S¦³¼å¤ô¡Aºñ¸­¤@¤ù¤ù¬\¶À­ä¹s¡C\n",
                                        "³o¤ùª´ºÀ¥Ð¦]¤[¥¼µ½¥[¨þÅ@¡A¤w¸g¥þ³¡¯î¼o¤F¡C\n",
                                }),
                                
                                "weather":
                                ([
                                        "RAINY":"¤j«B¨Ï±oª´ºÀ¥Ðªº®Úªw¤ô»GÄê¤F¡C\n",
                                        "SNOWY":"¤j³·¨Ïª´ºÀ¥Ð¾D¨ü¨ìÄY­«ªº¦B®`¡C\n",
                                        "WINDY":"¨g­·¨Ïªº¤@³¡¤Àªºª´ºÀ¥®Ðt³QÄd¸y§jÂ_¡C\n",
                                ]),
                        ]),
                ])
        );
}


