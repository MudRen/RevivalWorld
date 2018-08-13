/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : simul_efun.c
 * Author : Clode@RevivalWorld
 * Date   : 2000-12-28
 * Note   : 模擬外部函式物件, 以下 Include 順序有重要關聯, 隨意變動可能造成 Mud 無法啟動
 * Update :
 *  o 2000-00-00  

 -----------------------------------------
 */

#include <daemon.h>

#include "simul_efun/person.c"

#include "simul_efun/log.c"

#include "simul_efun/path.c"

#include "simul_efun/string.c"

#include "simul_efun/parse.c"

#include "simul_efun/file.c"

#include "simul_efun/object.c"

#include "simul_efun/zone.c"

#include "simul_efun/city.c"

#include "simul_efun/area.c"

#include "simul_efun/message.c"

#include "simul_efun/title_screen.c"

#include "simul_efun/socket.c"

#include "simul_efun/boolean.c"

#include "simul_efun/location.c"

#include "simul_efun/array.c"

#include "simul_efun/bit.c"

#include "simul_efun/math.c"

#include "simul_efun/secure.c"

#include "simul_efun/int.c"

#include "simul_efun/process.c"

private void create()
{
	printf("Simul Efun Object(/system/kernel/simul_efun.c) 載入成功\n");
}

string iconv_string(string from, string to, string text)
{
	printf("此 Efun 被懷疑是 Crasher 目前被封鎖中, 請勿任意使用\n");
	return 0;
}