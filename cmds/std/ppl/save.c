/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : save.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-2-6
 * Note   : save 指令
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <feature.h>
#include <message.h>

inherit COMMAND;

string help = @HELP
存檔指令

系統定時會幫使用者存檔，為了避免系統發生意外時無法即時存檔
這個指令可以讓使用者自行存檔

每位玩家應保持良好的習慣隨時存檔，以避免資料意外流失

相關指令:
HELP;

private void do_command(object me, string arg)
{
	int time = time() - query_temp("last_save_time", me);
	
	if( time < 60 )
		return tell(me, "你 "+time+" 秒前才儲存過。\n", CMDMSG);
	
	set_temp("last_save_time", time(), me);
	
	if( me->save() )
		tell(me, me->query_idname()+"資料儲存完畢。\n", CMDMSG);
	else
		tell(me, me->query_idname()+"資料儲存失敗，請通知巫師處理。\n", CMDMSG);
}