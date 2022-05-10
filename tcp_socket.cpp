//
//  tcp_socket.cpp
//  test_map
//
//  Created by wangyuhong2267 on 17/2/26.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#include "tcp_socket.hpp"


Ctcp_socket* Ctcp_socket::p_inst = NULL;

Ctcp_socket::Ctcp_socket()
{
	
	
	
}

Ctcp_socket::~Ctcp_socket()
{
	
}


Ctcp_socket * Ctcp_socket::get_instance()
{
	if(p_inst == NULL)
	{
		p_inst = new Ctcp_socket();
	}
	return p_inst;
}


void Ctcp_socket::test_print()
{
	cout<<"Ctcp_socket,terst_print......"<<endl;
}

int Ctcp_socket::tcp_connect_timeout (int* sd, unsigned int timeout ,char *ip,int port)
{
	
	int result = -1;

	int flags = 0;
	fd_set rfds;
	fd_set wfds;
	struct timeval tv;
	int optval;
	socklen_t optlen;
	
	*sd =  socket(AF_INET, SOCK_STREAM, 0);
	////////////////////////////////////
	struct sockaddr_in socketParameters;
	socketParameters.sin_family = AF_INET;
	//socketParameters.sin_addr.s_addr = inet_addr("112.16.180.61");
	socketParameters.sin_addr.s_addr = inet_addr(ip);
	//socketParameters.sin_port = htons([port intValue]);
	//socketParameters.sin_port = htons(7890);
	socketParameters.sin_port = htons(port);
	//printf("ddd\n");
	/////////////////////////////////////
	if(*sd < 0) {
		return -1;
	}
	
	/* make socket non-blocking */
	flags = fcntl(*sd, F_GETFL, 0);
	fcntl(*sd, F_SETFL, flags | O_NONBLOCK);
	
	/* attempt to connect */
	//result = connect(*sd, res->ai_addr, res->ai_addrlen);
	//printf("bbb\n");
	result = connect(*sd, (struct sockaddr *) &socketParameters, sizeof(socketParameters));
	/* immediately successful connect */
	if(result == 0) {
		result = 1;
		/*printf("IMMEDIATE SUCCESS\n");*/
	}
	
	/* connection error */
	else if(result < 0 && errno != EINPROGRESS) {
		result = -1;
	}
	
	/* connection in progress - wait for it... */
	else {
		
		do {
			
			/* set connection timeout */
			tv.tv_sec = timeout;
			tv.tv_usec = 0;
			
			FD_ZERO(&wfds);
			FD_SET(*sd, &wfds);
			rfds = wfds;
			
			/* wait for readiness */
			result = select((*sd) + 1, &rfds, &wfds, NULL, &tv);
			
			/*printf("SELECT RESULT: %d\n",result);*/
			
			/* timeout */
			if(result == 0) {
				/*printf("TIMEOUT\n");*/
				result = -1;
				break;
			}
			
			/* an error occurred */
			if(result < 0 && errno != EINTR) {
				result = -1;
				break;
			}
			
			/* got something - check it */
			else if(result > 0) {
				
				/* get socket options to check for errors */
				optlen = sizeof(int);
				if(getsockopt(*sd, SOL_SOCKET, SO_ERROR, (void *)(&optval), &optlen) < 0) {
					result = -1;
					break;
				}
				
				/* an error occurred in the connection */
				if(optval != 0) {
					result = -1;
					break;
				}
				
				/* the connection was good! */
				result = 1;
				break;
			}
			
			else {
				result = -1;
				break;
			}
			
		}
		while(1);
	}
	return result;
}



