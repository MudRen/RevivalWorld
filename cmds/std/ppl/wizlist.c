/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : wizlist.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-4-11
 * Note   : wizlist 指令
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <daemon.h>
#include <ansi.h>
#include <feature.h>
#include <message.h>

inherit COMMAND;

string help = @HELP
巫師清單

這個指令可以查詢重生的世界中的所有巫師及目前線上的巫師，
如您有任何疑問歡迎洽詢線上巫師，或利用 'bug' 指令回報遊戲問題。

相關指令:
HELP;

#define OVERDAY		30

nosave string *wiz_levels = ({ "admin", "advisor", "wizard", "guest" });

private void do_command(object me, string arg)
{
	int online, now_time = time();
	object user;
	string color, str;
	mapping final=allocate_mapping(5), num=allocate_mapping(0);
	mapping wizards = SECURE_D->query_wizards();

	final["admin"] = 	WHT"─ "HIW"Administrator 系統管理員"NOR WHT"  ─────────────────\n\n  "NOR;
        final["advisor"] = 	WHT"─ "HIW"Advisor 系統顧問"NOR WHT"  ─────────────────────\n\n  "NOR;
        final["wizard"] = 	WHT"─ "HIW"Wizard 巫師"NOR WHT"   ───────────────────────\n\n  "NOR;
        final["guest"] = 	WHT"─ "HIW"Guest 特別來賓"NOR WHT"  ──────────────────────\n\n  "NOR;
	if( wizardp(me) )
	foreach( string id in sort_array(keys(wizards), 1) )
	{
		if( find_player(id) )
			++online && color = HIC;
		else if( file_size(user_path(id)) != -2 )
			color = HIR"遺失角色";
		else
		{
			int last_login;
			if( !objectp(user = load_user(id)) ) color = HIR;
			// 超過 30 天未上線
			else if(
				!(last_login = query("last_login/time", user)) ||
				now_time - last_login > 60*60*24*OVERDAY
			) color = NOR YEL;
			else color = CYN;
			destruct(user);
		}
		final[wizards[id]] += sprintf("%-13s"NOR"%s", color+capitalize(id), ++num[wizards[id]]%6 ? "" : "\n  ");
	}
	else
	foreach(string id in sort_array(keys(wizards), 1))
	{
		if( find_player(id) )
			++online && color = HIC;
		else 
			color = CYN;
		
		final[wizards[id]] += sprintf("%-13s"NOR"%s", color+capitalize(id), ++num[wizards[id]]%6 ? "" : "\n  ");
	}
	str = sprintf(NOR WHT"\n  巫師共有 "HIW"%d"NOR WHT" 位，線上 "HIW"%d"NOR WHT" 位\n\n"NOR, sizeof(wizards), online);
	str = sprintf("%63s", str);
	foreach(string lv_name in wiz_levels)
		str += final[lv_name] + (!(num[lv_name]%6) ? "\n" : "\n\n");
	str += NOR WHT"  如"+pnoun(2, me)+"有任何疑問歡迎洽詢線上巫師，或利用 '"HIW"bug"NOR WHT"' 指令回報遊戲問題。\n\n"NOR;
	tell(me, str, CMDMSG);
}
