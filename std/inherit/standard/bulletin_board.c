/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : bulletin_board.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-3-21
 * Note   : ¼Ð·Ç¯d¨¥ªOÄ~©ÓÀÉ
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <feature.h>
#include <daemon.h>
#include <message.h>

#define BOARD_DATA_PATH		"/data/board/"

#define AUTHOR		0
#define TITLE		1

inherit MOVE;
inherit IDNAME;
inherit DATABASE;
inherit ACTION;

mapping actions;

// ¤é´ÁÀÉ¦W±Æ§Ç°}¦C
// POST_SORT = ({ ÀÉ®×int°}¦C(¤w±Æ§Ç) })
//int *POST_SORT = ({});

// Author »P Title ªººK­n§Ö¨ú
// SUMMARY = ([ ÀÉ®×(¤é´Á): ({ §@ªÌ, ¼ÐÃD }) ]);
//mapping SUMMARY = ([]);

void do_read(object me, string arg);
void do_post(object me, string arg);
void do_discard(object me, string arg);
void do_followup(object me, string arg);
void do_mail(object me, string arg);

int is_board()
{
	return 1;
}

void startup_action()
{
	actions = 
	([ 
	    "post"		:(: do_post :),
	    "read"		:(: do_read :),
	    "discard"		:(: do_discard :),
	    "followup"		:(: do_followup :),
	    "mail"		:(: do_mail :), 
	]);
}

// ¯d¨¥ªO¥DÅéªì©l¤Æ¸ü¤J¸ê®Æ
void initialize_board()
{
	int i, *post_sort = ({});
	string file, path, *elem;
	mapping summary = ([]);

	path = copy(set("savepath", BOARD_DATA_PATH + query("boardid") + "/"));

	// ­Y¨S¦³¯d¨¥ªO¥Ø¿ý«h«Ø¥ß
	if( file_size(path) != -2 ) mkdir(path);

	// Åª¨ú½s±Æ©Ò¦³¯d¨¥¸ê®Æ
	else foreach( file in get_dir(path) )
	{
		i = to_int(file);

		elem = allocate(2);
		sscanf( read_file(path+file,1,1), "%s|%s\n", elem[AUTHOR], elem[TITLE] );
		summary[i] = elem;
		post_sort += ({ i });
	}

	set("summary", summary);
	set("post_sort", post_sort);
	set("mass",-1);
}


string short()
{
	int *post_sort = copy(query("post_sort"));

	int unread, size, last_read = query("board_last_read/"+query("boardid"), this_player()) || 0;

	if( !(size = sizeof(post_sort)) ) return ::short()+" "+NOR WHT+"["NOR" ¨S¦³¥ô¦ó¯d¨¥ "WHT"]"NOR;

	unread = sizeof(filter_array(post_sort, (: $1 > $(last_read) :)));

	return ::short() +" "+NOR WHT+"[ "NOR+ size +" ±i¯d¨¥ " + (unread ? "¡M"+unread+" ±i¥¼Åª"WHT"]"NOR : WHT"]"NOR);
}

string long()
{
	string str;
	int i, index, last_read = query("board_last_read/"+query("boardid"), this_player());
	int *post_sort = copy(query("post_sort"));
	mapping summary = copy(query("summary"));

	str = sprintf("\n%-34s%s", this_object()->query_idname(), NOR WHT"¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n\n"NOR);

	foreach( index in post_sort )
	str += sprintf("%s[%4d] %s %-26s %-30s <%15s>\n",(index>last_read?HIY:""), ++i, NOR, summary[index][0], summary[index][1], TIME_D->replace_ctime(index));

	str += NOR WHT"\n¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n\n"NOR;

	return str;
}

void done_post(object me, int time, string arg)
{
	// Ã±¦WÀÉ
	string sig = query("signature", me);
	string *info = copy(query("summary"))[time];

	arg = info[AUTHOR]+"|"+info[TITLE]+"\n"+arg+(sig ? "\n\n"NOR WHT"¢w¢w\n"NOR+sig+NOR : NOR);

	if( write_file( (string)query("savepath")+time, arg ) )
	{
		set("post_sort", query("post_sort") + ({ time }), find_object(base_name(this_object())));
		tell(me, "¯d¨¥§¹²¦¡C\n");
		set_temp("lastpost/time", time(), me);
		me->finish_input();
	}
	else
		return tell(me, "¯d¨¥¥¢±Ñ¡A½Ð³qª¾§Å®v³B²z¡C\n");
}

