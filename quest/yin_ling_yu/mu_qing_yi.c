/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : grandam.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-12-13
 * Note   : 
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

/*
	系統預設之 NPC 反應函式
	void reply_emote(object me, string verb, string args);
	void reply_say(object me, string msg);
	void reply_catch_tell(object me, string verb, string args);
	void reply_get_object(object me, object ob, mixed amount);
	void reply_get_money(object me, string unit, mixed money);
*/

#include <ansi.h>
#include <inherit.h>
#include <gender.h>
#include <daemon.h>
#include <quest.h>

inherit STANDARD_NPC;

void do_command(string cmd);

void set_behavior()
{
	set("behavior/random", 
	    ([
			(: do_command("sing") :)   : 50,
	    ]));
}

void delete_behavior()
{
	delete("behavior");
}

void reply_say(object me, string msg)
{
	if( !objectp(me) ) return;

	if( !msg || !msg[0] )
		return;
		
	if( strsrch(msg, "柯文") != -1 )
	{
		do_command("say 我不知道他是誰，但我可以從這個名字中感受到一股人間的大愛");
		return;
	}
	
	if( strsrch(msg, "凡環") != -1 )
	{
		do_command("say 我不知道他是誰，但我知道他已經遭遇不測，人生就是如此，珍惜您所擁有的一切吧...");
		return;
	}
	
	if( strsrch(msg, "玲羽") != -1 )
	{
		do_command("say 唉...玲羽阿，她的純樸很討人喜歡，兩年前我曾遇見過她，僅管當時我已預知今日的結果，但我仍不忍心告訴她這個必定發生的悲劇");
		return;
	}
	
	if( strsrch(msg, "人參") != -1 )
	{
		do_command("say 玲羽所挖掘出的那株野山人參的特色並不在於它的藥性，而是在於它蘊育了數千年所產生的靈性");
		return;
	}
	
	if( strsrch(msg, "靈性") != -1 )
	{
		do_command("smile "+me->query_id(1));
		do_command("say "+pnoun(2, me)+"會遇上茵玲羽，便是有緣人，上天自會給"+pnoun(2, me)+"答案");
		
		if( me->query_quest_step(QUEST_YIN_LING_YU_2) == 1 )
		{
			me->set_quest_note(QUEST_YIN_LING_YU_2, QUEST_YIN_LING_YU_2_NAME, "找到了仙女『穆青依』，知道了原來這株野山人參具有著神秘的靈性。");
			me->set_quest_step(QUEST_YIN_LING_YU_2, 2);
		}
		return;
	}
	
	if( strsrch(msg, "答案") != -1 )
	{
		do_command("say 解鈴尚需繫鈴人阿.....");
		return;
	}
		
	if( me->query_quest_step(QUEST_CITY_WALKER) == 1 && strsrch(msg, "城市遊人") != -1 )
	{
		do_command("say 嗯？"+pnoun(2, me)+"想知道一些關於他的事情嗎？");
		me->set_quest_note(QUEST_CITY_WALKER, QUEST_CITY_WALKER_NAME, "或許該讀那段詩給穆青依聽聽。");
		me->set_quest_step(QUEST_CITY_WALKER, 2);
		return;
	}
	
	if( me->query_quest_step(QUEST_CITY_WALKER) == 2 && strsrch(msg, "一半擁有哥倫布的豪情") != -1 )
	{
		msg("$ME注意到$YOU輕靈的身形突然顫動了一下，但隨即又回復原本的樣子...。\n", me, this_object(), 1);
		do_command("say ...原來如此");
		do_command("say 這首詩叫作「孵一個文藝復興的夢」，"+pnoun(2, me)+"記著吧。");
		
		me->set_quest_note(QUEST_CITY_WALKER, QUEST_CITY_WALKER_NAME, "原來這首詩叫作「孵一個文藝復興的夢」。");
		me->set_quest_step(QUEST_CITY_WALKER, 3);
		return;
	}
}

void reply_emote(object me, string verb, string args)
{
	if( !objectp(me) ) return;
	
	do_command("bow "+me->query_id(1));
}

void reply_get_object(object me, object ob, mixed amount)
{
	if( !objectp(ob) ) return;

	process_function(({
		1,
		do_command("say 解鈴尚需繫鈴人..."),
		1,
		do_command("drop all "+ob->query_id(1)),
	}));
}


void create()
{
	set_idname("mu qing yi", HIG"穆"NOR GRN"青依"NOR);
	set_temp("status", HIG"世外"NOR GRN"仙女"NOR);

	set("long", "好清秀的年輕女子，她的氣質風采使人不敢直視著她，站在她的身旁不由得自慚形穢。");
	set("unit", "位");
	set("age", 24);
	set("gender", FEMALE_GENDER);

	// 啟動主動行為
	set_behavior();

	startup_living();
}
