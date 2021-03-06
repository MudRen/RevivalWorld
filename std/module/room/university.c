/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : university.c
 * Author : Clode@RevivalWorld
 * Date   : 2003-05-31
 * Note   : 大學
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <map.h>
#include <feature.h>
#include <message.h>
#include <daemon.h>
#include <npc.h>
#include <skill.h>
#include <condition.h>

inherit ROOM_ACTION_MOD;

#define CLASS_UNIT	10000
#define MSGTITLE	HIM"上課-"NOR


void do_list(object me, string arg)
{
	string skill_type;
	string list="";
	object skillob, env = environment(me);
	string *skills = SKILL_D->query_sorted_skills();
	string course = query("course", env);
	
	list += WHT"──────────────────────────────────────────\n"NOR;
	
	if( course )
		list += "目前課程："HIY+(SKILL(course))->query_idname()+"\n"NOR;
	else
		list += "目前沒有開設任何課程\n";

	list += WHT"──────────────────────────────────────────\n"NOR;
	list += "全部課程資料                    學習難度 上限 玩家 員工 課程簡介\n";
	
	foreach(string skill in skills)
	{
		if( !SKILL_D->skill_exists(skill) )
		{
			skill_type = skill;		
			continue;
		}
		
		skillob = load_object(SKILL(skill));
		
		if( !objectp(skillob) ) continue;
	
		if( skillob->self_learning() ) continue;

		if( skill_type )
		{
			list += "- "+skill_type+" -\n";
			skill_type = 0;
		}

		list += sprintf("%-36s"WHT"%4.1f"HIY" %4d "NOR" %2s   %2s  %s"NOR"\n"NOR
			    ,skillob->query_idname()
			    ,1/(skillob->exp_multiple(me))
			    ,skillob->max_level(me)

			    ,skillob->allowable_learn() & PLAYER_SKILL ? ( skillob->allowable_learn(me) ? HIW : HIR)+"○"NOR : WHT"╳"NOR
			    ,skillob->allowable_learn() & NPC_SKILL ? HIW"○"NOR : WHT"╳"NOR
			    ,skillob->query_skill_note()||"無說明");
	}
	list += WHT"──────────────────────────────────────────\n"NOR;
	list += "                                      "HIW"○"NOR"：可學習、"HIR"○"NOR"：可學習但程度未到、"WHT"╳"NOR"：無法學習\n\n"NOR;
	
	me->more(list);
}



void do_setup(object me, string arg)
{
	object env = environment(me);
	string course = query("course", env);

	if( query("owner", env)[11..] != query("enterprise", me) )
		return tell(me, pnoun(2, me)+"並不是本企業的成員。\n");

	if( !arg )
		return tell(me, "請輸入正確的指令格式。\n");

	if( sscanf(arg, "course %s", course) == 1 )
	{
		if( course == "-d" )
		{
			msg("$ME取消這間教室的課程設定。\n", me, 0, 1);
			delete("course", env);
			env->save();
			return;
		}
		
		if( !SKILL_D->skill_exists(course) || (SKILL(course))->self_learning() )
			return tell(me, "並沒有 "+course+" 這種課程。\n");
		
		msg("$ME將這間教室的課程設定為「"+(SKILL(course))->query_idname()+"」。\n", me, 0, 1);
		set("course", course, env);
		env->save();
	}
	else
		return tell(me, "請輸入正確的指令格式。\n");
}


