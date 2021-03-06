/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : error.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-07-05
 * Note   : included by Master Object
 * Update :
 *  o 2002-00-00

 -----------------------------------------
 */

#include <daemon.h>

#define TRACE_DETAIL_LENGTH_LIMIT	300
#define SPRINTF_OVERFLOW		65535

/* 處理錯誤訊息的函式 */
string tracert_error(mapping error, int caught)
{
        int count;
        string err_msg;
        mapping trace;

        err_msg="\n"+sprintf(@ERR
──────────────<Bugs Report>──────────────
[ 錯誤時間 ]: %-s
[ 錯誤內容 ]: %-s[m
[ 錯誤檔案 ]: %-s
[ 錯誤行數 ]: %-d[m
[ 資料回溯 ]:
ERR,
        ctime(time()),
        replace_string(error["error"], "\n", " "),
        error["file"],
        error["line"]);

        foreach(trace in error["trace"])
        {
                count++;
                err_msg +=sprintf(@ERR
    -- 第 %|3d 筆 --
        [ 觸動物件 ]: %O     
        [ 程式檔案 ]: %s
        [ 函式名稱 ]: %s(%s)
        [ 呼叫行數 ]: %s
ERR,
                count,
                trace["object"],
                trace["program"]||"",
                trace["function"]||"",
                trace["arguments"] ? implode(map(trace["arguments"], (:typeof($1):)), ", ") : "",
                (trace["line"] || "未知")+"");

                if( trace["arguments"] )
                {
                        err_msg += "        [ 傳入參數 ]:\n";
                        err_msg += implode(map(trace["arguments"], (: "                   ** ("+typeof($1)+")"+implode(explode(sprintf("%."+TRACE_DETAIL_LENGTH_LIMIT+"O\n", $1)+(strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... 訊息過長省略\n" : ""), "\n"),"\n                      ") :)), "\n")+"\n";
                }
                if( trace["locals"] )
                {
                        err_msg += "        [ 程式變數 ]:\n";
                        err_msg += implode(map(trace["locals"], (: "                   ** ("+typeof($1)+")"+implode(explode(sprintf("%."+TRACE_DETAIL_LENGTH_LIMIT+"O\n", $1)+(strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... 訊息過長省略\n" : ""), "\n"),"\n                      ") :)), "\n")+"\n";
                }
        }
        err_msg+="──────────────<Bugs Report>──────────────\n\n";
        return err_msg;
}

void error_handler(mapping error, int caught)
{
	object me;
	string msg;
	
	me = this_interactive() || this_player() || previous_object();

	// 避免陷入無限錯誤回報迴圈
	if( previous_object() == this_object() )
	{
		if( find_object(CHANNEL_D) )
			CHANNEL_D->channel_broadcast("sys", "Master object 發生無限錯誤迴圈，"+error["file"]+" 第 "+error["line"]+" 行，錯誤："+error["error"]+"，已強制中止。");
		return;
	}

        msg = tracert_error(error, caught);
        
        if( caught )
        	log_file("catch", msg);
        else
        	log_file("run", msg);
        	
        if( objectp(me) && userp(me) )
        {
        	string *command = query_temp("command", me);

		if( strlen(msg) >= SPRINTF_OVERFLOW-50000 ) msg = msg[0..SPRINTF_OVERFLOW-50000] + "\n\n[訊息過長省略...]\n";
		
		if( member_array("temp_database", variables(me)) != -1 ) 
			set_temp("bug_msg", msg, me);

		if( !wizardp(me) )
		{
			tell(me, "[1;5;33mWARNING[m 這個程式作業執行無效即將關閉，如有問題請洽程式設計師或相關人員...\n", "ERRMSG");			
			
			// 避免 CHANNEL_D 本身發生錯誤時的問題
			if( find_object(CHANNEL_D) )
			{
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"("+(sizeof(command)==2?command[0]+" "+command[1]:"Unknown")+")執行時段錯誤"+(caught ? "(Catch)" : "")+"："+error["file"]+" 第 "+error["line"]+" 行。");
				CHANNEL_D->channel_broadcast("sys", "錯誤："+replace_string(error["error"],"\n", " ")+"。");
			}
			tell(me, "[1;32m已自動將錯誤通知線上巫師處理，請稍後片刻，若無人處理請主動通報巫師。[m\n", "ERRMSG");
		}
		else
			tell(me, "[1;33m執行時段錯誤[m：請執行 bug 檢查詳細錯誤回溯。\n"+"[1;33m........檔案[m："+error["file"]+"\n[1;33m........行數[m：第 "+error["line"]+" 行\n[1;33m........錯誤[m："+replace_string(error["error"],"\n", " ")+"\n", "ERRMSG");

		//me->finish_input();
	}
	else
	{
		// 避免 CHANNEL_D 本身發生錯誤時的問題
		if( find_object(CHANNEL_D) )
		{
			CHANNEL_D->channel_broadcast("sys", (objectp(me) ? base_name(me)+" " : "")+"執行時段錯誤"+(caught ? "(Catch)" : "")+"："+error["file"]+" 第 "+error["line"]+" 行。");
			CHANNEL_D->channel_broadcast("sys", "錯誤："+replace_string(error["error"],"\n", " ")+"。");
		}
	}

}


// Write an error message into a log file. The error occured in the object
// 'file', giving the error message 'message'.
/* 紀錄顯示編譯錯誤之訊息 */
void log_error(string, string message)
{
	string error_type;
	object user = this_interactive() || this_player() || previous_object();

    	log_file("comp", message);

	error_type = strsrch(message, "Warning") == -1 ? "錯誤" : "警告";

	if( objectp(user) && userp(user) )
	{
		if( !wizardp(user) )
			CHANNEL_D->channel_broadcast("sys", user->query_idname()+"編譯時段"+error_type+"："+message);

		tell(user, "[1;33m編譯時段"+error_type+"[m：" + message, "ERRMSG");
	}
	else
		CHANNEL_D->channel_broadcast("sys", (objectp(user) ? base_name(user)+" " : "")+"編譯時段"+error_type+"："+message);
}