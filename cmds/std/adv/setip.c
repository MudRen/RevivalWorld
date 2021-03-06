/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : setip.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-04-12
 * Note   : setip 指令
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <ip.h>
#include <daemon.h>
#include <feature.h>
#include <message.h>

inherit COMMAND;

string help = @HELP
setip 					- 列出目前 IP 設定資料
setip ban 210.59.67.253			- 設定此 IP 永久禁止登入
setip ban 210.59.*.*			- 設定此 IP 永久禁止登入
setip ban 210.59.*.* in 50		- 設定 50 小時內禁止此 IP 登入
setip ban 210.59.*.* in 50 with '註解'	- 設定 50 小時內禁止此 IP 登入同時註解資料
setip -d 210.59.67.253			- 取消該 IP 所有設定

IP 表示式可用 regexp 的正規語法

setip 選項如下
 ban 		- 完全禁止 IP 登入
 cmdlimit	- 限制由此 IP 登入之玩家的指令執行速度(懲罰性限制)
 ok		- 標明此 IP 應屬合法 IP, 不需要設定限制(必免被重覆限制)
HELP;


int valid_ip(string ip)
{
	string *elem = allocate(4);
	
	if( sscanf(ip, "%s.%s.%s.%s", elem[0], elem[1], elem[2], elem[3]) != 4 )
		return 0;

	// 第一個 * 會造成 regexp 判斷錯誤
	if( elem[0] == "*" ) return 0;

	foreach(string e in elem)
	if( e != "*" && to_int(e) < 0 && to_int(e) > 255 )
		return 0;
		
	return 1;
}

private void command(object me, string arg)
{
	int releasetime;
	string option, ip, note;

	if( !is_command() ) return;
	
	if( !arg )
	{
		string msg;
		mapping ipdata = IP_D->query_ipdata();
		mapping data;
		msg  = HIW"IP                設定         設定時間         釋放時間         註解\n"NOR;
		msg += WHT"─────────────────────────────────────\n"NOR;
		
		if( sizeof(ipdata) )
		foreach(ip in sort_array(keys(ipdata), 1))
		{
			data = ipdata[ip];
			switch(data["status"])
			{
				case BAN: 		option = HIR"禁止登入"NOR; break;
				case CMDLIMIT:		option = HIY"指令速度限制"NOR; break;
				case OK:		option = HIG"合法"NOR;	break;
			}
			msg += sprintf("%-18s%-13s"HIM"%-17s"NOR MAG"%-17s"NOR"%s\n", ip, option, TIME_D->replace_ctime(data["recordtime"]), data["releasetime"] ? TIME_D->replace_ctime(data["releasetime"]) : "無限", data["note"]||"");
		}
		else
			msg += "沒有任何 IP 限制設定。\n";
		msg += WHT"─────────────────────────────────────\n"NOR;
		return me->more(msg);
	}
	
	if( sscanf(arg, "%s %s", option, arg) != 2 )
		return tell(me, "請 help setip 查詢正確指令格式。\n");
		
	if( sscanf(arg, "%s in %d with %s", ip, releasetime, note) != 3 && sscanf(arg, "%s in %d", ip, releasetime) != 2 && sscanf(arg, "%s with %s", ip, note) != 2 )
		ip = arg;

	if( !valid_ip(ip) )
		return tell(me, "IP 格式錯誤。\n");

	switch(option)
	{
		case "ban":
			if( IP_D->query_ip(ip) )
				return tell(me, "IP「"+ip+"」已有設定限制，請先刪除設定。\n");

			IP_D->set_ip(me, ip, BAN, releasetime*3600);
			
			if( releasetime )
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"設定 "+releasetime+" 小時內禁止玩家經由「"+ip+"」的 IP 位置登入遊戲。");
			else
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"設定永久禁止玩家經由「"+ip+"」的 IP 位置登入遊戲。");
			if( note )
			{
				IP_D->set_ip_note(me, ip, note);
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"標示 IP「"+ip+"」的設定註解為："+note+"。");
			}
			break;
		case "cmdlimit":
			if( IP_D->query_ip(ip) )
				return tell(me, "IP「"+ip+"」已有設定限制，請先刪除設定。\n");

			IP_D->set_ip(me, ip, CMDLIMIT, releasetime*3600);
			
			if( releasetime )
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"設定 "+releasetime+" 小時內限制經由「"+ip+"」的 IP 位置登入之玩家指令執行速度。");
			else
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"設定永久限制經由「"+ip+"」的 IP 位置登入之玩家指令執行速度。");
			if( note )
			{
				IP_D->set_ip_note(me, ip, note);
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"標示 IP「"+ip+"」的設定註解為："+note+"。");
			}
			break;
		case "ok":
			if( IP_D->query_ip(ip) )
				return tell(me, "IP「"+ip+"」已有設定限制，請先刪除設定。\n");
				
			IP_D->set_ip(me, ip, OK, releasetime*3600);
			
			if( releasetime )
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"設定 "+releasetime+" 小時內「"+ip+"」的 IP 位置應該合法無虞。");
			else
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"設定「"+ip+"」的 IP 位置應該合法無虞。");
			
			if( note )
			{
				IP_D->set_ip_note(me, ip, note);
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"標示 IP「"+ip+"」的設定註解為："+note+"。");
			}
			break;	
		case "-d":
			if( !IP_D->query_ip(ip) )
				return tell(me, "IP「"+ip+"」原本就沒有任何限制設定。\n");
				
			IP_D->delete_ip(me, ip);
			CHANNEL_D->channel_broadcast("sys", me->query_idname()+"取消 IP「"+ip+"」的所有設定限制。");
			break;
		default:
			return tell(me, "沒有 "+option+" 這個設定選項。\n");	
	}	
}