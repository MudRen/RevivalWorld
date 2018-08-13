/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : enterprise.c
 * Author : Clode@RevivalWorld
 * Date   : 2006-02-08
 * Note   : ¥ø·~¸¹
 * Update :
 *  o 2000-00-00
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <inherit.h>
#include <feature.h>
#include <equipment.h>
#include <buff.h>
#include <daemon.h>
#include <secure.h>
#include <map.h>
#include <location.h>

inherit STANDARD_OBJECT;
inherit EQUIPMENT;

mapping actions;

void fire_process(object me, object target, int combo, int sec)
{
	if( sec == 0 )
	{
		int damage, faint;
		for(int i=0;i<combo;i++)
		{
			damage = range_random(1, 125);
			
			if( !target->cost_health(damage) )
				faint = 1;
			
			msg("$YOU³Q$MEµo®gªº 12 «¬¥ú¬¶°}¦CÀ»¤¤¡A¾É­P "HIR+damage+NOR" ªº¥Í©R¶Ë®`("NOR GRN+target->query_health_cur()+NOR"/"HIG+target->query_health_max()+NOR")¡C\n", me, target, 1);

			if( faint )
				target->faint();
		}
		
		delete_temp("delay/fire");
	}
	else
	{
		msg("¶ZÂ÷ 12 «¬¥ú¬¶°}¦CÀ»¤¤$YOUÁÙ¦³ "+sec+" ¬íÄÁ...\n", me, target, 1);
		call_out((: fire_process, me, target, combo, sec-1 :), 1);
	}
}

void fire(object me, string arg)
{
	int combo = random(11)+1;
	object target = find_player(arg) || present(arg);
	
	if( !me->is_equipping_object(this_object()) )
		return tell(me, pnoun(2, me)+"¥²¶·¥ý¸Ë³Æ"+this_object()->query_idname()+"¡C\n");

	if( query_temp("delay/fire") > time() )
		return tell(me, "¦¹ªZ¾¹µLªk³sÄòµo®g¡A½Ðµ¥«ÝªZ¾¹¨t²Î§N«o¡C\n");

	if( !objectp(target) )
		return tell(me, "¨S¦³ "+arg+" ³o­Ó¤H¡C\n");
	
	for(int i=0;i<combo;i++)
	msg("$ME¾ÞÁa"+this_object()->query_idname()+"¹ïµÛ$YOUµo®g 12 «¬¥ú¬¶°}¦C("HIY+combo+NOR YEL" ³sµo"NOR")¡C\n", me, target, 1);
	set_temp("delay/fire", time() + 5);
	call_out((: fire_process, me, target, combo, 5 :), 1);
}

void shield(object me, string arg)
{
	if( !me->is_equipping_object(this_object()) )
		return tell(me, pnoun(2, me)+"¥²¶·¥ý¸Ë³Æ"+this_object()->query_idname()+"¡C\n");

	if( !query_temp("shield/on") )
	{
		msg("$ME±Ò°Ê"+this_object()->query_idname()+"¦Û°Ê½ÕÀW¨¾Å@¸n¨t²Î¡C\n", me, 0, 1);
		set_temp("status", HIR"(¨¾Å@¸n)"NOR);
		set_temp("shield/on", 1);
	}
	else
	{
		msg("$MEÃö³¬"+this_object()->query_idname()+"¦Û°Ê½ÕÀW¨¾Å@¸n¨t²Î¡C\n", me, 0, 1);
		delete_temp("status");
		delete_temp("shield/on");
	}
}

void antimatter_process(object me, object target, int sec)
{
	if( sec == 0 )
	{
		msg("$YOU³Q$ME©Ò±Ò°Êªº¤Ïª«½è´²¥¬¤f¹ý©³·´·À¡A¾É­P "HIR+1000000+NOR" ªº¥Í©R¶Ë®`("NOR RED+"-1000000"+NOR"/"HIG+target->query_health_max()+NOR")¡C\n", me, target, 1);

		target->faint();
		
		if( userp(target) )
		LOGOUT_D->quit(target);
		
		delete_temp("delay/antimatter");
	}
	else
	{
		msg("¶ZÂ÷¤Ïª«½è´²¥¬¤f»E¶°¯à¶q§¹¦¨ÁÙ¦³ "+sec+" ¬íÄÁ...\n", me, target, 1);
		call_out((: antimatter_process, me, target, sec-10 :), 10);
	}
}

