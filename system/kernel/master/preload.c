/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : preload.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-07-05
 * Note   : included by Master Object
 * Update :
 *  o 2002-00-00

 -----------------------------------------
 */

#define FIRST_PRELOAD	"/system/daemons/system_d.c"

/* ﹍て穨 Initialization */
/* 璝 driver 把计 -e , flag 獶箂 */
string *epilog(int flag)
{
	if( flag )
	{
		printf("臱笆祘Α箇更祘\n");
		log_file("system/preload","臱笆祘Α箇更祘\n");
		return allocate(0);
	}

	return ({ FIRST_PRELOAD });
}

/* 箇更ン */
void preload(string file)
{
	mixed err;
	
	if( err = catch(load_object(file)) )
		log_file("system/preload",sprintf("更 %s 祇ネ岿粇: %O\n", file, err));
}
