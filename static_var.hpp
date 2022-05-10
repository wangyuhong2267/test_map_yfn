//
//  static_var.hpp
//  test_map
//
//  Created by wangyuhong2267 on 17/2/26.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#ifndef static_var_hpp
#define static_var_hpp

#include <stdio.h>
#include "const.h"
#include "static_func.hpp"
#include "person.h"
#include "csv.hpp"
#include "original_ssl_client.h"
class Cstatic_var
{
public:
	static bool bool_thread_epool_recv;
	static bool bool_thread_ping;
	static bool bool_connect_apns_status_ping;
	static bool bool_connect_apns_status_ssl_handshake;
	static std::mutex mutex_map_event_cid_05_00;
	static std::mutex mutex_map_alarm_event_cid;
	static std::mutex mutex_map_machine;
	static std::mutex mutex_map_phone;
	static std::mutex mutex_map_language;
	static unsigned int tmie_count;
	static original_ssl_client test_ssl_client;
	
	static map<string,shared_ptr<Cmachine_info>> map_phone;
	static map<string,shared_ptr<Cmachine_info_language>> map_phone_language;
	static map<string,shared_ptr<list<Cphone_info>>> map_machine;
	
	static map<string,shared_ptr<list<Calarm_event_cid_info>>> map_alarm_cid;
	static map<string,shared_ptr<list<Cmachine_05_00_cid_info>>> map_event_cid_05_00;
	
	static unsigned int time_calculate_three_second;
	static unsigned int time_calculate_three_second2;
	///////////////////////////////////////////////////////
	
	static int socket_fd_jiaxing;
	static struct epoll_event events_jiaxing[MAX_EVENTS];


	static Cstatic_func *p_static_func;
	static person *p_static_person;
	static csv *p_csv;
	static struct server_info ServerInfo[MAX_USER_NUMBER];
	
	
	////////////////////////////////////////////////////////
	static time_t time_nghttp2_ping_send;
	static time_t time_nghttp2_ping_recv;
	
	
	
	
	Cstatic_var();
	virtual ~Cstatic_var();
	

	////////////////////////////////////////////////////////
	
	
	static void Close(int fd);
	static int  query_machine_push_status(string str_machine_account);
	static void server_info_init_time(unsigned int conn_number);
	static void server_info_init(unsigned int conn_number);
	static void server_info_init2(unsigned int conn_number);
	
	//////////////////////////////////////////////////////////
	
	static void send_cmd_to_server(unsigned int index,unsigned char *cmd);
	static void send_cmd_to_server_0e_03(int sock_recv,unsigned char *cmd);
	static void send_delete_success_to_app_0f_02(unsigned int conn_number,int sock_recv,int para);
	static void send_clear_badges_to_app_0f_03(unsigned int conn_number,int sock_recv,int para);
	static void send_clear_badges_to_app_0f_04(unsigned int conn_number,int sock_recv,unsigned int nums_cid,char *buf_cid);
	static void send_heart_beat_to_server(unsigned int index);
	static void reconn_server();
	static void reconn_server2();
	static void res_release_apns_server();
	
	//////////////////////////////////////////////////////////////
	static void apns_push(char *device_token,char *payload,int num);
	//static void apns_push();
	static void apns_connect();
	static void nghttp2_ping_init_time();
	static void nghttp2_reconnect();
	static void apns_connection_cleanup();
	static void apns_push_message(string str_machine_account,char * chstr_cid);
	///////////////////////////////////////////////////////////////
	static void handle_feedback();
	static void release_resource_apns_session();
};
#endif /* static_var_hpp */
