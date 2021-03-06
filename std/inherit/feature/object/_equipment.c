/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : _equipment.c
 * Author : Clode@RevivalWorld
 * Date   : 2006-01-21
 * Note   :
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

private nosave object* equipping = allocate(0);

//
// 是否為裝備物件
//
int is_equipment()
{
	return 1;
}

//
// 刪除遺失的裝備者物件
//
void remove_null_equipping()
{
	foreach(object ob in equipping)
		if( !objectp(ob) )
			equipping -= ({ ob });
			
	if( !sizeof(equipping) )
		delete_temp("equipping");
}

//
// 回傳所有正在裝備此物件的使用者
//
object *query_equipping()
{
	remove_null_equipping();

	return equipping;	
}


//
// 是否正被裝備中
//
int is_equipping()
{
	return query_temp("equipping");
}


//
// 設定 ob 裝備上此物件
// set_temp("equipping") 讓 _loginload_usr 可以儲存裝備狀態
//
void set_equipping(object ob)
{
	equipping |= ({ ob });
	
	// 設定鎖定
	this_object()->set_keep();

	set_temp("equipping", 1);
	
	remove_null_equipping();
}


//
// 解除 ob 裝備此物件的狀態
// 只應由 _equipment_liv 呼叫, 不應由外界呼叫
//
varargs void delete_equipping(object ob)
{
	remove_null_equipping();

	if( undefinedp(ob) )
		equipping = allocate(0);
	else
		equipping -= ({ ob });

	// 解除鎖定
	if( !sizeof(equipping) )
	{
		delete_temp("equipping");
	}
}


//
// 取得部位設定
//
array query_part_set()
{
	return query("equip/part/set");
}


//
// 取得部位名稱
//
string query_part_name()
{
	return query("equip/part/name");
}


//
// 檢查是否允許被 user 裝備
//
int valid_equip(object user)
{
	return 1;
}


//
// 檢查是否允許被 user 卸下裝備
//
int valid_unequip(object user)
{
	return 1;
}


//
// 初始裝備設定
// 利用 set() 讓部位設定僅被設定於 shadow_object 內節省 memory 使用
//
void setup_equipment(array set, string name)
{
	set("equip/part/set", set);
	set("equip/part/name", name);
}

