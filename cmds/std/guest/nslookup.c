/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : nslookup.c
 * Author : Clode@RevivalWorld
 * Date   : 2003-03-03
 * Note   : nslookup 指令
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <feature.h>
#include <message.h>

inherit COMMAND;

private nosave mapping caller = allocate_mapping(0);

string help = @HELP
	標準 nslookup 指令。
HELP;

private void command(object me, string arg)
{
       	if( !is_command() ) return;
       	
	if( !arg )
		return tell(me, "請輸入欲查詢的網域名稱或 IP。\n", CMDMSG);
	
	tell(me, "查詢中，請稍後...\n", CMDMSG);
	
	caller[resolve(arg, "callback")] = me;
}

void callback(string address, string resolved, int key)
{
	string msg="\n\n查詢結果:\n";
	
	msg += "Name    : "+(address||"不存在網域名稱")+"\n";
	msg += "Address : "+(resolved||"不存在IP")+"\n\n";

	if( objectp(caller[key]) )
	{
		tell(caller[key], msg, CMDMSG);
		caller[key]->finish_input();
	}
	
	map_delete(caller, key);
}