// ¤Ïª«½è´²¥¬¤f
void antimatter(object me, string arg)
{
	object target = find_player(arg) || present(arg);
	
	if( !me->is_equipping_object(this_object()) )
		return tell(me, pnoun(2, me)+"¥²¶·¥ý¸Ë³Æ"+this_object()->query_idname()+"¡C\n");

	if( query_temp("delay/antimatter") > time() )
		return tell(me, "¦¹ªZ¾¹µLªk³sÄòµo®g¡A½Ðµ¥«ÝªZ¾¹¨t²Î§N«o¡C\n");

	if( !objectp(target) )
		return tell(me, "¨S¦³ "+arg+" ³o­Ó¤H¡C\n");
		
	msg("$ME¾ÞÁa"+this_object()->query_idname()+"¹ïµÛ$YOU¶}±Ò¤Ïª«½è´²¥¬¤f¡C\n", me, target, 1);
	set_temp("delay/antimatter", time() + 60);
	call_out((: antimatter_process, me, target, 60 :), 1);
}

void create()
{
	set_idname(HIW"enter"WHT"prise"NOR, HIW"¥ø"WHT"·~¸¹");
	set_temp("status", HIY"µ´"NOR YEL"ª©");

	actions = ([
		"fire" : (: fire :),
		"shield" : (: shield :),
		"antimatter": (: antimatter :),
	]);

	if( this_object()->set_shadow_ob() ) return;
	
	set("long", @LONG
  °t³Æ¶W¥ú³t­¸¦æªº¦±³t¤ÞÀº¤§¬P»Ú¾ÔÅ²¡A¾Ö¦³¹ý©³·´·À¹ï¤âªº¯à¤O
  
    ªZ¸Ë
      11 ±ø 12 «¬¥ú¬¶°}¦C¡AÁ`¿é¥X¶q¬° 8 ¸U 5 ¤d¥ü¥Ë
      1 ­Ó°ª³t¶q¤l³½¹pºÞ¡A¸Ë³Æ 50 ªT¶q¤l³½¹p
      4 ­Ó 4 «¬³sµo¦¡¥ú¹pºÞ¡AÁ`¦@¸Ë³Æ¦³ 250 ªT¥ú¹p
      ¤Ïª«½è´²¥¬¤f¡C
  
    ¨¾¿m
      ¦Û°Ê½ÕÀW¨¾Å@¸n¨t²Î¡AÁ`®e¶q¬° 459 ¸U¥üµJ
      ­««¬¤G«×½Æ¦X±KÂë¿û»P¤T«×½Æ¦X±KÂë¿ûÂù¼h¥~´ß¡A¥[¤W 10 Íù¦Ìªº§Ü¿N»k¸Ë¥Ò
      °ª¯Åµ²ºc«OÅ@¬Þ¡C 
  
    ¦±³t¯à¤O
      ¥¿±`¨µ¯è¦±³t 8 ¯Å
      ¥þ³t¨µ¯è¦±³t 9.9 ¯Å
      ³Ì¤j¯à¤O¬O¥H¦±³t 9.99 ¯è¦æ 24 ¤p®É¡C   
   
    ¦±³t¹ï·Óªí
    ¦±³t(¯Å)     ¥ú³t(¨C³æ¦ì 299,792,458 ¤½¤Ø/¬í)
    [1;37m1            [1;30m1
    [1;37m2            [1;30m8
    [1;37m3            [1;30m27
    [1;37m4            [1;30m64
    [1;37m5            [1;30m125
    [1;37m6            [1;30m216
    [1;37m7            [1;30m343
    [1;37m8            [1;30m512
    [1;37m9            [1;30m729      
    [1;37m10           [1;30m1000
    [1;37m11           [1;30m1331
    [1;37m12           [1;30m1728
    [1;37m13           [1;30m2197
    [1;37m14.1         [1;30m2803.221  [0m
LONG
	);

	set("unit", "¿´");
	set("mass", 0);
	set("value", 0);
	set("flag/no_amount", 1);

	set(BUFF_STR, 100);
	set(BUFF_PHY, 100);
	set(BUFF_INT, 100);
	set(BUFF_AGI, 100);
	set(BUFF_CHA, 100);

	set(BUFF_STAMINA_MAX, 100);
	set(BUFF_HEALTH_MAX, 100);
	set(BUFF_ENERGY_MAX, 100);
	
	set(BUFF_STAMINA_REGEN, 100);
	set(BUFF_HEALTH_REGEN, 100);
	set(BUFF_ENERGY_REGEN, 100);

	set(BUFF_LOADING_MAX, 100);
	set(BUFF_FOOD_MAX, 100);
	set(BUFF_DRINK_MAX, 100);
	
	set(BUFF_SOCIAL_EXP_BONUS, 100);

	set("buff/status", HIW"¥ø"WHT"·~¸¹");
	
	::setup_equipment(EQ_MOUNT, HIG"¾r"NOR GRN"¾p"NOR);
}
