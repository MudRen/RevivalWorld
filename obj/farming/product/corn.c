/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : corn.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-09-09
 * Note   : ¥É¦Ì
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
	set_idname("corn","¥É¦Ì");
	
	if( this_object()->set_shadow_ob() ) return;
	
	set("long","¨ã¦³­»¿@¤f¨ýªº¤­½\­¹«~¡A¤SºÙ¬°µf³Á¡B¥É¸¾¶Á¡B±s³Á¡C\n");
	set("unit", "³U");
	set("mass", 800);
	set("value", 400);
}
