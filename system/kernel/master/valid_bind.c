/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : valid_bind.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-07-05
 * Note   : included by Master Object
 * Update :
 *  o 2002-00-00

 -----------------------------------------
 */

/*
名稱：
        valid_bind - 判斷一個指定的函式指標 (function pointer) 是否能結合
                     (bind) 到一個物件上。
語法：
        int valid_bind( object doer, object owner, object victim );

        整數 valid_bind( 物件 作用者, 物件 擁有者, 物件 受害者 );
用法：
        當 doer 嘗試使用 bind() 外部函式結合 owner 對 victim 物件的函式指
        標，會呼叫此函式。如果此函式傳回 0，就禁止結合。
參考：
        bind
作者：
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
翻譯：
        spock@muds.net          2000.May.21.    v22 版
*/

int valid_bind(object doer, object owner, object victim) 
{
        return 1;
}
