/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : nature_d.c
 * Author : Clode@RevivalWorld
 * Date   : 2003-07-22
 * Note   : 自然環境精靈, 氣候, 天災
 * Update :
 *
 -----------------------------------------
 */

#include <nature.h>
#include <nature_data.h>
#include <ansi.h>
#include <time.h>
#include <daemon.h>
#include <message.h>


// 自然資料
mapping nature;

string season;
int hour;

int flag_temperature(int temp)
{
	int flag;
	switch(temp)
	{
	case TEMPERATURE_LV_0:
		flag = WE_TEMPERATURE_0; break;
	case TEMPERATURE_LV_1:
		flag = WE_TEMPERATURE_1; break;
	case TEMPERATURE_LV_2:
		flag = WE_TEMPERATURE_2; break;
	case TEMPERATURE_LV_3:
		flag = WE_TEMPERATURE_3; break;
	default: break;
	}

	return flag;
}

int hour_plus(int h)
{
	h += hour;

	if( h >= 24 )
		return h - 24;
	else
		return h;
}

// 進行天氣排序
void arrange_queue(object environment)
{
	int season_term = SEASON_DATA[season][SEASON_ELEMENT];
	int temperature_term = flag_temperature(nature[environment][TEMPERATURE]);
	int humidity_term = nature[environment][HUMIDITY];
	int wind_term = nature[environment][WIND];
	string weather_msg;

	array fit_weather;

	fit_weather = filter_array(ALL_WEATHER, (: 
		($(season_term) & $1[WEATHER_OCCUR_TERM]) &&
		($(temperature_term) & $1[WEATHER_OCCUR_TERM]) &&
		($(humidity_term) & $1[WEATHER_OCCUR_TERM]) &&
		($(wind_term) & $1[WEATHER_OCCUR_TERM]) :));

	// 若沒有任何一項符合
	if( !sizeof(fit_weather) )
		fit_weather = ({ WEATHER_CLOUDY });

	nature[environment][CURRENT_WEATHER] = probability(allocate_mapping(fit_weather, map(fit_weather, (: $1[WEATHER_PROBABILITY] :))));
	nature[environment][NEXTTIME_ARRANGE] = hour_plus(probability(nature[environment][CURRENT_WEATHER][WEATHER_HOLDTIME_TERM]));
	
	switch(nature[environment][CURRENT_WEATHER][WEATHER_ID])
	{
		case SUNNY: 	weather_msg = HIC"\n    ∫"NOR CYN"數朵白雲在天空上緩緩飄著，相當清爽。"NOR; break;
		case CLOUDY: 	weather_msg = HIW"\n    ∫"NOR WHT"天空佈滿著烏雲，一幅風雨欲來的樣子。"NOR; break;
		case RAINY: 	weather_msg = HIW"\n    ∫"NOR WHT"滴答聲逐漸傳了開來，開始下起了棉棉細雨。"NOR; break;
		case WINDY: 	weather_msg = HIY"\n    ∫"NOR YEL"大地開始刮起了強風，帶起來的沙塵幾乎使人睜不開眼睛。"NOR; break;
		case SNOWY: 	weather_msg = WHT"\n    ∫"NOR HIW"凜冽的寒風中，晶瑩剔透的白雪緩緩從天上飄落"NOR; break;
		case SHOWER: 	weather_msg = HIW"\n    ∫"NOR WHT"「轟隆轟隆」的雷雨聲，驚醒了大地上的萬物。"NOR; break;
		case TYPHOON: 	weather_msg = HIG"\n    ∫"NOR GRN"颱風夾帶著豪雨襲擊而來，萬物被摧殘得支離破碎。"NOR; break;
		case FOEHN: 	weather_msg = HIY"\n    ∫"NOR YEL"焚風夾帶著高溫，所經之處變得一片死寂。"NOR; break;
	}
	
	filter_array(all_inventory(environment), (: userp($1) :))->catch_tell(weather_msg+"\n\n");
}

// 啟動自然環境效應
void activate_nature(object environment)
{
	if( !objectp(environment) )
		error("NATURE_D activate_nature() arg 1 error.");

	nature[environment] = allocate_mapping(0);
	
	nature[environment][CURRENT_DISASTER] = allocate(5);

	// 天氣事件
	nature[environment][EVENT] = query("nature_event", environment);

	// 初始化溫度
	nature[environment][TEMPERATURE] = range_random(SEASON_DATA[season][SEASON_TEMPERATURE_LOW], SEASON_DATA[season][SEASON_TEMPERATURE_HIGH]);

	// 初始化濕度
	nature[environment][HUMIDITY] = probability(HUMIDITY_PROBABILITY[season]);

	// 初始化風速
	nature[environment][WIND] = probability(WIND_PROBABILITY[season]);

	// 安排天氣排序
	arrange_queue(environment);
}