void do_post(object me, string arg)
{
	int time = time();
	mapping summary = copy(query("summary"));

	if(!arg)
		return tell(me, "½Ð¬°±zªº¤å³¹«ü©w¤@­Ó¼ÐÃD¡C\n");

	if( noansi_strlen(arg) > 26 )
		return tell(me, "§Aªº¼ÐÃD¤Óªø¤F¡A½ÐÁYµu§Aªº¼ÐÃD¡C\n");

	if( time() - query_temp("lastpost/time", me) < 20 )
		return tell(me, "©êºp¥Ø«eµo¤å®É¶¡¥²¶·¶¡¹j 20 ¬í¡C\n");

	while( member_array(time, query("post_sort"))+1 ) time++;
	summary[time] = ({ me->query_idname(), arg });
	set("summary", summary, find_object(base_name(this_object())));

	me->edit( (: done_post, me, time :) );
}

void do_discard(object me, string arg)
{
	int num, file;
	int *post_sort = copy(query("post_sort"));
	mapping summary = copy(query("summary"));

	if( !arg || !sscanf(arg, "%d", num) )
		return tell(me, "½Ð¿é¤J¹w§R°£¤§¤å³¹½s¸¹¡C\n");

	if( num < 1 || num > sizeof(post_sort) )
		return tell(me, "¨S¦³³o±i¯d¨¥¡C\n");

	file = post_sort[--num];

	if( me->query_idname() != summary[file][AUTHOR] )
	{
		string author_id;
		sscanf( remove_ansi(summary[file][AUTHOR]), "%*s(%s)", author_id );
		author_id = lower_case(author_id);
		if( me->query_id(1) != author_id 
		    && (!wizardp(me) || SECURE_D->level_num(author_id) > SECURE_D->level_num(me->query_id(1)) )
		    && !CITY_D->is_mayor(query("city"), me))
			return tell(me, "³o±i¯d¨¥¤£¬O"+ pnoun(2, me) +"¼gªº¡C\n");
	}

	if( rm(query("savepath")+(file<1000000000?"0":"")+file) )
	{
		set("post_sort", post_sort - ({ file }), find_object(base_name(this_object())));
		map_delete(summary, file);
		set("summary", summary, find_object(base_name(this_object())));
		tell(me, "§R°£§¹²¦¡C\n");
	}
	else tell(me, "§R°£¥¢±Ñ¡A½Ð³qª¾§Å®v³B²z¡C\n");
}

void do_read(object me, string arg)
{
	string msg;
	int num, last_read, file;
	int *post_sort = copy(query("post_sort"));
	mapping summary = copy(query("summary"));

	last_read = query("board_last_read/"+query("boardid"), me);


	if( !arg || arg == "new" || arg == "next" )
		num = (last_read ? sizeof(filter_array(post_sort, (: $1 <= $(last_read) :))) : 0) + 1;

	else if( !sscanf(arg, "%d", num) )
		return tell(me, "§A­nÅª²Ä´X±i¯d¨¥¡S\n");

	if( num < 1 || num-1 > sizeof(post_sort) )
		return tell(me, "¨S¦³³o±i¯d¨¥¡C\n");

	else if( num-1 == sizeof(post_sort) )
		return tell(me, "¨S¦³·sªº¯d¨¥¡C\n");

	file = post_sort[--num];

	msg = sprintf("[1;46m½g ¼Æ[m %-27s[1;46m§@ ªÌ[m %s\n[1;46m¥D ÃD[m %-27s[1;46m®É ¶¡[m %s[m\n¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[1;30m[[1;37mContent[m[1;30m][m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n%s\n%s",
	    "²Ä"+CHINESE_D->chinese_number(num+1)+"½g",
	    summary[file][AUTHOR],
	    summary[file][TITLE],
	    TIME_D->replace_ctime(file),
	    read_file(query("savepath")+(file<1000000000?"0":"")+file, 2),
	    "¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[1;30m[[1;37mEnd[m[1;30m][m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n\n"
	);

	me->more( msg );

	if( file >= last_read ) set("board_last_read/"+query("boardid"), file, me);
}

