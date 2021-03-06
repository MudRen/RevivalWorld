/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : promote.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-3-1
 * Note   : promote 指令
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <feature.h>
#include <daemon.h>
#include <message.h>
#include <secure.h>

inherit COMMAND;

string help = @HELP
	標準 promote 指令。
HELP;

private void command(object me, string arg)
{
	int level_num, my_level_num, no_online;
	object user;
	string id, level;

	if( !arg || !is_command() ) return;

	if( !sscanf(arg, "%s %s", id, level) )
		return tell(me, "指令格式: promote 使用者 等級。\n");
	
	id = lower_case(id);
	
	if( !objectp(user = find_player(id)) )
	{
		if( !objectp(user = load_user(id)) )
			return tell(me, "目前沒有 "+id+" 這位使用者。\n");
		else
			no_online = 1;
	}

	my_level_num = SECURE_D->level_num(me->query_id(1));
	level_num = SECURE_D->level_name_to_level_num(level);

	if( !level_num )
		return tell(me, "沒有 "+level+" 這個等級。\n");

	if( my_level_num < level_num || my_level_num < SECURE_D->level_num(id) )
		return tell(me, pnoun(2, me)+"的等級不足，無法將等級提升至 "+level+"。\n");

	if( SECURE_D->change_wizard_level(id, level) )
	{
		string msg = me->query_idname()+"將 "HIY+user->query_idname()+" 使用者等級改為 "+HIY+level+NOR"。\n";
		
		CHANNEL_D->channel_broadcast("sys", msg);
		log_file("command/promote",msg);
		
		set("channels",CHANNEL_D->query_default_channel(id, user), user);
		
		if( SECURE_D->level_num(id) != PLAYER )
			tell(user, "請 Quit 離開遊戲後自 port 4001 重新登錄，才能享有巫師權利。\n");
		
		user->save();
		
		if( no_online )
			destruct(user);
	}
	else
		tell(me, "等級調整失敗。\n");
}	
