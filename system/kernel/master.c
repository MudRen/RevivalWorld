/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : master.c
 * Author : Clode@RevivalWorld
 * Date   : 2000-12-18
 * Note   : 主宰物件
 * Update :
 *  o 2000-00-00  

 -----------------------------------------
 */

#include <object.h>

//-----------------------------------------------------------------------------

#include "master/flag.c";/* 用來 Debug , 平時無需載入 */
#include "master/compile_object.c";/* 用來載入 MudOS 虛擬物件 */
#include "master/crash.c";/* 用來處理 Crash 時的緊急情況 */
#include "master/preload.c";/* 預先載入初始化動作 */
#include "master/error.c";/* 處理錯誤訊息的函式 */
#include "master/file.c";/* 關於 domain_file , author_file , privs_file */
#include "master/ed.c";/* 有關 Edit 的一些設定 */
#include "master/parse.c";/* 文法(對中文Mud而言似乎沒有用處?) */
#include "master/object.c";/* 環境遭到毀滅時, 所有內在物件都會呼叫此函式 */

//-----------------------------------------------------------------------------

#include "master/valid_asm.c";
#include "master/valid_author.c";
#include "master/valid_bind.c";/* 檢查函式指標與物件的結合 */
#include "master/valid_compile_to_c.c";/* 判斷是否可以用 LPC->C 編譯 */
#include "master/valid_domain.c";
#include "master/valid_hide.c";/* 檢查匿蹤能力 */
#include "master/valid_link.c";/* 控制 link 外部函式的用途 */
#include "master/valid_object.c";/* 讓你能控制是否要載入某個物件 */
#include "master/valid_override.c";/* 控制 efun:: 的用途 */
#include "master/valid_readwrite.c";/* 檢查是否有權讀取寫入檔案 */
#include "master/valid_save_binary.c";/* 控制一個物件是否可以儲存它已載入的程式 */
#include "master/valid_shadow.c";/* 控制哪些物件可以被投影 */
#include "master/valid_socket.c";/* 保護 socket 外部函式 */
#include "master/valid_database.c";

//-----------------------------------------------------------------------------

/* 回傳連線物件 */
//        connect() 傳回的物件，會當作初始使用者物件 (initial user object)。
//        請注意，之後你可以使用 exec() 外部函式將改變使用者物件。

private object connect( int port )
{
        object ob;
        
        if( !catch(ob = new(LOGIN_OB) ) )
        	return ob;
        else
        	printf("\n登錄程式正在修改中，請稍後再試。\n\n");
}

private void create()
{
        printf("Master Object(/system/kernel/master.c) 載入成功\n");
}
