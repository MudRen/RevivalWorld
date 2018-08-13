/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : seed_of_lily.c
 * Author : Tzj@RevivalWorld
 * Date   : 2003-05-30
 * Note   : ¦Ê¦XºØ¤l
 * Update :
 *  o 2000-05-30
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
        set_idname("seed of lily",HIW"¦Ê¦X"NOR"ºØ¤l");
        
        if( this_object()->set_shadow_ob() ) return;
        
        set("unit", "²É");
        set("mass", 2);
        set("value", 200);
        set("long","»Ý­n¤p¤ß¨þÅ@¤~¯àªø¦¨[0m[37;1m¦Ê¦X[0mªá¦·¡C\n");
        set("badsell", 1);

        // ºØ¤l¸ê°T
        set("seed_data",
                ([
                        //´¡¯±¼½ºØ, Äéµ@, ¦¬³Î©Ò¯ÓÅé¤O³]©w
                        "str_cost": ([
                                "sow"           :5, //´¡¯±©Î¼½ºØ®É»Ý­nªºÅé¤O
                                "irrigate"      :9, //Äéµ@¨C¤É¤ô»Ý­nªºÅé¤O 
                                "reap"          :8 //¦¬³Î®É»Ý­nªºÅé¤O
                                ]),
                        
                        //ºØ¤lºØÃþ
                        "seed":"¦Ê¦XºØ¤l",
                        
                        //³]©w´¡¯±©Î¬O¼½ºØ
                        "sow_type":"¼½ºØ",
                        
                        //¦¬³Î²£«~ªº¸ô®|»P¼Æ¶q³]©w
                        "reap":({ 3, "/obj/farming/lily.c"}),
                        
                        //¦U­Ó¨BÆJªº¹A§@°T®§
                        "msg":
                        ([
                                // ´¡¯±¼½ºØ®Éªº°T®§
                                "sow":
                                        "¦Ê¦XºØ¤l´²¼½¦b¥Ð¸Ì¡AÁÙ¬Ý¤£¥X¥®Ðt¡C\n" ,
                                
                                // Äéµ@®Éªº°T®§
                                "irrigate":
                                ({
                                        2,"¦Ê¦XºØ¤lµÞ¥X¤@®Ú®Ú¹àªÞº¥º¥¥Íªø¡C\n",
                                        3,"¦Ê¦X¥®ÐtºCºC¥Íªø¡A¤W­±ªººñ¸­¤@¤@µÎ®i¶}¨Ó¡C\n",
                                        6,"¦Ê¦Xªá¥Ð«_¥X¤F³\¦h¦Ê¦Xªá­c¡A¦A¹L¤£¤[´N·|¶}ªá¤F¡C\n",
                                        7,"ºì¶}ªº¥Õ¦â¦Ê¦Xªá¦bºñ¸­ªº¬MÅ¨¤§¤U¸t¼äµL¤ñ¡A¦Aµ¥¤@¤U¤l´N¥i¥H±Ä¦¬¤F¡C\n",
                                }),
                                
                                // ¦¨¼ô¦¬³Î®Éªº°T®§
                                "reap":
                                ({
                                        10,
                                        "¦Ê¦Xªá¥Ð¤Wªº¦Ê¦X¤w¥þ³¡ºì©ñ¡A¤w¸g¥i¥H±Ä¦¬¤F¡C\n",
                                        "³o¤ù¦Ê¦Xªá¥Ð¦b²Ó¤ß¨þÅ@¤§¤U¡Aºì©ñ¤F³\¦h¦Ê¦X¡C\n¦@±Ä¦¬¤F$NUM¦·ªº¦Ê¦Xªá¡C\n"
                                }),
                                
                                // ¯î¼o®Éªº°T®§
                                "neglect":
                                ({      
                                        25,
                                        "³o¤ù¦Ê¦Xªá¥Ð¦]¬°ªø¤[¨S¦³¼å¤ô¡Aºñ¸­¤@¤ù¤ù¬\¶À­ä¹s¡C\n",
                                        "³o¤ù¦Ê¦Xªá¥Ð¦]¤[¥¼µ½¥[¨þÅ@¡A¤w¸g¥þ³¡¯î¼o¤F¡C\n",
                                }),
                                
                                "weather":
                                ([
                                        "RAINY":"¤j«B¨Ï±o³\¦h¦Ê¦Xªº®Úªw¤ô»GÄê¤F¡C\n",
                                        "SNOWY":"¤j³·¨Ï¦Ê¦Xªá¥Ð¾D¨ü¨ìÄY­«ªº¦B®`¡C\n",
                                        "WINDY":"¨g­·¨Ï¤@³¡¤Àªº¦Ê¦X¥®Ðt³QÄd¸y§jÂ_¡C\n",
                                ]),
                        ]),
                ])
        );
}