// 終止自然環境效應
void deactivate_nature(object environment)
{
	map_delete(nature, environment);
}


// 取得目前自然環境情形
varargs array query_nature(object environment)
{
	if( undefinedp(environment) || undefinedp(nature[environment]) )
		return copy(nature);
	
	return ({ nature[environment][CURRENT_WEATHER], 
		nature[environment][CURRENT_DISASTER],
		nature[environment][TEMPERATURE],
		nature[environment][HUMIDITY],
		nature[environment][WIND] });
}

void game_month_process()
{
	array gametime = TIME_D->query_gametime_array();
	
	/* 季節變換時更新天氣資料 */
	switch( gametime[MON] )
	{
		case 2:
			shout(HIC"\n    ∫春"NOR CYN"天來了，花香緩緩飄散了過來......。\n"NOR);
			break;
		case 5:
			shout(HIR"\n    ∫夏"NOR RED"天到了，氣溫偷偷地升高了......。\n"NOR);
			break;
		case 8:
			shout(HIY"\n    ∫秋"NOR YEL"天來了，一陣涼意緩緩襲來......。\n"NOR);
			break;
		case 10:
			shout(HIY"\n    ∫"NOR YEL"不知不覺已然進入了深秋......。\n"NOR);
			break;
		case 11:
			shout(HIW"\n    ∫冬"NOR WHT"天到了，大地寂靜無聲......。\n"NOR);
			break;
		default:return;
	}
}

// 由 TIME_D 呼叫, 每遊戲小時呼叫一次(實際時間 2.5 分鐘)
void game_hour_process()
{
	array gametime = TIME_D->query_gametime_array();

	season = TIME_D->season_period(gametime[MON]);
	hour = gametime[HOUR];

	// 顯示太陽升起
	if( SEASON_DATA[season][SEASON_SUNRISE_HOUR] == hour )
		shout(HIC"\n    ∫"NOR CYN"朝陽緩緩由東方升起...\n\n"NOR);

	// 顯示太陽落下
	else if( SEASON_DATA[season][SEASON_SUNSET_HOUR] == hour )
		shout(HIY"\n    ∫"NOR YEL"夕陽緩緩由西方落下...\n\n"NOR);


	foreach( object environment, mapping data in nature )
	{
		if( !objectp(environment) )
		{
			nature[environment] = 0;
			continue;
		}

		// 微調溫度
		if( hour >= 5 && hour <= 16 ) 
			nature[environment][TEMPERATURE] += range_random(-1, 2);
		else
			nature[environment][TEMPERATURE] += range_random(-2, 1);

		if( nature[environment][TEMPERATURE] > 38 )
			nature[environment][TEMPERATURE] = 38;
		else if( nature[environment][TEMPERATURE] < -2 )
			nature[environment][TEMPERATURE] = -2;
	
		// 微調濕度
		nature[environment][HUMIDITY] = probability(HUMIDITY_PROBABILITY[season]);

		// 微調風速
		nature[environment][WIND] = probability(WIND_PROBABILITY[season]);

		if( --nature[environment][NEXTTIME_ARRANGE] <= 0 )
			arrange_queue(environment);

/*
		CHANNEL_D->channel_broadcast("sys", file_name(environment)+" 持續時間："+data[NEXTTIME_ARRANGE]+" 天氣："+nature[environment][CURRENT_WEATHER][WEATHER_CHINESE]+" 溫度："+query_current_temperature(environment)+" 水氣："+nature[environment][HUMIDITY]+" 風速："+nature[environment][WIND]);

		foreach( array disaster in nature[environment][CURRENT_WEATHER][WEATHER_RELATED_DISASTER] )
		{
			
			CHANNEL_D->channel_broadcast("sys", "引發"+disaster[0]+"機率："+
			    ((disaster[DISASTER_OCCUR_TERM] & nature[environment][HUMIDITY])&&
			    (disaster[DISASTER_OCCUR_TERM] & flag_temperature(nature[environment][TEMPERATURE]))&&
			    (disaster[DISASTER_OCCUR_TERM] & nature[environment][WIND]) ? range_random(disaster[DISASTER_OCCUR_PROB]-10,disaster[DISASTER_OCCUR_PROB]+10) +"/1000" : "不會發生"));
		}
*/
	}
}

void debug()
{
	printf("%O\n", nature);
}

void create()
{
	nature = allocate_mapping(0);

	game_hour_process();

	// 啟動所有 maproom 自然行為
	foreach( object environment in MAP_D->query_all_maproom() )
	{
		if( query("no_weather", environment) ) 
			continue;

		activate_nature(environment);
	}
}
string query_name()
{
	return "自然環境系統(NATURE_D)";
}
