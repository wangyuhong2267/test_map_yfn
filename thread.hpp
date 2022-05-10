//
//  thread.hpp
//  test_map
//
//  Created by wangyuhong2267 on 17/3/1.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#ifndef thread_hpp
#define thread_hpp

#include <stdio.h>
#include "const.h"
#include "static_var.hpp"
#include "tcp_socket.hpp"
class Cthread
{
public:
	Cthread();
	virtual ~Cthread();
	pthread_t   pthreadid_jiaxing;
	pthread_attr_t attr_jiaxing;
	
	pthread_t   pthreadid_ninghai;
	pthread_attr_t attr_ninghai;
	
	pthread_t   pthreadid_time;
	pthread_attr_t attr_time;
	
	pthread_t   pthreadid_cid_05_00;
	pthread_attr_t attr_cid_05_00;
public:
	static Cthread* p_inst;
	
	static Cthread *get_instance();
	void test_print();
	
	void create_thread_jiaxing();
	static void * ThreadHandle_jiaxing(void *args);
	void create_thread_ninghai();
	static void * ThreadHandle_ninghai(void *args);
	
	void create_thread_time();
	static void* ThreadHandle_time(void* args);
	
	void create_thread_cid_05_00();
	static void* ThreadHandle_cid_05_00(void* args);
	
	/////////////////////////////////////////////////
	static void command_handle_apns(unsigned char *cmd,int sock_recv);
};
#endif
	
	/* thread_hpp */
