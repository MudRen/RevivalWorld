/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : _product_action_mod.c
 * Author : Clode@RevivalWorld
 * Date   : 2005-04-06
 * Note   : product action module
 * Update :
 *
 *
 -----------------------------------------
 */

void create()
{
	string this_basename = base_name(this_object())+".c";
	
	// 暴力更新所有使用此模組之物件 action...
	objects( (: $1->query_module_file() == $(this_basename) :) )->enable_action();
}

mapping query_product_info()
{
	return fetch_variable("product_info");
}
