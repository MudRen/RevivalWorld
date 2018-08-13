/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : chinese_d.c
 * Author : Clode@RevivalWorld
 * Date   : 2001-3-1
 * Note   : いゅ弘艶, 箇璸盢┮ΤㄧΑ糶 MudOS's Chinese Package
 * Update :
 *  o 2001-03-01 Clode ミе戈(30kオram), 碩糤秈瞯
 *  o 2001-03-01 Clode 穝糤﹃块笷礚计计陪ボ
 *
 -----------------------------------------
 */

private string *number = ({ "箂","","","","","き","せ","","","","" });
private string *number2 = ({ "箂","滁","禠","把","竩","ヮ","嘲","琺","","╤","ぐ" });

// 程计虫パ糤搭
//string *unit = ({"窾","货","","ㄊ","","猇","鲽","肪","碱","タ","更","伐","猠‵","宫","êパウ","ぃ某","礚秖","计",});
private string *unit = ({"窾","货","",});

private mapping cache;

string chinese_number(mixed i)
{
	// 璝块把计 integer (穦 overflow) 
	if( intp(i) )
	{
	    if( i < 0 )
		return "璽"+chinese_number(-i);
	    if( i < 11 )
	    	return number[i];
	    if( i < 1000 )
		return cache[i];
	    if( i < 10000 )
	    {
		if( !(i % 1000) ) return number[i/1000]+"";
		if( i%1000 < 100 ) return number[i/1000]+"箂"+cache[i%1000];
		return number[i/1000]+""+cache[i%1000];
	    }
	    if( i < 100000000 ) 
	    {
		if( !(i % 10000) ) return chinese_number(i/10000)+"窾";
		if( i%10000 < 1000 ) return chinese_number(i/10000)+"窾箂"+cache[i%10000];
		return chinese_number(i/10000)+"窾"+chinese_number(i%10000);
	    }
	    if( i < 2147483648 )
	    {
		if( !(i % 100000000) ) return cache[i/100000000]+"货";
		if( i%100000000 < 10000000 ) return cache[i/100000000]+"货箂"+chinese_number(i%100000000);
		return cache[i/100000000]+"货"+chinese_number(i%100000000);
	    }
	    else return "2147483647(overflow)";
	}
	// 璝块把计 string (礚计矪瞶)
	else if( stringp(i) && i != "")
	{
	   	int j, k, *n=({}), usize = sizeof(unit);
		string *u=({""}), msg;
		
		if( i[0] == '-' ) return "璽"+chinese_number(i[1..]);
		
		// 盢计ㄌ计╊秆
		while( (msg = i[<(j+=4)..<(j-3)])!="" )
		{			
			n += ({ to_int(msg) });
			if( j != 4 ) u += ({ unit[k++%usize] });
		}
		
		j = k = sizeof(n);
			
		while(j--)
			if( n[j] ) msg += (j+1<k ? (n[j+1] && n[j]>999 ? chinese_number(n[j]):"箂"+chinese_number(n[j])):chinese_number(n[j])) + u[j];
			else if( u[j] == unit[usize-1] ) msg += unit[usize-1];

		return msg;
	}
	else return "岿粇计";
}

nomask string chinese_period(int t)
{
	int y, n, d, h, m, s;
	string time="";

	s = t %60;
	m = t /60%60;
	h = t /60/60%24;
	d = t /60/60/24%30;
	n = t /60/60/24/30%13;
	y = t /60/60/24/30/13;

	if(y) time = cache[y] + "";
	if(n) time += cache[n] + "る"		+ (y?"":"");
	if(d) time += cache[d] + "ぱ"		+ (n||y?"":"");
	if(h) time += cache[h] + ""		+ (d||n||y?"":"");
	if(m) time += cache[m] + "だ"		+ (h||d||n||y?"":"");

	return time+cache[s]+"";	
}

private mapping chinese =
([
"north"		:"娩",
"south"		:"玭娩",
"east"		:"狥娩",
"west"		:"﹁娩",
"northwest"	:"﹁娩",
"northeast"	:"狥娩",
"southwest"	:"﹁玭娩",
"southeast"	:"狥玭娩",
"down"		:"加",
"up"		:"加",
]);

string to_chinese(string idx)
{
	return chinese[idx];
}

int chinese_to_number(mixed chinese)
{
	int i, len, num, idx;
	
	if( intp(chinese) ) return chinese;
	
	if( !stringp(chinese) )
		return 0;

	len = sizeof(chinese);
	
	for(i=0;i<len;i+=2)
	{
		idx = member_array(chinese[i..i+1], number);
		
		if( idx == -1 )
			idx = member_array(chinese[i..i+1], number2);
		
		if( idx == -1 )
			continue;
		
		if( idx == 10 )
		{
			if( i!=0 )
				continue;
			else if(i+2!=len)
				idx = 1;
		}

		num = num*10 + idx;
	}
	return num;
}

string initialize(int i)
{
	if( i < 11 ) return number[i];
	if( i < 20 ) return ""+number[i%10];
	if( i < 100 ) return number[i/10]+""+(i%10 ? number[i%10] : "" );
	if( i < 1000 ) return number[i/100]+"κ"+(i%100 ? ((i%100<10?"箂":0)||(i%100<20?"":""))+initialize(i%100) : "");
}
 
private void create()
{
	cache = allocate_mapping(0);
	
	/* ミ计е */
	for(int i=0;i<=1000;i++)
		cache[i] = initialize(i);
}

string query_name()
{
	return "いゅ╰参(CHINESE_D)";
}
