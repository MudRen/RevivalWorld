/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : standard_maproom.c
 * Author : Clode@RevivalWorld
 * Date   : 2002-09-24
 * Note   : 標準地圖物件繼承檔
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <feature.h>

inherit DATABASE;

nomask int is_maproom()
{
        return 1;
}
