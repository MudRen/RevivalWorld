/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : lily.c
 * Author : Tzj@RevivalWorld
 * Date   : 2003-05-30
 * Note   : ¦Ê¦Xªá
 * Update :
 *  o 2000-05-30
 *
 -----------------------------------------
 */

#include <inherit.h>

inherit STANDARD_OBJECT;

void create()
{
        set_idname("lily","[0m[37;1m¦Ê¦Xªá[0m");
        
        if( this_object()->set_shadow_ob() ) return;
        
        set("long","¦Û¥j¥H¨Ó´N¶H¼x¯Â¼ä»P©M¥­ªº[0m[37;1m¦Ê¦Xªá[0m¡C\n");
        set("unit", "¦·");
        set("mass", 5);
        set("value", 800);
}