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

/* ³B²z¿ù»~°T®§ªº¨ç¦¡ */
string tracert_error(mapping error, int caught)
{
        int count;
        string err_msg;
        mapping trace;

        err_msg="\n"+sprintf(@ERR
¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w<Bugs Report>¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w
[ ¿ù»~®É¶¡ ]: %-s
[ ¿ù»~¤º®e ]: %-s[m
[ ¿ù»~ÀÉ®× ]: %-s
[ ¿ù»~¦æ¼Æ ]: %-d[m
[ ¸ê®Æ¦^·¹ ]:
ERR,
        ctime(time()),
        replace_string(error["error"], "\n", " "),
        error["file"],
        error["line"]);

        foreach(trace in error["trace"])
        {
                count++;
                err_msg +=sprintf(@ERR
    -- ²Ä %|3d µ§ --
        [ Ä²°Êª«¥ó ]: %O     
        [ µ{¦¡ÀÉ®× ]: %s
        [ ¨ç¦¡¦WºÙ ]: %s(%s)
        [ ©I¥s¦æ¼Æ ]: %s
ERR,
                count,
                trace["object"],
                trace["program"]||"",
                trace["function"]||"",
                trace["arguments"] ? implode(map(trace["arguments"], (:typeof($1):)), ", ") : "",
                (trace["line"] || "¥¼ª¾")+"");

                if( trace["arguments"] )
                {
                        err_msg += "        [ ¶Ç¤J°Ñ¼Æ ]:\n";
                        err_msg += implode(map(trace["arguments"], (: "                   ** ("+typeof($1)+")"+implode(explode(sprintf("%."+TRACE_DETAIL_LENGTH_LIMIT+"O\n", $1)+(strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... °T®§¹Lªø¬Ù²¤\n" : ""), "\n"),"\n                      ") :)), "\n")+"\n";
                }
                if( trace["locals"] )
                {
                        err_msg += "        [ µ{¦¡ÅÜ¼Æ ]:\n";
                        err_msg += implode(map(trace["locals"], (: "                   ** ("+typeof($1)+")"+implode(explode(sprintf("%."+TRACE_DETAIL_LENGTH_LIMIT+"O\n", $1)+(strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... °T®§¹Lªø¬Ù²¤\n" : ""), "\n"),"\n                      ") :)), "\n")+"\n";
                }
        }
        err_msg+="¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w<Bugs Report>¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n\n";
        return err_msg;
}

void error_handler(mapping error, int caught)
{
	object me;
	string msg;
	
	me = this_interactive() || this_player() || previous_object();

	// Á×§K³´¤JµL­­¿ù»~¦^³ø°j°é
	if( previous_object() == this_object() )
	{
		if( find_object(CHANNEL_D) )
			CHANNEL_D->channel_broadcast("sys", "Master object µo¥ÍµL­­¿ù»~°j°é¡A"+error["file"]+" ²Ä "+error["line"]+" ¦æ¡A¿ù»~¡G"+error["error"]+"¡A¤w±j¨î¤¤¤î¡C");
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

		if( strlen(msg) >= SPRINTF_OVERFLOW-50000 ) msg = msg[0..SPRINTF_OVERFLOW-50000] + "\n\n[°T®§¹Lªø¬Ù²¤...]\n";
		
		if( member_array("temp_database", variables(me)) != -1 ) 
			set_temp("bug_msg", msg, me);

		if( !wizardp(me) )
		{
			tell(me, "[1;5;33mWARNING[m ³o­Óµ{¦¡§@·~°õ¦æµL®Ä§Y±NÃö³¬¡A¦p¦³°ÝÃD½Ð¬¢µ{¦¡³]­p®v©Î¬ÛÃö¤H­û...\n", "ERRMSG");			
			
			// Á×§K CHANNEL_D ¥»¨­µo¥Í¿ù»~®Éªº°ÝÃD
			if( find_object(CHANNEL_D) )
			{
				CHANNEL_D->channel_broadcast("sys", me->query_idname()+"("+(sizeof(command)==2?command[0]+" "+command[1]:"Unknown")+")°õ¦æ®É¬q¿ù»~"+(caught ? "(Catch)" : "")+"¡G"+error["file"]+" ²Ä "+error["line"]+" ¦æ¡C");
				CHANNEL_D->channel_broadcast("sys", "¿ù»~¡G"+replace_string(error["error"],"\n", " ")+"¡C");
			}
			tell(me, "[1;32m¤w¦Û°Ê±N¿ù»~³qª¾½u¤W§Å®v³B²z¡A½Ðµy«á¤ù¨è¡A­YµL¤H³B²z½Ð¥D°Ê³q³ø§Å®v¡C[m\n", "ERRMSG");
		}
		else
			tell(me, "[1;33m°õ¦æ®É¬q¿ù»~[m¡G½Ð°õ¦æ bug ÀË¬d¸Ô²Ó¿ù»~¦^·¹¡C\n"+"[1;33m........ÀÉ®×[m¡G"+error["file"]+"\n[1;33m........¦æ¼Æ[m¡G²Ä "+error["line"]+" ¦æ\n[1;33m........¿ù»~[m¡G"+replace_string(error["error"],"\n", " ")+"\n", "ERRMSG");

		//me->finish_input();
	}
	else
	{
		// Á×§K CHANNEL_D ¥»¨­µo¥Í¿ù»~®Éªº°ÝÃD
		if( find_object(CHANNEL_D) )
		{
			CHANNEL_D->channel_broadcast("sys", (objectp(me) ? base_name(me)+" " : "")+"°õ¦æ®É¬q¿ù»~"+(caught ? "(Catch)" : "")+"¡G"+error["file"]+" ²Ä "+error["line"]+" ¦æ¡C");
			CHANNEL_D->channel_broadcast("sys", "¿ù»~¡G"+replace_string(error["error"],"\n", " ")+"¡C");
		}
	}

}


// Write an error message into a log file. The error occured in the object
// 'file', giving the error message 'message'.
/* ¬ö¿ýÅã¥Ü½sÄ¶¿ù»~¤§°T®§ */
void log_error(string, string message)
{
	string error_type;
	object user = this_interactive() || this_player() || previous_object();

    	log_file("comp", message);

	error_type = strsrch(message, "Warning") == -1 ? "¿ù»~" : "Äµ§i";

	if( objectp(user) && userp(user) )
	{
		if( !wizardp(user) )
			CHANNEL_D->channel_broadcast("sys", user->query_idname()+"½sÄ¶®É¬q"+error_type+"¡G"+message);

		tell(user, "[1;33m½sÄ¶®É¬q"+error_type+"[m¡G" + message, "ERRMSG");
	}
	else
		CHANNEL_D->channel_broadcast("sys", (objectp(user) ? base_name(user)+" " : "")+"½sÄ¶®É¬q"+error_type+"¡G"+message);
}