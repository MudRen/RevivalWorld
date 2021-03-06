/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : _command_wiz.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-2-4
 * Note   : 巫師指令系統
 * Update :
 *  o 2002-07-08 Clode 整理 action 程式碼
 *
 -----------------------------------------
 */

#include <daemon.h>

private nosave int commands_authority;

/* 啟動互動性質 */
nomask void enable_interactive()
{
	if( !interactive(this_object()) || !is_daemon(previous_object()) )
		error(sprintf("互動目標啟動權限不足 %O(Call Stack)\n", call_stack(1)));

	enable_wizard();

	/* 向安全系統及指令系統拿取指令權限 */	
	commands_authority = SECURE_D->level_num(this_object()->query_id(1));
	
	/* 向 Channel_D 登錄名單 */
	CHANNEL_D->register_channel(this_object(), query("channels"));
}

int query_commands_authority()
{
	return commands_authority;
}
