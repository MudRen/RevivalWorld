/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : system_d.c
 * Author : Clode@RevivalWorld
 * Date   : 2002-09-28
 * Note   : 系統精靈
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <object.h>
#include <daemon.h>
#include <mudlib.h>
#include <message.h>

string *preload_list;
object *loginuser;

#define	PRELOAD_PATH	"/system/kernel/etc/preload"

void broadcast(string msg)
{
	foreach(object ob in loginuser)
	{
		if( objectp(ob) )
			ob->directly_receive(msg);
	}
}

void distributed_preload()
{
	mixed err;
	object ob;
	
	if( !sizeof(preload_list) )
	{
		foreach(ob in loginuser)
		{
			if( objectp(ob) )
			{
				ob->directly_receive("\n"MUD_FULL_NAME"啟動完畢，重新連線中...。\n");
				destruct(ob);
			}
		}

		return;
	}
	
	log_file("system/preload",sprintf("載入 %s\n", preload_list[0]));
	
	

	if( !(ob = find_object(preload_list[0])) ) 
	{
		reset_eval_cost();

		if( err = catch(ob = load_object(preload_list[0])) )
		{
			broadcast(sprintf(HIW+"%'0'3d "NOR"- 載入 %s ...", sizeof(preload_list), preload_list[0]));
			broadcast(HIR"Failed\n"NOR);
			log_file("system/preload",sprintf("載入 %s 時發生錯誤: %O\n", preload_list[0], err));
		} 
		else
		{
			broadcast(sprintf(HIW+"%'0'3d "NOR"- 載入 %s ...", sizeof(preload_list), preload_list[0]->query_name() || preload_list[0]));
			broadcast(sprintf(HIG"Done (%.2f Kbytes)\n"NOR, memory_info(ob)/1024.));
		}
		preload_list = preload_list[1..];
		call_out((: distributed_preload :), 1);
	}
	else
	{
		broadcast(sprintf(HIW+"%'0'3d "NOR"- 載入 %s ...", sizeof(preload_list), preload_list[0]->query_name() || preload_list[0]));
		broadcast(sprintf(HIC"Loaded (%.2f Kbytes)\n"NOR, memory_info(ob)/1024.));
		preload_list = preload_list[1..];
		distributed_preload();
	}
}

void distributed_system_preload()
{
	string path, file;
	
	loginuser = allocate(0);
	preload_list = filter_array( explode(read_file(PRELOAD_PATH), "\n") , (: $1[0]!='#' :) );

	foreach( path in preload_list )
	{
		if( path[<1] == '/' && file_size(path)==-2 )
		{
			foreach( file in get_dir(path) )
			{
				if( file[<2..<1] == ".c" && file_size(path+file) > 0 )
					preload_list += ({ path+file });
			}
			preload_list -= ({ path });
		}
		else if( path[<2..<1] != ".c" || file_size(path) <= 0 )
			preload_list -= ({ path });
	}
	
	log_file("system/preload",sprintf("Preload 列表 %O\n", preload_list));

	distributed_preload();
}

int valid_login()
{
	return !preload_list || !sizeof(preload_list);
}

void add_loginuser(object ob)
{
	loginuser |= ({ ob });
}

string query_total_system_info()
{
	int module_room, module_npc, module_product;
	string msg = "";

	
	foreach(object ob in objects())
	{
		if( ob->is_module_room() )
			++module_room;
		else if( ob->is_module_npc() )
			++module_npc;
		else if( ob->is_module_product() )
			++module_product;
	}
	
	msg += "真實時間   - "+TIME_D->replace_ctime(time())+"\n";
	msg += "遊戲時間   - "+TIME_D->game_time_description()+"\n";
	msg += "啟動時間   - "+CHINESE_D->chinese_period(uptime())+"\n";
	msg += "使用者總數 - "+sizeof(users())+" 人\n";
	msg += "物件總數   - "+sizeof(objects())+" 個\n";
	msg += "房間模組數 - "+module_room+" 間\n";
	msg += "員工模組數 - "+module_npc+" 員\n";
	msg += "產品模組數 - "+module_product+" 個\n";
	msg += "心跳總數   - "+sizeof(heart_beats())+" 個\n";
	msg += "延遲呼叫數 - "+sizeof(call_out_info())+" 個\n";
	msg += "系統負載   - "+query_load_average()+"\n";
	msg += "封包傳輸   - "+NETWORK_D->query_network_packet_stats()+"\n";
	msg += "記憶體使用 - "+sprintf("%.6f MBytes\n", memory_info()/1024./1024. );

	return msg;
}

void create()
{
	if( uptime() < 30 )
		distributed_system_preload();
}

int remove()
{

}
string query_name()
{
	return "中央管理系統(SYSTEM_D)";
}
