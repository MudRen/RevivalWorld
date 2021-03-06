/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : look.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-2-8
 * Note   : look 指令
 * Update :
 *  o 2001-07-03 Clode 增加物件座標判斷
 *
 -----------------------------------------
 */

#include <map.h>
#include <lock.h>
#include <time.h>
#include <ansi.h>
#include <daemon.h>
#include <feature.h>
#include <location.h>
#include <message.h>

inherit COMMAND;

string help = @HELP
        標準 look 指令。
HELP;

#define MAX_OBJECT_SHOW		30

#define EXITSORT	({"up","down","west","east","north","south","southeast","southwest","northwest","northeast"})

int sort_exits(mapping exits, string e1, string e2)
{
	int idx1, idx2;
	
	if( arrayp(exits[e1]) ) return 1;
	if( arrayp(exits[e2]) ) return -1;

	idx1 = member_array(e1, EXITSORT);
	idx2 = member_array(e2, EXITSORT);
	
	if( idx1 == -1 ) return 1;
	if( idx2 == -1 ) return -1;

	return idx1-idx2;
}

private void do_command(object me, string arg)
{
	string msg="";
	object ob, env = environment(me);
	object *inventories;
	mapping exits, actions;
	mixed targetroom;

	if( !env )
		return tell(me, "你漫漫飄身在空虛之中，附近什麼都沒有，一切虛空。\n");

	if( !arg || arg == "here" )
		inventories = present_objects(me) - ({ me });
	else if( arg == "outside" )
	{
		if( !environment(env) )
			return tell(me, query("short", env)+"的外面什麼都沒有。\n");
		else
		{
			inventories = present_objects(env) - ({ env });
			env = environment(env);
		}
	}
	else
	{
		// Looking At Interactive Object
		if( arg == "me" ) ob = this_player();
		if( !ob ) ob = present(arg);
		if( objectp(ob) )
		{
			if( ob->is_living() )
			{
				if( ob == me )
					msg("$ME看了看自己身體，一臉讚嘆的樣子。\n", me, 0, 1);
				else
					msg("$ME眼光迅速掃過$YOU身上的每一個毛細孔，似乎想要看透$YOU的一切。\n", me, ob, 1);
			}
	
			if( !ob->is_living() && mapp(actions = ob->query_actions()) )
				msg += sprintf("特殊指令 "HIY"%-=80s\n"NOR, implode(keys(actions), ", "));
	
			msg = " "+ob->long()+msg;
			return me->more(msg);
		}
		else if( targetroom = query("exits/" + arg, env) )
		{
			if( !wizardp(me) && query("lock/" + arg, env) )
				return tell(me, "往 "+capitalize(arg)+" 方向有一道牆擋住了"+pnoun(2, me)+"的視線。\n");
			if( stringp(targetroom) )
			{
				env = load_object(targetroom);
				inventories = all_inventory(env);
				msg("$ME伸長了脖子，探頭往 "+capitalize(arg)+" 方向的"+query("short", env)+"看去。\n", me, 0, 1);
				broadcast(env, "附近似乎有人正往這個地方看了過來。\n");
			}
			else
				return tell(me, "從這裡無法往 "+arg+" 的方向看。\n");
		}
		else return tell(me, "這裡沒有 " + arg + " 這個東西或出口。\n");
	}

	// 地圖系統
	if( env->is_maproom() )
	{
		array loc = arg == "outside" ? query_temp("location", environment(me)) : query_temp("location", me);

		if( query("last_title_screen", me) != MAP_D )
		{
			tell(me, SAVEC + REF + REST);
			set("last_title_screen", MAP_D, me);
		}

		if( sizeof(loc) )
		msg += "目前位置"NOR WHT"("+(loc[X]+1)+","+(loc[Y]+1)+")──"NOR"「"+MAP_D->coor_short_name(loc)+NOR"」\n";

		if( !query("env/no_map", me) )
			msg += (MAP_D->show_map(loc) || "地圖系統錯誤，請通知巫師處理。\n");
		msg += MAP_D->query_map_system(loc)->query_coor_data(loc, "long")||"";
		msg += MAP_D->query_map_system(loc)->query_coor_data(loc, "status")||"";

	}
	// 一般環境物件顯示
	else	
	{
		
		array loc = env->query_location();
		object master = env->query_master();
		string room_function_short = env->query_room_function_short();
		string longtext = query("long", env);

		msg += (query("short", env)||"無名稱") + (room_function_short?" "+room_function_short:"") +(loc?" "+HIG+env->query_coor_short()+NOR:"")+ (wizardp(me)?" -> "+NOR WHT+file_name(env)+NOR:"")+"\n\n";
		
		if( longtext && longtext[0] )
			msg += longtext + (longtext[<1] == '\n' ? "\n" : "\n\n");

		msg += query("status", env)||"";

		if( env->is_module_room() )
			msg += (env->query_module_file())->look_room(env) || "";

		if( objectp(master) && sizeof(master->query_slave()) )
			msg += "連鎖 "+ (env == master ? HIG"連鎖"NOR GRN"中心"NOR:query("short", master)+HIG" <"+(master->query_location()[X]+1)+","+(master->query_location()[Y]+1)+">"NOR )+"，共 "+HIG+(sizeof(master->query_slave())+1)+NOR" 處\n";

		if( mapp(actions = env->query_actions()) && sizeof(actions))
			msg += "指令 "HIY+implode(sort_array(keys(actions),1)," ")+NOR+"\n";

		if( !(exits = query("exits", env)) ) 
			msg += "這個地方沒有任何的出口。\n";
		else
		{
			int lockflag;
			string *sort_exits, exitname, exitlong;

			exitlong = "出口 ";

			sort_exits = sort_array(keys(exits), (: sort_exits($(exits), $1, $2) :));

			foreach( string dir in sort_exits )
			{
				if( arrayp(exits[dir]) )
				{
					exitname = HIW"<"+capitalize(dir)+">"NOR;
					lockflag = MAP_D->query_coor_data(exits[dir], "lock");
				}
				else if( functionp(exits[dir]) )
				{
					exitname = HIG"<"+capitalize(dir)+">"NOR;
					lockflag = query("lock/"+dir, env);
				}
				else
				{
					exitname = "<"+capitalize(dir)+">"NOR;
					lockflag = query("lock/"+dir, env);
				}
				
				if( lockflag & LOCKED )
					exitname = HIR"<"+capitalize(dir)+">"NOR;
				if( lockflag & WIZLOCKED )
					exitname = HIY"<"+capitalize(dir)+">"NOR;
					
				exitlong += exitname+" ";
			}

			msg += multiwrap(exitlong, 72);
			
			msg[<1..<1] = NOR"\n\n";
		}
	}

	foreach(ob in sort_objects(inventories))
		msg += (ob->is_living()||ob->is_board() ? ob->short(1) : " "+remove_fringe_blanks(ob->short(1)))+ (wizardp(me)&&!userp(ob)?" -> "+NOR WHT+file_name(ob)+NOR:"")+"\n";

	tell(me, msg);
}
