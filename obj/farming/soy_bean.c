/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : soy_bean.c
 * Author : Tzj@RevivalWorld
 * Date   : 2003-5-4
 * Note   : 大豆
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
        set_idname("soy bean","大豆");
        
        if( this_object()->set_shadow_ob() ) return;
        
        set("unit", "顆");
        set("mass", 7);
        set("value", 8);
        set("badsell", 1);
        
        // 種子資訊
        set("seed_data",
                ([
                        //插秧播種, 灌溉, 收割所耗體力設定
                        "str_cost": ([
                                "sow"           :3, //插秧或播種時需要的體力
                                "irrigate"      :4, //灌溉每升水需要的體力 
                                "reap"          :5 //收割時需要的體力
                                ]),
                        
                        //種子種類
                        "seed":"大豆",
                        
                        //設定插秧或是播種
                        "sow_type":"播種",
                        
                        //收割產品的路徑與數量設定
                        "reap":({ 15, "/obj/farming/soy_bean.c"}),
                        
                        //各個步驟的農作訊息
                        "msg":
                        ([
                                // 插秧播種時的訊息
                                "sow":
                                        "大豆整齊地佈滿整片田地，一片欣欣向榮的感覺。\n" ,
                                
                                // 灌溉時的訊息
                                "irrigate":
                                ({
                                        3,"大豆田上小小的幼苗已經漸漸長大了。\n",
                                        5,"只見大豆田一片綠意盎然，充滿了生氣。\n",
                                        10,"大豆田上的大豆已經漸漸成熟了。\n",
                                        15,"只見一整片綠油油的大豆，已經不用再灌溉了，耐心等一陣子便可以收割。\n",
                                }),
                                
                                // 成熟收割時的訊息
                                "reap":
                                ({
                                        20,
                                        "這片大豆田上的大豆已經全部成熟了，終於可以採收了。\n",
                                        "這片大豆田經過多日來的灌溉，終於成熟收割了。\n共收割了$NUM顆的大豆。\n"
                                }),
                                
                                // 荒廢時的訊息
                                "neglect":
                                ({      
                                        200,
                                        "這片大豆田由於多日來缺乏灌溉，上面的豆芽漸漸枯萎了。\n",
                                        "這片大豆田由於多日來缺乏灌溉，已經完全荒廢了。\n",
                                }),
                                
                                "weather":
                                ([
                                        "RAINY":"連日來的雨量使得一些大豆因泡水而腐爛了。\n",
                                        "SNOWY":"大雪連連嚴重使得大豆苗們陸續地枯萎了。\n",
                                        "WINDY":"狂風吹襲使得部份大豆苗被強風攔腰折斷。\n",
                                ]),
                        ]),
                ])
        );
}


