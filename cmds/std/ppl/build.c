/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : build
 * Author : Cookys@RevivalWorld
 * Date   : 2001-06-19
 * Note   : (¤@¯ëª±®a)¦a¹Ï½s¿è«ü¥O, ¥u¯à«Ø³yÀð¾À»P¤@¨Ç¤p´ºÆ[¡C
 * Update :
 *  o 2001-07-09 Clode §ï¼g«ü¥O edit_map ¦¨¬° build
 *
 -----------------------------------------
 */

#include <map.h>
#include <ansi.h>
#include <daemon.h>
#include <feature.h>
#include <material.h>
#include <location.h>
#include <message.h>

#define ICON_ELEM		0
#define NAME_ELEM		1
#define MTR_ELEM		2

inherit COMMAND;


string list = @LIST
¢z¢w¢s¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{
¡UÀð¡U¢ß¢å¢Ó  ¢~¢w¢¡ ùæùùùè ùï¢wùñ ¢z¢w¢{ ùÝùùùß  6. ª½ªù  ¡ü ¡U
¡U  ¡U¢Ï  ¢Ò  ¢x¢°¢x ¢x¢±¢x ùø¢²ùø ¢x¢³¢x ùø¢´ùø  	      ¡U
¡U¾À¡U¢è¢æ¢Ñ  ¢¢¢w¢£ ùìùùùî ùõ¢wù÷ ¢|¢w¢} ùãùùùå  7. ¾îªù  ¡× ¡U
¢u¢w¢q¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t
¡U´º¡U10. ¸ô¿O   [1;33m£F[m       11. ¤ô¦À   [1;36m¡ó[m        12. ²D«F   [1;37m¡¸[m  ¡U
¡U  ¡U13. ¤j¾ð   [1;32m¢D[m       14. ¯ó¥Ö   [0;32m£s[m        15. ÀJ¹³   [1;35m¢Ç[m  ¡U
¡UÆ[¡U                                                        ¡U
¢u¢w¢q¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢t
¡U¨ä¡U50. ¹A¥Ð   [1;32;42m¡²[m       51. ªª³õ   [1;33;43m¡²[m        52. ¾i´Þ³õ [1;34;44m¡²[m  ¡U
¡U  ¡U                                                        ¡U
¡U¥L¡U                                                        ¡U
¢|¢w¢r¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}
 («Ø¿v¤¤¥i²¾°Ê)       ls. ¦C¥X¦¹ªí   er. ©î°£«Ø¿v  lv. §¹²¦Â÷¶}
LIST;

string help = @HELP

[0m
[0m «Ø³y«ü¥O                                                             [build]
[0mùÝùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùß
[0m      ·í§A¸g¥Ñ¨Ï¥Î¤g¦a©Ò¦³Åvª¬¦Ó»{»â¡A©ÎªÌ¬O¥Ñ¦Û¤v¨¯­WÁÈ¨Óªºª÷¿ú¶R¤U¤F¤@¶ôÄÝ
[0m  ©ó¦Û¤vªº¤g¦a¡C¦pªG§A¤£¦b¤W­±«Ø³y¨Ç¤°»òªº¸Ü¡A¨º¶ô¦a¥Ã»·³£¥u¬O¤@­Ó³æ¯ÂªºªÅ¦a
[0m  ¡CµL½×§A¬O­nºØ¥Ð©ÎªÌ¬O¶}©±¡A¤@©w³£±o«Ø³y¤~¥i¤@¨B¨B¹F¦¨§A­nªº¥Øªº¡C
[0m
[0m      ¥´¤U[33;1mbuild[0m«ü¥O¤§«á«K¶i¤J«Ø¿v¼Ò¦¡¡A·|¥X²{¦p¤Uµe­±¡G

HELP + list + @HELP

[0m  ¡DÀð¾À¡G
[0m¡@¡@¡@[36;1m¢ß¢å¢Ó¢Ï¢Ò¢è¢æ¢Ñ[0m¬OÀð¾À¤è¦ì¡C
[0m
[0m        [36;1m¢ß[0m¡Ð[32;1m¥ª¤W[0mªº[32mÂà¨¤[37m  [36;1m¢å[0m¡Ð[32;1m¾î[0;32m½u[37m  [36;1m¢Ó[0m¡Ð[32;1m¥k¤W[0mªº[32mÂà¨¤
[0m        [36;1m¢Ï[0m¡Ð[32;1mª½[0;32m½u[37m                  [36;1m¢Ò[0m¡Ð[32;1mª½[0;32m½u
[0m        [36;1m¢è[0m¡Ð[32;1m¥ª¤U[0mªº[32mÂà¨¤[37m  [36;1m¢æ[0m¡Ð[32;1m¾î[0;32m½u[37m  [36;1m¢Ñ[0m¡Ð[32;1m¥k¤U[0mªº[32mÂà¨¤
[0m
[0m      [36;1m¢°¢±¢²¢³¢´[0m¬OÀð¾Àªº¼Ë¦¡¡A¦b´£¥Ü¤W¤w¦³©úÅã»¡©ú¹Ï¥Ü¤F¡C¤è¦ì¥²¶·­n»P¼Ë¦¡°t
[0m      ¦X¬°¤@²Õ¡A¤è¯à«Ø³y¡C
[0m
[0m      [36;1m¢µ[0m©M[36;1m¢¶[0m«h¬Oªùªº¤è¦V¡A¥u¶·«Ø¤J¡u[36;1m¢µ[0m¡v©Î¡u[36;1m¢¶[0m¡v´N¥i¥H«Ø³y¤F¡C
[0m
[0m      ¥t¥~¡A­YµL«ü©w«Ø§÷«h·|«Ø³y¥X¡u[32m¥Ù¯ó[37m¡v§÷½èªºÀð¾À¡C
[0m      ¨Ï¥Î«Ø§÷ªº«ü¥O®æ¦¡¡Ð[33;1m2a by stone
[0m¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@[33;1m6 by wood
[0m
[0m[33m      ¬ÛÃö«ü¥O: open
[0m
[0m¡@¡D´ºÆ[¡G
[0m¡@¡@¡@10. ¸ô¿O  [33;1m£F[0m¡Ð¥i¦b´c¦H¤Ñ®ð¤¤´£°ª©P³òªº¯à¨£«×¡A¤@®æ¡C
[0m      11. ¤ô¦À  [36;1m¡ó[0m¡Ð¥i¥Î¨Ó±Ä¶°([33;1mcollect[0m) ¤ô¸ê·½¡A¤@®æ¡C
[0m      12. ²D«F  [1m¡¸[0m¡Ð¥Î¨Ó¥ð®§([33;1msit[0m) ¡A®ÄªG³Ì¨Î¡A¤@®æ¡C
[0m      13. ¤j¾ð  [32;1m¢D[0m¡Ð¥Î¨Ó¥ð®§([33;1msit[0m) ¡A®ÄªG´¶³q¡A¤@®æ¡C
[0m      14. ¯ó¥Ö  [32m£s[37m¡Ð¥Î¨Ó¥ð®§([33;1msit[0m) ¡A®ÄªG²¤®t¡A¤@®æ¡C
[0m      15. ÀJ¹³  [35;1m¢Ç[0m¡Ð¨ã¦³¯«©_Å]¤O¡A¥i«O¯§¥|©Pªº¹A¥Ð¡A¨Ï¤Ñ¨a©Ò³y¦¨ªº·l¥¢­°¨ì³Ì
[0m                  §C¡C
[0m
[0m[33m      ¬ÛÃö«ü¥O: collect, sit
[0m
[0m  ¡D¨ä¥L¡G
[0m      50. «Ø³y¹A¥Ð¡u[32;42;1m¡²[0m¡v
[0m      51. «Ø³yªª³õ¡u[33;43;1m¡²[0m¡v
[0m      52. «Ø³y¾i´Þ³õ¡u[34;44;1m¡²[0m¡v
[0m
[0m[33m      ¬ÛÃö«ü¥O: grow
[0m
[0m    [33;1mls[0m¡Ð¦C¥X«Ø¿v´£¥Ü¹Ï¡C
[0m    [33;1mer[0m¡Ð±N¦¹®æ«Ø¿v©î°£¡A¤~¥i¥H½æ¥X©Î«Ø³y¨ä¥L«Ø¿vª«¡C
[0m    [33;1mlv[0m¡ÐÂ÷¶}«Ø¿v¼Ò¦¡¡C
[0m
[0m[33m      ¬ÛÃö«ü¥O: sell here
[0mùãùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùùå
[0m                                                            ¤å¥ó«ùÄò§ó·sºûÅ@¤¤[0m
HELP;

mapping wall_type = ([
"q"	:	0,
"e"	:	1,
"z"	:	2,
"c"	:	3,
"w"	:	4,
"x"	:	4,
"a"	:	5,
"d"	:	5,
]);

mapping walls = ([
1	:	({ "¢~","¢¡","¢¢","¢£","¢w","¢x" }),
2	:	({ "ùæ","ùè","ùì","ùî","ùù","¢x" }),
3	:	({ "ùï","ùñ","ùõ","ù÷","¢w","ùø" }),
4	:	({ "¢z","¢{","¢|","¢}","¢w","¢x" }),
5	:	({ "ùÝ","ùß","ùã","ùå","ùù","ùø" }),
]);

mapping doors = ([
6	:	({ "¡ü", 	"ª½ªù" }),
7	:	({ "¡×", 	"¾îªù" }),
]);

mapping sceneries = ([
10	:	({ HIY"£F"NOR, 		"¸ô¿O", ([METAL	:20, STONE:10, WOOD:5	]) }),
11	:	({ HIC"¡ó"NOR, 		"¤ô¦À", ([WATER	:50, STONE:20		]) }),
12	:	({ HIW"¡¸"NOR, 		"²D«F", ([WOOD	:15, STONE:15		]) }),
13	:	({ HIG"¢D"NOR, 		"¤j¾ð", ([WATER	:30, WOOD:20		]) }),
14	:	({ NOR GRN"£s"NOR, 	"¯ó¥Ö", ([WATER	:15, WOOD:10		]) }),
15	:	({ HIM"¢Ç"NOR, 		"ÀJ¹³", ([STONE	:40, METAL:20		]) }),
]);

mapping others = ([
50	:	({ HIG BGRN"¡²"NOR,	"¹A¥Ð",	([WOOD:20			]) }),
51	:	({ HIY BYEL"¡²"NOR,	"ªª³õ",	([WOOD:20			]) }),
52	:	({ HIB BBLU"¡²"NOR,	"¾i´Þ³õ",([WOOD:20			]) }),
]);
void select_icon(object me, string arg);


void do_build(object me, object material, array building_info, int type)
{

	int str_cost;
	int num;
	string mtr_name;
	mapping mtr_exerted = allocate_mapping(0);
	mapping mtr_ingredient;
	array loc = query_temp("location", me);


	if( CITY_D->query_coor_data(loc, TYPE) )
	{
		tell(me, "³o¶ô¤g¦a¤W¤w¸g¦³«Øª«¤F¡AµLªk¦A¦¸«Ø³y¡A°£«D"+pnoun(2, me)+"¥ý©î°£±¼²{¦³ªº«Øª«¡C\n");
		tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
		input_to((: select_icon, me :));
		return;
	}

	if( !objectp(material) )
	{
		if( !mapp(building_info[MTR_ELEM]) )
		{
			if( !me->cost_stamina(300) )
			{
				tell(me, "\n"+pnoun(2, me)+"¤w¸g¨S¦³Åé¤O«Ø³yªF¦è¤F¡C\n");
				return me->finish_input();
			}
			
			CITY_D->set_coor_data(loc, TYPE, type);
			CITY_D->set_coor_icon(loc, building_info[ICON_ELEM]);
		
			// §R°£ material ¸ê°T
			CITY_D->delete_coor_data(loc, "material");

			tell(me, "¯Ó¶O¤F 300 ÂIÅé¤O¡A"HIG"["+me->query_stamina_cur()+"/"+me->query_stamina_max()+"]"NOR"¡C\n");
			msg("$ME¦¨¥\¦a¦b³o¶ô¤g¦a¤W«Ø³y¤F¡u"+building_info[NAME_ELEM]+" "+building_info[ICON_ELEM]+"¡v¡C\n",me,0,1);
			me->add_social_exp(30+random(51));
			
			tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
			input_to((: select_icon, me :));
			return;
		}
		else
		{
			foreach( mtr_name, num in building_info[MTR_ELEM] )
				mtr_exerted[mtr_name] = CITY_D->query_coor_data(loc, "material/"+mtr_name);
	
			tell(me, "§÷®Æ¤£¨¬¡A«Ø³y¡u"+building_info[NAME_ELEM]+" "+building_info[ICON_ELEM]+"¡v»Ý­n"+MATERIAL_D->material_required_info(building_info[MTR_ELEM])+"¡A¥Ø«e§¹¦¨«× "+MATERIAL_D->material_percentage(building_info[MTR_ELEM], mtr_exerted)+"¡C\n\n");
			return me->finish_input();
		}
	}
	else
		mtr_ingredient = query("material", material);

	if( !mapp(mtr_ingredient) )
	{
		tell(me, material->query_idname()+"¤w¸g·lÃa¤F¡C\n");
		return me->finish_input();
	}

	if( sizeof(keys(mtr_ingredient) - keys(building_info[MTR_ELEM])) == sizeof(keys(mtr_ingredient)) )
	{
		tell(me, material->query_idname()+"¤£¾A¦X¥Î¨Ó«Ø³y¦¹«Ø¿vª«¡C\n");
		return me->finish_input();
	}
		
	foreach( mtr_name, num in building_info[MTR_ELEM] )
	{
		if( !me->cost_stamina(mtr_ingredient[mtr_name]*50) )
		{
			tell(me, "\n"+pnoun(2, me)+"¤w¸g¨S¦³Åé¤O«Ø³yªF¦è¤F¡C\n");
			return me->finish_input();
		}
		
		mtr_exerted[mtr_name] = CITY_D->add_coor_data(loc, "material/"+mtr_name, mtr_ingredient[mtr_name]);

		// ¨C³æ¦ìªº§÷®Æ·|¯Ó¶O 50 ÂIÅé¤O
		str_cost += mtr_ingredient[mtr_name]*50;
	}

	tell(me, "¯Ó¶O¤F "+str_cost+" ÂIÅé¤O¡A"HIG"["+me->query_stamina_cur()+"/"+me->query_stamina_max()+"]"NOR"¡C\n");

	me->add_social_exp(str_cost/10+random(31));
	msg("$ME§Q¥Î"+material->query_idname()+"§@¬°§÷®Æ¦b³o¶ô¤g¦a¤W«Ø³y¡u"+building_info[NAME_ELEM]+" "+building_info[ICON_ELEM]+"¡v¡A¥Ø«e¤w§¹¦¨¡G"+MATERIAL_D->material_percentage(building_info[MTR_ELEM], mtr_exerted)+"¡C\n",me,0,1);
	
	destruct(material ,1);

	if( MATERIAL_D->is_accomplished(building_info[MTR_ELEM], mtr_exerted) )
	{
		msg("\n$ME©Ò«Ø³yªº¡u"+building_info[NAME_ELEM]+" "+building_info[ICON_ELEM]+"¡v§¹¤u¤F¡A½Ð¤j®a©ç¤â¹ªÀy¹ªÀy¡I\n", me, 0, 1);

		BUILDING_D->materialize_outdoor_building(me, CITY_D->query_coor_data(loc, "owner"), loc, building_info[ICON_ELEM], building_info[NAME_ELEM], type);	
		
		me->finish_input();
		return;
	}

	tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
	input_to((: select_icon, me :));
	return;
}

// «Ø¿vÀð¾À
void build_wall(object me, object material, int choice, int wall_type)
{
	if( !objectp(material) )
		do_build(me, material, ({ GRN+walls[choice][wall_type]+NOR, "­T¯óÀð¾À", 0}), WALL );
	else
	{
		mapping mtr_ingredient = query("material", material);
		
		if( mapp(mtr_ingredient) && mtr_ingredient[WOOD] )
			do_build(me, material, ({ NOR YEL+walls[choice][wall_type]+NOR, "¤ìªOÀð¾À", ([ WOOD : 10 ]) }), WALL );
		else if( mapp(mtr_ingredient) && mtr_ingredient[STONE] )
			do_build(me, material, ({ NOR +walls[choice][wall_type]+NOR, "¥Û§÷Àð¾À", ([ STONE : 30 ]) }), WALL );
		else
		{
			tell(me, material->query_idname()+"¨Ã¤£¾A¦X§@¬°Àð¾Àªº«Ø§÷¡C\n\n");
			me->finish_input();
		}
	}
}

// «Ø¿v¤jªù
void build_door(object me, object material, int choice)
{
	if( !objectp(material) )
		do_build(me, material, ({ GRN+doors[choice][0]+NOR, doors[choice][1], 0}), DOOR );
	else
	{
		mapping mtr_ingredient = query("material", material);

		if( mapp(mtr_ingredient) && mtr_ingredient[WOOD] )
			do_build(me, material, ({ NOR YEL+doors[choice][0]+NOR, doors[choice][1], ([ WOOD : 10 ]) }), DOOR );
		else if( mapp(mtr_ingredient) && mtr_ingredient[STONE] )
			do_build(me, material, ({ NOR +doors[choice][0]+NOR, doors[choice][1], ([ STONE : 30 ]) }), DOOR );
		else
		{
			tell(me, material->query_idname()+"¨Ã¤£¾A¦X§@¬°ªùªº«Ø§÷¡C\n\n");
			me->finish_input();
		}
	}
}

// «Ø¿v´ºÆ[
void build_scenery(object me, object material, int choice)
{
	string my_id = me->query_id(1);
	string loc_owner = CITY_D->query_coor_data(query_temp("location", me), "owner");

	// ¸ô¿O¥u¦³¬F©²¯à»\
	if( choice == 10 )
	{
		if( !belong_to_government(loc_owner) )
			return tell(me, "³oºØ´ºÆ[¥u¯à«Ø³y¦b¬F©²¤g¦a¤W¡C\n");
	}
	else if( loc_owner != my_id && !ENTERPRISE_D->same_enterprise(loc_owner, my_id) )
	{
		tell(me, "³o¶ô¦a¤£¯à«Ø³y³oÃþªº´ºÆ[¡C\n");
		return me->finish_input();
	}

	switch(choice)
	{
		case 10:
			do_build(me, material, sceneries[choice], LIGHT);
			break;
		case 11:
			do_build(me, material, sceneries[choice], POOL);
			break;
		case 12:
			do_build(me, material, sceneries[choice], PAVILION);
			break;
		case 13:
			do_build(me, material, sceneries[choice], TREE);
			break;
		case 14:
			do_build(me, material, sceneries[choice], GRASS);
			break;
		case 15:
			do_build(me, material, sceneries[choice], STATUE);
			break;
		default:
			tell(me, list+"\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
			input_to((: select_icon, me :));
			return;
	}
			
}

// «Ø³y¨ä¥L¯S®í«Ø¿v
void build_other(object me, object material, int choice)
{
	string my_id = me->query_id(1);
	string loc_owner = CITY_D->query_coor_data(query_temp("location", me), "owner");

	if( loc_owner != my_id && !ENTERPRISE_D->same_enterprise(loc_owner, my_id) )
	{
		tell(me, "³o¶ô¦a¤£¯à«Ø³y³oÃþªº«Ø¿vª«¡C\n");
		return me->finish_input();
	}
	
	switch(choice)
	{
		// ¹A¥Ð
		case 50:
			if( !(CITY_D->query_coor_data(query_temp("location", me), "region") & AGRICULTURE_REGION) )
				return tell(me, "¦¹¦a¨Ã¤£¬O¹A·~°Ï¡AµLªk«Ø³y¹A¥Ð¡C\n");

			do_build(me, material, others[choice], FARM);
			return;
		// ªª³õ
		case 51:
			if( !(CITY_D->query_coor_data(query_temp("location", me), "region") & AGRICULTURE_REGION) )
				return tell(me, "¦¹¦a¨Ã¤£¬O¹A·~°Ï¡AµLªk«Ø³yªª³õ¡C\n");

			do_build(me, material, others[choice], PASTURE);
			return;
		// ¾i´Þ³õ
		case 52:
			if( !(CITY_D->query_coor_data(query_temp("location", me), "region") & AGRICULTURE_REGION) )
				return tell(me, "¦¹¦a¨Ã¤£¬O¹A·~°Ï¡AµLªk«Ø³y¾i´Þ³õ¡C\n");

			do_build(me, material, others[choice], FISHFARM);
			return;
		default:
			tell(me, list+"\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
			input_to((: select_icon, me :));
			return;
	}
}
		
		

void clean_build(object me)
{
	array loc = query_temp("location", me);
	
	if( !CITY_D->query_coor_data(loc, TYPE) )
	{
		tell(me, "³o¶ô¤g¦a¤W¨Ã¨S¦³¥ô¦ó«Ø¿v¡A¤£»Ý­n©î°£¡C\n");
		
		return me->finish_input();
	}

	if( !me->cost_stamina(300) )
	{
		tell(me, pnoun(2, me)+"¤w¸g®ð³Ý¼N¼N¡A¨S¦³Åé¤O©î°£³o¨ÇªF¦è¤F¡C\n");
		return me->finish_input();
	}

	msg("$ME±N«Ø³y¦nªº¡u"+CITY_D->query_coor_icon(loc)+"¡v©î°£±¼¤F¡C\n", me, 0, 1);
	tell(me, "¯Ó¶O¤F 300 ÂIÅé¤O¡A"HIG"["+me->query_stamina_cur()+"/"+me->query_stamina_max()+"]"NOR"¡C\n");

	CITY_D->delete_coor_data(loc, "growth");
	CITY_D->delete_coor_data(loc, "status");
	CITY_D->delete_coor_data(loc, TYPE);
	CITY_D->set_coor_icon(loc, BWHT"¡¼"NOR);
	
	ESTATE_D->set_land_estate(CITY_D->query_coor_data(loc, "owner"), loc);
	
	tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
	input_to((: select_icon, me  :));
	return;
}

mapping move_string = ([
    "n":        "north",
    "e":        "east",
    "w":        "west",
    "s":        "south",
    "u":        "up",
    "d":        "down",
    "nu":       "northup",
    "eu":       "eastup",
    "wu":       "westup",
    "su":       "southup",
    "nd":       "northdown",
    "ed":       "eastdown",
    "wd":       "westdown",
    "sd":       "southdown",
    "ne":       "northeast",
    "se":       "southeast",
    "nw":       "northwest",
    "sw":       "southwest",
]);
void select_icon(object me, string arg)
{
	int choice;
	string owner;
	array loc = query_temp("location", me);
	
	string material_id;
	object material;

	if( !arg || !arg[0] )
	{
		tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
		input_to((: select_icon, me :));
		return;
	}
	
	if( !arrayp(loc) || !environment(me)->is_maproom() ) 
	{
		tell(me, pnoun(2, me)+"¤£¯à¦b³o¸Ì«Ø³y¥ô¦ó«Ø¿vª«¡C\n");
		return me->finish_input();
	}

	owner = CITY_D->query_coor_data(loc, "owner");
	
	if( !owner ) 
	{
		tell(me, "³o¬O¤@¶ô¤£ÄÝ©ó¥ô¦ó¤Hªº¤g¦a¡A"+pnoun(2, me)+"¥²¶·¥ý¶R¤U³o¶ô¦a¤~¯à¦b¤W­±«Ø³y«Ø¿vª«¡C\n");
		return me->finish_input();
	}

	if( belong_to_government(owner) )
	{
		if( !CITY_D->is_mayor_or_officer(loc[CITY], me) )
		{
			tell(me, "³o¶ô¦a¬O¥«¬F©²¥Î¦a¡A"+pnoun(2, me)+"¨S¦³Åv§Q¦b³o¤W­±«Ø³y¥ô¦óªF¦è¡C\n");
			return me->finish_input();
		}
	}
	else if( belong_to_enterprise(owner) )
	{
		if( owner[11..] != query("enterprise", me) )
		{
			tell(me, pnoun(2, me)+"¤£¬O"+ENTERPRISE_D->query_enterprise_color_id(query("enterprise", me))+"¥ø·~¶°¹Îªº¦¨­û¡AµLªk¦b¦¹«Ø³y¥ô¦óªF¦è¡C\n");
			return me->finish_input();
		}
	}
	else if( owner != me->query_id(1) && !ENTERPRISE_D->same_enterprise(owner, me->query_id(1)) ) 
	{
		tell(me, "³o¶ô¦a¬O "+capitalize(owner)+" ªº¨p¤H¤g¦a¡A"+pnoun(2, me)+"¨S¦³Åv§Q¦b³o¤W­±«Ø³y¥ô¦óªF¦è¡C\n");
		return me->finish_input();
	}

	foreach( string coor, mixed data in CITY_D->query_coor_range(loc, ROOM, 1) )
                if( data )
                {
                        tell(me, pnoun(2, me)+"¥²¶·¥ýÃö³¬³o´É«Ø¿vª«¤~¯à­«·s«Ø³y¡C\n");
                        return me->finish_input();
		}
	
	if( ESTATE_D->query_loc_estate(loc) && ESTATE_D->query_loc_estate(loc)["type"] != "land" )
	{
		tell(me, pnoun(2, me)+"¥²¶·¥ýÃö³¬³o´É«Ø¿vª«¤~¯à­«·s«Ø³y¡C\n");
                return me->finish_input();
	}
		
	arg = lower_case(arg);

	switch(arg)
	{
		case "lv":
		case "leave":
		{
			tell(me, "¨ú®ø«Ø³y°Ê§@¡C\n");
			return me->finish_input();
		}
		case "l":
		case "look":
		{
			tell(me,MAP_D->show_map(query_temp("location", me), 0) || "¦a¹Ï¨t²Î¿ù»~¡A½Ð³qª¾§Å®v³B²z¡C\n");
			tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
			input_to((: select_icon, me :));
			return;
		}
		case "ls":
		case "list":
		{
			tell(me, list+"\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
			input_to((: select_icon, me :));
			return;
		}
		case "er":
		case "erase":
		{
			evaluate((: clean_build, me :));
			return;
		}
	}

	if( sscanf( arg, "%d%s", choice, arg ) != 2 )
	{
		// ¿é¤J¤è¦V«ü¥O ?
		if( member_array(arg, keys(move_string)+values(move_string))!=-1)
		{
			if( member_array(arg, keys(move_string)) != -1 )
				arg = move_string[arg];

			if( MAP_D->valid_move(me, arg) <= 0  )
			{
				tell(me, "µLªk©¹¸Ó¤è¦V«e¶i¡C\n");
				tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
				input_to((:select_icon, me:));
				return;
			}
				
			CITY_D->move(me, arg);
		} 
		
		tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
		input_to((: select_icon, me :));
		return;
	}
	
	// ¸ÑªR§÷®Æª«¥ó
	if( sscanf(arg, "%s by %s", arg, material_id) == 2 )
	{
		if( !objectp(material = present(material_id, me) || present(material_id, environment(me))) )
		{
			tell(me, pnoun(2, me)+"ªºªþªñ¨Ã¨S¦³ "+material_id+" ³o­ÓªF¦è¡C\n");
			tell(me, "\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
			input_to((: select_icon, me :));
			return;
		}
	}

	switch(choice)
	{
		// Àð¾À
		case 1..5:
			if( arg=="" || nullp(wall_type[arg]) )
			{
				tell(me, "\n¿é¤J¥¿½Tªº¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
				input_to((: select_icon, me :));
				return;
			}
			evaluate((: build_wall, me, material, choice, wall_type[arg] :));
			break;
		// ªù
		case 6..7:
			evaluate((: build_door, me, material, choice :));
			break;
		// ´ºÆ[¹w¯d½d³ò
		case 10..49:
			evaluate((: build_scenery, me, material, choice :));
			break;
		// ¨ä¥L«Ø¿v¹w¯d½d³ò
		case 50..99:
			evaluate((: build_other, me, material, choice :));
			break;

		default:
			tell(me, list+"\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");
			input_to((: select_icon, me :));
			return;
	}
}

private void do_command(object me, string arg)
{
	string owner;
	array loc = query_temp("location", me);

	if( !arrayp(loc) || !CITY_D->is_city_location(loc) )
		return tell(me, pnoun(2, me)+"¥u¯à¦b«°¥«¦a¹Ï¤¤«Ø³y«Ø¿vª«¡C\n");

	owner = CITY_D->query_coor_data(loc, "owner");
	
	if( !owner ) 
		return tell(me, "³o¬O¤@¶ô¤£ÄÝ©ó¥ô¦ó¤Hªº¤g¦a¡A"+pnoun(2, me)+"¥²¶·¥ý¶R¤U³o¶ô¦a¤~¯à¦b¤W­±«Ø³y«Ø¿vª«¡C\n");

	if( belong_to_government(owner) )
	{
		if( !CITY_D->is_mayor_or_officer(loc[CITY], me) )
			return tell(me, "³o¶ô¦a¬O¥«¬F©²¥Î¦a¡A"+pnoun(2, me)+"¨S¦³Åv§Q¦b³o¤W­±«Ø³y¥ô¦óªF¦è¡C\n");
	}
	else if( belong_to_enterprise(owner) )
	{
		if( owner[11..] != query("enterprise", me) )
			return tell(me, pnoun(2, me)+"¤£¬O"+ENTERPRISE_D->query_enterprise_color_id(query("enterprise", me))+"¥ø·~¶°¹Îªº¦¨­û¡AµLªk¦b¦¹«Ø³y¥ô¦óªF¦è¡C\n");
	}
	else if( owner != me->query_id(1) && !ENTERPRISE_D->same_enterprise(owner, me->query_id(1)) ) 
		return tell(me, "³o¶ô¦a¬O "+capitalize(owner)+" ªº¨p¤H¤g¦a¡A"+pnoun(2, me)+"¨S¦³Åv§Q¦b³o¤W­±«Ø³y¥ô¦óªF¦è¡C\n");

	if( arg )
		return select_icon(me, arg);
	
	tell(me, list+"\n¿é¤J¼Æ¦r¿ï¶µ»P¨Ï¥Îªº§÷®Æ(¨Ò 2a by stone)¡A"HIW"ls"NOR" Åã¥Ü¦Cªí¡G\n");

	input_to((: select_icon, me :));
}