void confirm_learn(object me, string skill, int socialexp, string moneyunit, int is_member, string input)
{
	int bonus;
	string msg = "";

	if( input && (lower_case(input) == "y" || lower_case(input) == "yes") )
	{
		switch(random(50))
		{
			case 0:
			{
				bonus = socialexp/100;
				msg = MSGTITLE"老師拿著粉筆在黑板上敲寫著複雜的數學公式...。\n";
				msg += MSGTITLE HIC"$ME減少耗費 1% 的社會經驗值("+bonus+")！！！\n"NOR;
				
				break;
			}
			case 1:
			{
				bonus = socialexp/50;
				msg = MSGTITLE"老師的腳突然從講臺上踩空狠狠地扭了一下，卻假裝什麼事也沒發生...。\n";
				msg += MSGTITLE HIC"$ME減少耗費 2% 的社會經驗值("+bonus+")！！！\n"NOR;
				
				break;
			}
			case 2:
			{
				msg = MSGTITLE"$ME偷偷拿了個小紙團往老師背後高速射去，只見老師左手輕輕往後一抄，化襲擊於無形...。\n";
				break;
			}
			case 3:
			{
				bonus = socialexp/33;
				msg = MSGTITLE"老師冷冷地說道：「"+me->query_idname()+pnoun(2, me)+"來回答這個問題。」\n";
				msg += MSGTITLE"$ME臉色一變馬上說道：「嘔...老師對不起，我身體不舒服想吐...。」\n";
				msg += MSGTITLE HIC"$ME減少耗費 3% 社會經驗值("+bonus+")！！！\n"NOR;
				
				break;
			}
			case 4:
			{
				msg = MSGTITLE"$ME睡死在桌上，書上流滿了口水：「呼...呼...呼...」。\n";
				break;
			}
			case 5:
			{
				msg = MSGTITLE"$ME坐在第一排的座位上不時地試著偷看女老師的裙底。\n";
				break;
			}
			case 6:
			{
				msg = MSGTITLE"教室外不時地傳來：「燒肉粽...好吃的燒肉粽來囉...」。\n";
				break;
			}
			case 7:
			{
				msg = MSGTITLE"教室裡傳來陣陣飯菜香，只見$ME低著頭不知道在幹嘛...。\n";
				break;
			}
			case 8:
			{
				msg = MSGTITLE"$ME兩眼癡呆地隨手抄寫筆記，想來$ME自己也看不懂筆記寫了些什麼。\n";
				break;
			}
			case 9:
			{
				bonus = socialexp/33;
				msg = MSGTITLE"老師：「"+me->query_idname()+"我問"+pnoun(2, me)+"，1+1 等於多少？」\n";
				msg += MSGTITLE"$ME緊張的臉色頓時輕鬆起來：「這題我終於會了，答案是 11 。\n";
				msg += MSGTITLE HIC"$ME減少耗費 3% 社會經驗值("+bonus+")！！！\n"NOR;
				break;
			}
			case 10:
			{
				bonus = socialexp/20;
				msg = MSGTITLE"$ME不屑地說：「吼，老師你這裡教錯了啦，到底懂不懂啊不要亂教。」\n";
				msg += MSGTITLE"老師：「"+me->query_idname()+pnoun(2, me)+"不用想畢業了...」\n";
				msg += MSGTITLE HIC"$ME減少耗費 5% 社會經驗值("+bonus+")！！！\n"NOR;
				break;
			}
			case 11:
			{
				bonus = socialexp/10;
				msg = MSGTITLE"$ME淫蕩地說：「老師妳好美，聲音也好好聽喔。」\n";
				msg += MSGTITLE"女老師害羞地說：「"+me->query_idname()+"同學千萬別這麼說，不過"+pnoun(2, me)+"這科成績將會得到滿分。」\n";
				msg += MSGTITLE HIC"$ME減少耗費 10% 社會經驗值("+bonus+")！！！\n"NOR;
				break;
			}
			case 12:
			{
				bonus = socialexp/33;
				msg = MSGTITLE"老師：「請"+me->query_idname()+"同學用'棉被'造一個句子。」\n";
				msg += MSGTITLE"$ME：「前面那位女同學的衛生棉被我偷走了。」\n";
				msg += MSGTITLE HIC"$ME減少耗費 3% 的社會經驗值("+bonus+")！！！\n"NOR;
				break;
			}
			case 13:
			{
				msg = MSGTITLE"$ME突然往教室門口衝去。\n";
				msg += MSGTITLE"老師：「"+me->query_idname()+pnoun(2, me)+"上課上到一半要去哪！給我站住！」\n";
				msg += MSGTITLE"$ME：「有人正在偷我商店架子上的東西！！」\n";
				msg += MSGTITLE"老師：「...」\n";
				break;
			}
			case 14:
			{
				msg = MSGTITLE"老師：「請"+me->query_idname()+"同學用'Mud'造一個句子。」\n";
				msg += MSGTITLE"$ME：「媽的不要吵我睡覺。」\n";
				break;
			}
			case 15:
			{
				bonus = socialexp/50;
				msg = MSGTITLE"老師拿起被剪爛的點名簿罵道：「這是誰亂剪的！？」\n";
				msg += MSGTITLE"$ME拿著剪刀指著隔壁善良的同學：「他。」\n";
				msg += MSGTITLE"隔壁善良的同學還未來得及反應已經被老師格殺倒斃。\n";
				msg += MSGTITLE HIC"$ME減少耗費 2% 的社會經驗值("+bonus+")！！！\n"NOR;
				break;
			}
		
		}

		if( !me->cost_social_exp(socialexp-bonus) )
		{
			tell(me, pnoun(2, me)+"沒有足夠的社會經驗值來作這項學習。\n");
			return me->finish_input();
		}

		me->add_skill_exp(skill, socialexp);

		msg(msg+"$ME耗費 "HIG+(socialexp-bonus)+NOR" 點社會經驗值來學習「"HIY+(SKILL(skill))->query_idname()+NOR"」。\n", me, 0, 1);
		me->finish_input();
	}
	else
	{
		tell(me, pnoun(2, me)+"決定不學習這項技能。\n");
		me->finish_input();
	}
}

