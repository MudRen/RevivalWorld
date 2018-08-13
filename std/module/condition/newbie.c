/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : newbie.c
 * Author : Clode@RevivalWorld
 * Date   : 2006-02-09
 * Note   : 
 * Update :
 *  o 2000-00-00  

 -----------------------------------------
 */
 
#include <ansi.h>
#include <buff.h>

#define CONDITION_ID		"newbie"
#define CONDITION_NAME		HIG"�s��"NOR GRN"���|�N"NOR
#define CONDITION_TYPE		"�[��"
#define DEFAULT_TIME		21600
#define DEFAULT_HEART_BEAT	0

// �^�Ǫ��A�^��W��
string query_condition_id()
{
	return CONDITION_ID;
}

// �^�Ǫ��A����W��
string query_condition_name()
{
	return CONDITION_NAME;
}

// �^�Ǫ��A���A�W��
string query_condition_type()
{
	return CONDITION_TYPE;
}

// �^�Ǫ��A�w�]����ɶ�
int query_default_condition_time()
{
	return DEFAULT_TIME;
}

// �^�Ǫ��A�w�]�߸��ɶ�
int query_default_condition_heart_beat()
{
	return DEFAULT_HEART_BEAT;
}

// �Ұʪ��A�ɪ��ĪG
void start_effect(object ob)
{
	set("condition/"+replace_string(base_name(this_object()), "/","#")+"/"+BUFF_SOCIAL_EXP_BONUS, 50, ob);
	msg("$ME�i�J�u"CONDITION_NAME"�v��"CONDITION_TYPE"���A�C\n", ob, 0, 1);
}

// �������A�ɪ��ĪG
void stop_effect(object ob)
{
	msg("$ME�����u"CONDITION_NAME"�v��"CONDITION_TYPE"���A�C\n", ob, 0, 1);
}

// ���A�i�椤���ĪG
void heart_beat_effect(object ob)
{


}