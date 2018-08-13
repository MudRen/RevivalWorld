/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : _database.c
 * Author : Clode@RevivalWorld
 * Date   : 2000-12-29
 * Note   : 資料庫系統
 * Update :
 *  o 2001-03-24 Clode 原有 Functions 已全改用 External Functions
 *
 -----------------------------------------
 */

// 長存資料庫
private mapping database = allocate_mapping(0);
// 暫存資料庫
private nosave mapping temp_database = allocate_mapping(0);

mapping query_database()
{
	return copy(database);
}

mapping query_temp_database()
{
	return copy(temp_database);
}

void set_temp_database(mapping tdb)
{
	if( !mapp(tdb) ) return;

	temp_database = copy(tdb);
}
	
varargs int set_shadow_ob(object ob)
{
	if( clonep() ) 
	{
		set("shadow_ob", ob || load_object(base_name(this_object())));
		return 1;
	}
	return 0;
}

object query_shadow_ob()
{
	return database["shadow_ob"];
}