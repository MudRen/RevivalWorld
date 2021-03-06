/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : clam.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : 蚌殼
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>
#include <nature.h>
#include <map.h>

inherit STANDARD_OBJECT;

void create()
{
        set_idname("clam","蚌殼");
        
        if( this_object()->set_shadow_ob() ) return;
        
        set("long", "用來培養珍珠的蚌殼。\n");
        set("unit", "個");
        set("mass", 50);
        set("value", 10000);
        set("badsell", 1);

	// 種子資訊
	set("growth",
	([
		//種類
		"type":		FISHFARM,

		//名稱
		"idname":	this_object()->query_idname(),
		
		//開始生產時的訊息
		"start_msg":"蚌殼整齊地排列在水底，水流輕輕地流過。\n" ,
			
	       	//每單位需要的原料種類與數量
	       	"material":
	       	([
	       		"/obj/materials/water":20,
	       		"/obj/materials/wood":20,
	       	]),
			
	       	//產品的數量設定與產品路徑
	       	"harvest":
	       	([
	       		"/obj/fishfarm/product/pearl":3,
	       	]),

		//生成時的訊息
		"harvest_msg":"$ME歡喜地取出蚌殼內的珍珠。\n",

		//種植此類產品所需要的技能與其等級
		"skill":
		([
			"fishfarm":80,
		]),

		//成長時的訊息
		"growing":
		([
			5:	"蚌殼在水底輕輕地吐砂，一些小魚小蝦在附近游動。\n",
			100:	"蚌殼靜靜地在水底一動也不動。\n",
			300:	"蚌殼突然一口氣吐了一堆砂出來，接著兩片貝殼又漸漸合了起來。\n",
			600:	"蚌殼在水底輕輕地吐砂，一些小魚小蝦在附近游動。\n",
			1200:	"蚌殼愈長愈大，從旁可以隱隱看到白色的珍珠在中閃耀。\n",
			1800:	"蚌殼的大小已經大到足以進行收成了。\n",
		]),
	
		// 天氣影響敘述
		"weather":
		([
			SNOWY:	"大雪連連嚴重使得蚌殼們陸續的凍死。\n",
			SHOWER:	"連日來的雨量使得部份的蚌殼們被大水沖走。\n",
			TYPHOON:"颱風來襲使得部份的蚌殼們被大水沖走。\n",
			FOEHN:	"焚風的吹襲讓部份的蚌殼們因水溫過高而死。\n",
		]),
	]));
}
