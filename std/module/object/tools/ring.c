/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : rod.c
 * Author : Kyyung@RevivalWorld
 * Date   : 2003-05-17
 * Note   : 魚竿
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <feature.h>
#include <material.h>

inherit EQUIP;

inherit OBJECT_ACTION_MOD;

// 設定物件動作

nosave mapping action_info =
([
        "help"  : "尚未建構說明。",
]);


// 設定物件資料
nosave array object_info = ({
        
        // 基本 name
        "戒指"
        
        // 基本 id
        ,"ring"

        // 分類,定義繼承檔
        ,"ring"

        // 基本材料需求
        ,([ GOLD:2 ])
        
        // 製造此產品所需要的科技值
        ,10000

        // 基本製造速度(每位員工/每遊戲時間一分鐘)
        ,20

        // 基本價值
        ,"1500"

        // 科技樹資料
        ,0

        // 物件參數
        ,([ "equip":"finger", "applyattr/phy":1 , "addloading":1000 ])
});
