string *ip_list = allocate(0);

int check_login_ip( object ob )
{
	string ip = query_ip_number(ob);

	// 若找不到
	if( member_array( ip, ip_list ) == -1 )
	{	
		ip_list += ({ ip });
		return 0;
	} else {
		// 若找到了, 返回 
		return 1;
	}
}

