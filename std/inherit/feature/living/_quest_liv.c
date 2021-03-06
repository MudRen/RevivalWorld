/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : _quest_liv.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-12-19
 * Note   : 任務繼承檔
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <daemon.h>

// 設定 quest 紀錄
void set_quest_note(string quest, string name, string note)
{
	set("quest/"+quest+"/time", time());
	set("quest/"+quest+"/name", name);
	set("quest/"+quest+"/note", note);
	
	tell(this_object(), HIY"任務訊息更新，請利用 quest 指令查詢。\n"NOR);
}

// 設定 quest 資料
void set_quest_data(string quest, string key, mixed value)
{
	set("quest/"+quest+"/data/"+key, value);
}

// 取得 quest 資料
mixed query_quest_data(string quest, string key)
{
	return query("quest/"+quest+"/data/"+key);
}

// 設定 quest 步驟
void set_quest_step(string quest, int step)
{
	set("quest/"+quest+"/step", step);
}

// 取得 quest 步驟
int query_quest_step(string quest)
{
	return query("quest/"+quest+"/step");
}

// 設定此 quest 已經結束
void set_quest_finish(string quest, string name, string note)
{
	int finish_time = addn("quest/"+quest+"/finish", 1);
	
	if( finish_time == 1 && !SECURE_D->is_wizard(this_object()->query_id(1)) )
	{
		int totalquests = sizeof(filter(query("quest"), (: $2["finish"] :)));
		TOP_D->update_top("quest", this_object()->query_id(1), totalquests, this_object()->query_idname(), query("city"));
	}
	
	delete("quest/"+quest+"/step");
	delete("quest/"+quest+"/data");
	set_quest_note(quest, name, note);
}

// 檢查 quest 是否已經結束
int query_quest_finish(string quest)
{
	return query("quest/"+quest+"/finish");
}

// 取得最後一次更新時間
int query_quest_time(string quest)
{
	return query("quest/"+quest+"/time");
}
