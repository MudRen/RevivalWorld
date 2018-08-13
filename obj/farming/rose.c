/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : rose.c
 * Author : Tzj@RevivalWorld
 * Date   : 2003-5-22
 * Note   : ª´ºÀ
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
        set_idname("rose","[0m[31;1mª´ºÀ[0m");
        
        if( this_object()->set_shadow_ob() ) return;
        
        set("long","¦Û¥j¥H¨Ó¶H¼x·R±¡ªº[0m[31;1mª´ºÀ[0m¡A®³¨Ó°e·R¤H¥i¦¬·N·Q¤£¨ìªº®ÄªG¡C\n");
        set("unit", "¦·");
        set("mass", 5);
        set("value", 500);
}