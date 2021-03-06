/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : dict.c
 * Author : Msr@RevivalWorld
 * Date   : 2005-07-21
 * Note   : dict 指令
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <feature.h>
#include <daemon.h>
#include <message.h>

inherit COMMAND;

string help = @HELP

HELP;

private void do_command(object me, string arg)
{
	if( !arg ) return tell( me, "請加入想要查詢的位置。\n", CMDMSG);

	find_object("/system/daemons/whois_d.c")->find_ip(me, arg);
	return;
}