void do_learn(object me, string arg)
{
	int is_member;
	int socialexp;
	string skill;
	object skillob;
	object env = environment(me);
	string moneyunit = env->query_money_unit();

	skill = query("course", env);

	if( !skill )
		return tell(me, "這間教室並沒有開設任何課程。\n");
	
	if( !SKILL_D->skill_exists(skill) || (SKILL(skill))->self_learning() )
		return tell(me, "並沒有 "+skill+" 這種課程。\n");

	skillob = load_object(SKILL(skill));

	if( !arg || (!sscanf(arg, "%d", socialexp) && arg != "full") )
		return tell(me, "請輸入正確的指令格式。\n");

	if( arg == "full" )
	{
		socialexp = to_int((skillob->level_exp(skillob->max_level(me)) - me->query_skill_exp(skill))/skillob->exp_multiple(me));

		if( socialexp < 1 )
			return tell(me, pnoun(2, me)+"的「"HIY+skillob->query_idname()+NOR"」技能等級已經到達最大值。\n");
	}
	
	if( socialexp < 1 || socialexp > 100000000 )
		return tell(me, "耗費的社會經驗值必須介於 1 至 100,000,000 之間("+socialexp+")。\n");

	if( !skillob->allowable_learn(me) )
		return tell(me, skillob->query_idname()+"對"+pnoun(2, me)+"而言太過艱深。\n");
		
	if( me->query_skill_level(skill) >= skillob->max_level(me) )
		return tell(me, pnoun(2, me)+"的"+skillob->query_idname()+"已經達到最高等級了。\n");

	is_member = query("owner", env)[11..] == query("enterprise", me);
	
	tell(me, pnoun(2, me)+"準備耗費 "HIG+NUMBER_D->number_symbol(socialexp)+NOR" 點社會經驗值來學習「"HIY+skillob->query_idname()+NOR"」。\n是否確定要學習(Yes/No)？\n");	

	input_to( (: confirm_learn, me, skill, socialexp, moneyunit, is_member :) );
}



void leave(object room, object me)
{
	me->stop_condition(KNOWLEDGESANCTUARY);
}

void init(object room, object me)
{
	if( query("function", room) == "classroom" )
	{
		if( !me->in_condition(KNOWLEDGESANCTUARY) )
			me->start_condition(KNOWLEDGESANCTUARY);
	}
}

string look_room(object room)
{
	string course = query("course", room);
	
	if( query("function", room) == "classroom" )
	{
		if( !course )
			return "目前沒有開設任何課程。\n"NOR;
		else if( !SKILL_D->skill_exists(course) )
		{
			delete("course", room);
			return "目前沒有開設任何課程。\n"NOR;
		}
		else
			return "老師正在講台上講解著"HIY+(SKILL(course))->query_idname()+NOR"的課程。\n"NOR;
	}
}

// 設定建築物內房間型態種類
nosave mapping action_info =
([
	"classroom"	:
	([
		"short"	: NOR HIW"教室"NOR,
		"help"	: 
			([ 
"topics":
@HELP
    這裡是大學內的一間教室。
HELP,

"list":
@HELP
查詢課程指令
  list			- 列出所有的課程資訊
HELP,

"setup":
@HELP
教室課程種類設定指令
  setup course water	- 設定本教室專門教授清水採集(Water)的課程
  setup course -d	- 取消課程設定
HELP,

"learn":
@HELP
學習指令
  learn full		- 自動計算學習到最高等級所需的社會經驗值
  learn 20000		- 耗費 20,000 點的社會經驗值來學習這間教室所開設的課程
                          學費每單位以 10,000 社會經驗來計算
HELP,
			]),

		"heartbeat":0,	// 實際時間 1 秒為單位
		"job": 0,
		"action":
			([
			
				"list" 		: (: do_list :),
				"learn"		: (: do_learn :),
				"setup"		: (: do_setup :),
			]),
	]),
]);

// 設定建築物資料
nosave array building_info = ({
	
	// 建築物之中文名稱
	HIM"大學"NOR

	// 開張此建築物之最少房間限制
	,12

	// 城市中最大相同建築數量限制(0 代表不限制)
	,5

	// 建築物建築種類, GOVERNMENT(政府), ENTERPRISE(企業集團), INDIVIDUAL(私人)
	,ENTERPRISE

	// 建築物可建築區域, AGRICULTURE_REGION(農業), INDUSTRY_REGION(工業), COMMERCE_REGION(商業)
	,AGRICULTURE_REGION

	// 開張儀式費用
	,"20000000"
	
	// 建築物關閉測試標記
	,0

	// 繁榮貢獻度
	,0
	
	// 最高可加蓋樓層
	,3
	
	// 最大相同建築物數量(0 代表不限制)
	,0
	
	// 建築物時代
	,1
});
