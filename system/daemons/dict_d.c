/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : dict_d.c
 * Author : Whatup@Revival World
 * Date   : 2000-00-00
 * Note   : 翻譯精靈
 * Update :
 *  o 2000-00-00 目前是利用此網站作查詢 http://www.ee.tku.edu.tw/~rexchen/
 *
 -----------------------------------------
 */
#include <ansi.h>
#include <socket.h>
#include <socket_err.h>
#include <message.h>

string strs="";

// string simplex; /* 查詢的單字 */
// object tu;/* 把訊息傳給user看到 */
mapping connects = allocate_mapping(0);
private void get_data(int);

void create() { }

void find_word(object user,string word)
{
	int err,fd;

	if(!user) return ;
	if(!word) return ;        

	/* 開啟網路連結 */
	fd = socket_create(STREAM, "read_callback","close_socket");

	if ( fd < 0 )
	{
		return tell( user, HIR"查詢失敗, 請稍後在試。\n"NOR);             
	}

	err = socket_connect(fd,"163.13.132.61 80","read_callback","write_callback" );

	if( err!=EESUCCESS )
	{
		return tell( user, HIR"查詢失敗, 請稍後在試。\n"NOR);     
	}

	connects[fd] = allocate_mapping(3);
	connects[fd]["data"] = "";
	connects[fd]["user"] = user;
	connects[fd]["simplex"] = word;

	return ;
}

int close_socket(int fd)
{
	socket_close(fd);
	get_data(fd);
}

void read_callback(int fd, mixed message)
{
	/* 把每次取得的資料存進 strs 裡 */
	connects[fd]["data"] += message;
	return ;
}

void write_callback(int fd)
{
	string code="";
	code = connects[fd]["simplex"];
	/* 輸入指令抓取該頁內容 */
	socket_write(fd,
	    sprintf("GET /~rexchen/cdict/wwwcdict.cgi?word=%s\r\n"
		,code));
	return ;
}

private void get_data(int fd)
{
	string str;
	if(sscanf(connects[fd]["data"],"%*s<pre>%s</pre>%*s",str)!=3)
	{
		tell(connects[fd]["user"], HIR"查詢失敗, 請稍後在試。\n"NOR);
		return ;
	}
	str = replace_string(str,connects[fd]["simplex"],HIY+connects[fd]["simplex"]+NOR);
	str = sprintf(HIC"您查詢的單字為 : %s "NOR"\n%s\n%s", 
	    connects[fd]["simplex"],repeat_string("=",50),str);

	tell(connects[fd]["user"], str );

	return ;
}

string query_name()
{
	return "字典系統(DICT_D)";
}
