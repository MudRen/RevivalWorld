/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : _heart_beat_npc.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-10-10
 * Note   : NPC 心跳
 * Update :
 *  o 2005-02-12  修正 tick 以及檢查 save 函式是否存在
 *
 -----------------------------------------
 */

#include <daemon.h>
#include <location.h>
#include <function.h>

private nosave int tick;

nomask void condition_handler()
{
	object me = this_object();
	mapping condition;
	
	if( mapp(condition = query("condition")) )
	{
		foreach( string key, mapping value in condition )
		{
			if( value["time"] <= 0 )
			{
				catch(replace_string(key, "#","/")->stop_effect(this_object()));
				delete("condition/"+key);
				continue;
			}
			
			if( value["heart_beat"] > 0 && !(value["time"] % value["heart_beat"]) )
				catch(replace_string(key, "#","/")->heart_beat_effect(this_object()));
			
			addn("condition/"+key+"/time", -1);
		}
	}

	if( !me->is_stamina_full() )
		me->earn_stamina(this_object()->stamina_regen());
	if( !me->is_health_full() )
		this_object()->earn_health(me->health_regen());
	if( !me->is_energy_full() )
		this_object()->earn_energy(me->energy_regen());

	// 每 25 秒執行一次
	if( !(tick % 25) )
	{
		// 食物與飲水
		if( me->query_food_cur() > 0 )
			me->cost_food(1);
		if( me->query_drink_cur() > 0 )
			me->cost_drink(1);
	}

	if( query("faint") )
	{		
		float recover_speed = 1 + me->query_skill_level("consciousness")/100.;
		
		if( me->query_stamina_cur()*recover_speed >= me->query_stamina_max()/2 )
			me->wakeup();
	}
}

/*
	NPC 行為整理表 :
		
	*behavior/reply_say	執行 say 指令時被動呼叫
	(function) fp(object this_player(), string "說話內容")
	
	*behavior/reply_emote	執行表情指令時被動呼叫
	(function) fp(object this_player(), string "表情指令", string "表情附加文字")
	
	*behavior/walking	由 heart_beat 主動依照 walking 設定秒數定期走動
	(int) 秒數

	*behavior/shopping	由 heart_beat 主動依照 shopping 設定秒數定期購物
	(int) 秒數

	*behavior/get_salary	由 heart_beat 主動依照 get_salary 設定秒數定期索拿薪水
	(int) 秒數
	
	*behavior/random	由 heart_beat 每次呼叫
	(mapping) random =
	([
		fp 1	:	每個 heart_beat 做一次此指令的機率 1(單位:萬分之一),
		fp 2	:	每個 heart_beat 做一次此指令的機率 2(單位:萬分之一),
	])
*/
		
void heart_beat()
{
	mapping behavior;

	if( !tick )
		tick = random(1024);
	else
		++tick;

	condition_handler();

	// 遊戲時間 1 小時(即實際時間 120 秒)紀錄一次年齡
	if( !(tick % 120) )
	{
		if( addn("age_hour", 1) == 8760 )
			BIRTHDAY_D->grow_up(this_object());
	}

	if( mapp(behavior = query("behavior")) )
	{
		// 走動行為
		if( behavior["walking"] && !(tick % behavior["walking"]) )
			this_object()->behavior_walking();

	
		// 任意指令行為
		if( sizeof(behavior["random"]) )
		{
			foreach(function fp, int prob in behavior["random"])
				if( prob > random(10000) )
				{
					if( functionp(fp) & FP_OWNER_DESTED )
				        {
				                if( functionp(fp) & FP_NOT_BINDABLE )
				                	error("heart_beat_npc.c reply_say() 函式無法再次連結。\n");
				
				                fp = bind(fp, this_object());
				        }
					evaluate(fp);
				}
		}
	}
	// fixed by sinji
	//if( !(tick%1800) && function_exists("save", this_object()) ) 
	//	this_object()->save();
		
	if( !(tick%1800) ) 
		this_object()->save();
}

int query_tick()
{
	return tick;
}