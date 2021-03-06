/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : language_d.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-8-6
 * Note   : 處理語言跟編碼的問題
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#define is_ZH(x)    ((x)>=0xa1&&(x)<=0xfe)

#define is_B5maj(x) ((x)>=0x40&&(x)<=0x7e) //100%
#define	is_B5min(x) ((x)>=0xa1&&(x)<=0xfe) //40%
#define	is_GB(x)    ((x)>=0xa1&&(x)<=0xfe) //60%

/* 
	推測一字串為Big5碼的可能性(百分比機率)
	低於20%的百分比就幾乎可確定為GB碼
	判斷的正確度與字串長度呈正比
 */
int encode_conjecture(string arg)
{
	int i, poss=0, size;
	float gbposs=0.;
	
	if( !arg || !arg[0] ) return -1;
	
	size = sizeof(arg);
	
	for(i=0;i<size;i++)
	{
		if( !is_ZH(arg[i]) ) continue;
		
		i++;poss++;

		if( i<size&&!is_B5maj(arg[i]) )
		{
			if( is_GB(arg[i]) )
			{
				gbposs+=0.6;
				continue;
			}
			i--; poss--;	
		}
		gbposs-=0.4;
	}
	
	return poss ? to_int(exp(-gbposs/poss)*100)*2-100 : -1;
}

/*
	自動判別編碼並傳回採用Big5碼之字串 
   	僅適用於長度較長之字串, 判別率較高
*/
string auto_G2B(string arg)
{
	int con = encode_conjecture(arg);
	
	if( con > 0 && con < 20 ) return G2B(arg);
	return arg;
}

string query_name()
{
	return "語言系統(LANGUAGE_D)";
}
