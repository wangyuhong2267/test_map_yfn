//
//  tcp_socket.hpp
//  test_map
//
//  Created by wangyuhong2267 on 17/2/26.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#ifndef tcp_socket_hpp
#define tcp_socket_hpp
#include "const.h"
class Ctcp_socket
{
public:
	Ctcp_socket();
	virtual ~Ctcp_socket();
	
	string  str;
	
public:
	
	
	static Ctcp_socket* p_inst;
	static Ctcp_socket *get_instance();
	int tcp_connect_timeout (int* sd, unsigned int timeout ,char *ip,int port);
	void test_print();
};

#endif /* tcp_socket_hpp */
