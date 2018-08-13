/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : drink.c
 * Author : Clode@RevivalWorld
 * Date   : 2003-03-04
 * Note   : drink 
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <feature.h>

inherit COMMAND;

string help = @HELP
都ノ都
drink '珇'		- 盢琘珇耻▄柑

HELP;

private void do_command(object me, string arg)
{
	int capacity;
	object ob;
	
	if( !arg )
	{
		if( me->is_npc() )
			return me->do_command("say ρ馏稱璶и耻ㄇぐ或\n");
		else
			return tell(me, pnoun(2, me)+"稱璶耻ㄇぐ或\n");
	}
	
	ob = present(arg, me) || present(arg, environment(me));
	
	if( !objectp(ob) )
	{
		if( me->is_npc() )
			return me->do_command("say ⊿Τ "+arg+" 硂贺都\n");
		else
			return tell(me, "⊿Τ "+arg+" 硂贺都\n");
	}

	if( !ob->is_drink() )
	{
		if( me->is_npc() )
			return me->do_command("say "+ob->query_idname()+"ぃ琌都礚猭都ノ\n");
		else
			return tell(me, ob->query_idname()+"ぃ琌都礚猭都ノ\n");
	}
	
	capacity = query("capacity", ob);

	if( capacity + me->query_drink_cur() > me->query_drink_max() )
	{
		if( me->is_npc() )
			return me->do_command("say и耻ぃ"+ob->query_idname()+"\n");
		else
			return tell(me, pnoun(2, me)+"耻ぃ"+ob->query_idname()+"\n");
	}
	
	me->add_drink(capacity);

	msg("$MEр$YOU耻\n", me, ob, 1);

	ob->drink();
	destruct(ob, 1);
}