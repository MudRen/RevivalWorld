/* This	program	is a part of RW	mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File	  : coarse_bucket.c
 * Author : Clode@RevivalWorld
 * Date	  : 2004-06-05
 * Note	  : 
 * Update :
 *  o 2000-00-00  

 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>

inherit	STANDARD_OBJECT;

void create()
{
	set_idname("coarse bucket", "粗製水桶");

	if( this_object()->set_shadow_ob() ) return;
	
	set("long", "政府大量生產的廉價物品，用來採集清水，品質低落，損壞率相當高。");
	set("endurance", 100);
	set("unit", "個");
	set("value", 100);
	set("mass", 500);
	set("collection_tool", "water");
	set("badsell", 1);
}