void do_followup(object me, string arg)
{
	int num, file, time = time();
	string msg="", new_title;
	int *post_sort = copy(query("post_sort"));
	mapping summary = copy(query("summary"));

	if( !arg )
		return tell(me, "½Ð¿é¤J±ý¦^ÂÐªº¤å³¹½s¸¹©Î last ¦^ÂÐ³Ì«á¤@½g¤å³¹¡C\n");
	if( arg == "last" ) num = sizeof(post_sort)-1;
	else if( !sscanf(arg, "%d", num) || !sscanf(arg, "%d %s", num, new_title) )
		return tell(me, "½Ð¿é¤J±ý¦^ÂÐªº¤å³¹½s¸¹¡C\n");
	else if( arg == "last" ) num = sizeof(post_sort);

	if( num < 1 || num > sizeof(post_sort) )
		return tell(me, "¨S¦³³o±i¯d¨¥¡C\n");

	if( new_title && noansi_strlen(new_title) > 26 )
		return tell(me, "§Aªº¼ÐÃD¤Óªø¤F¡A½ÐÁYµu§Aªº¼ÐÃD¡C\n");

	file = post_sort[num-1];

	foreach( string word in explode( read_file(query("savepath")+(file<1000000000?"0":"")+file, 2), "\n" ) )
	{
		if( word == "" || word[0..7]=="[1;30m>" ) continue;
		else if( word == NOR WHT"¢w¢w" ) break;
		else if( word[0..5] == "[33m>" ) msg += "[1;30m> "+word[5..]+"\n";
		else if( word[0..5] == "[36m>" ) msg += "[33m> "+word[5..]+"\n";
		else msg += "[36m> "+word+"\n";
	}

	if( msg[0..5] == "[36m>" ) 
		msg = "[36m> ¡·"+summary[file][AUTHOR]+" ¦b "+TIME_D->replace_ctime(file)+" ¯d¤U³o½g¯d¨¥¡R\n" + msg;

	msg += "\n¡·"+me->query_idname()+" ¦b "+TIME_D->replace_ctime(time)+" ¯d¤U³o½g¯d¨¥¡R\n";

	while( member_array(time, post_sort)+1 ) time++;
	set("summary", summary + ([ time : ({ me->query_idname(), (new_title || (summary[file][TITLE][0..5]!="¦^ÂÐ¡G"?"¦^ÂÐ¡G":"")) + summary[file][TITLE] }) ]), find_object(base_name(this_object())));

	me->edit( (: done_post, me, time :), msg );
}

void do_mail(object me, string arg)
{
	int file, num, *post_sort = copy(query("post_sort"));
	string msg, email;
	mapping summary = copy(query("summary"));

	if( !arg || !sscanf(arg, "%d", num) )
		return tell(me, "«ü¥O®æ¦¡: mail <¤å³¹½s¸¹>\n");

	if( num < 1 || num > sizeof(post_sort) )
		return tell(me, "¨S¦³³o±i¯d¨¥¡C\n");

	if( !wizardp(me) )
		return tell(me, "¥»¥\¯à©|¥½¶}©ñª±®a¨Ï¥Î¡C\n");

	if( !stringp(email = query("email", me)) )
		return tell(me, "±z¨S¦³³]©w¹q¤l¶l¥ó¡C\n");

	file = post_sort[--num];

	msg = "¥H¤U°T®§Âà¸ü¦Û ­«¥Íªº¥@¬É(Revival World)\n\n";
	msg += sprintf("[1;46m½g ¼Æ[m %-27s[1;46m§@ ªÌ[m %s\n[1;46m¥D ÃD[m %-27s[1;46m®É ¶¡[m %s[m\n¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[1;30m[[1;37mContent[m[1;30m][m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n%s\n%s",
	    "²Ä"+CHINESE_D->chinese_number(num+1)+"½g",
	    summary[file][AUTHOR],
	    summary[file][TITLE],
	    TIME_D->replace_ctime(file),
	    read_file(query("savepath")+(file<1000000000?"0":"")+file, 2),
	    "¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w[1;30m[[1;37mEnd[m[1;30m][m¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w\n\n"
	);
	msg = remove_ansi(msg);
	SMTP_D->mail(email, msg, "­«¥Íªº¥@¬É(Revival World) - ¤å³¹Âà¸ü");
	tell(me, "¤å³¹¤w°e¥X¦Ü±zªº E-mail «H½c¡C\n");
}

