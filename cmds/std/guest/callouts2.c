/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : callouts2.c
 * Author : Msr@RevivalWorld
 * Date   : 2001-2-6
 * Note   : callouts 
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <feature.h>
#include <ansi.h>
#include <daemon.h>

inherit COMMAND;

string help = @HELP
        硂琩高ヘ玡 mud いΤㄏノ SCHEDULE_D ㄧ计┑㊣兜ヘ
HELP;

private void command(object me, string arg)
{
	mapping info;
        string msg;

	msg  = sprintf("%6s %-20s %-25s %-40s\n", "┑筐", "㊣ㄧ计", "ン", "把计");
	msg += "\n";

	info = SCHEDULE_D->query_events();

	foreach(int key in keys(info)) 
	{
		msg += sprintf("%6d %-20s %-25O %-40s\n", 
		    info[key][2] - info[key][1],
		    info[key][4], 
		    info[key][3],
		    (sizeof(info[key])>5 ? info[key][5]: "礚")              
		);
	}

	if( !sizeof(info) ) 
		msg += "ヘ玡⊿Τ祘㊣い\n";

	msg += "\n";
	msg += NOR WHT" ㄧΑ㊣ "NOR"ヘ玡Τ " + sizeof(info) + " 祘┑筐㊣い\n";

	me->more(msg);
}
