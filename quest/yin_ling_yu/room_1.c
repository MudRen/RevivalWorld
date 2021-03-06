/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : room_1.c
 * Author : Clode@RevivalWorld
 * Date   : 2003-08-19
 * Note   : 標準房間
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>
#include <quest.h>

inherit STANDARD_ROOM;

string help = @HELP
在這個平凡無奇的房間內並沒有任何特殊的資訊。
HELP;



void create()
{
	set("short", WHT"良凡環的家"NOR);
	set("long",@TEXT
    這間屋子的四周都放滿了各種農作器具，很明顯是一個平凡的農家，但不平凡
的是地上的血泊中正倒臥著一個男子，胸口插著把刀，從血跡看來似乎剛被殺害不
久。這個男子雖然已經死亡，但手中仍緊握著一個藍色錦囊，似乎對他而言是個很
重要的東西，或許可以看看裡面有什麼線索。
TEXT);

	set("exits", ([
		"south" 	: ({ 37, 51, 0, "blueflowers", 0, 0, "37/51/0/blueflowers/0/0" }),
		"west"	: "/quest/yin_ling_yu/room_2",
	]));
	
	set("objects", ([
		"/quest/yin_ling_yu/liang_fan_huan" : 1 ,
	]));
	
	::reset_objects();
}

void do_search(object me, string arg)
{	
	if( !arg || arg=="" )
		return tell(me, pnoun(2, me)+"想要搜尋什麼？\n");

	if( strsrch(arg, "錦囊") != -1 )
	{
		if( query("total_online_time", me) < 15*24*60*60 )
			return tell(me, pnoun(2, me)+"的上線時間不足 15 天無法進行這個任務。\n");

		if( me->query_quest_step(QUEST_YIN_LING_YU) == 0 )
		{
			if( me->query_quest_finish(QUEST_YIN_LING_YU) && time() < me->query_quest_time(QUEST_YIN_LING_YU) + 60*60*24*7)
				return tell(me, pnoun(2, me)+"不久前才翻過這個錦囊，看不出有什麼其他特別的地方了。\n");
				
			tell(me, pnoun(2, me)+"打開了藍色錦囊，但裡頭卻沒有任何東西，只見錦囊外繡著兩個名字，分別是凡環與玲羽。\n");
			
			me->set_quest_note(QUEST_YIN_LING_YU, QUEST_YIN_LING_YU_NAME, "從藍色錦囊的外面發現了兩個名字：「凡環與玲羽」。");
			me->set_quest_step(QUEST_YIN_LING_YU, 1);
		}
		else if( me->query_quest_step(QUEST_YIN_LING_YU) == 2 )
		{
			tell(me, pnoun(2, me)+"又仔細的看了看藍色錦囊，原來內襯也縫著一些字，上面寫著：「綠影映照繯宇心」。\n");
			
			me->set_quest_note(QUEST_YIN_LING_YU, QUEST_YIN_LING_YU_NAME, "從藍色錦囊的內襯中發現了一句詩：「綠影映照繯宇心」。");
			me->set_quest_step(QUEST_YIN_LING_YU, 3);
		}
		else
			tell(me, pnoun(2, me)+"找不到這個藍色錦囊有什麼其他特別的地方了。\n");
	}
	else if( strsrch(arg, "血") != -1 || strsrch(arg, "足") != -1 )
		tell(me, "地上混亂的血色足跡中可以分辨出有數個人往西南方而去。\n");
	else if( strsrch(arg, "刀") != -1 )
		tell(me, "一把沾滿血跡的刀，但看刀形似乎並不是農家中使用的刀具。\n");
	else if( strsrch(arg, "藍") != -1 )
		tell(me, "非常精美的錦囊，以藍色的絲線縫製而成。\n");
	else if( strsrch(arg, "男") != -1 )
		tell(me, "這個男子的胸口被刀直穿而過，顯然是個致命的傷口。\n");
	else
		tell(me, pnoun(2, me)+"想要搜尋什麼？\n");
}

mapping actions = 
([
	"search" : (: do_search :),
]);