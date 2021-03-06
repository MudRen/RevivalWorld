/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : yi_ke_wen.c
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

#define QUEST_1 "茵玲羽之謎"

inherit STANDARD_NPC;

void create()
{
	set_idname("yi ke wen","易柯文");
	set("long", "一位身中數刀失血過多而死的男子。");
	set("unit", "位");
	set("age", 26);
	set("gender", MALE_GENDER);
	set_temp("status", ([ HIR"屍體"NOR : -1 ]));
}
