//
//  static_var.cpp
//  test_map
//
//  Created by wangyuhong2267 on 17/2/26.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#include "static_var.hpp"
#include "tcp_socket.hpp"

#include "nghttp2_push.h"

///////////////////////////////////////////////////////////////////
bool Cstatic_var::bool_thread_ping = true;
bool Cstatic_var::bool_thread_epool_recv = true;
bool Cstatic_var::bool_connect_apns_status_ping = false;
bool Cstatic_var::bool_connect_apns_status_ssl_handshake = false;

std::mutex Cstatic_var::mutex_map_event_cid_05_00;
std::mutex Cstatic_var::mutex_map_alarm_event_cid;
std::mutex Cstatic_var::mutex_map_machine;
std::mutex Cstatic_var::mutex_map_phone;
std::mutex Cstatic_var::mutex_map_language;
unsigned int Cstatic_var::tmie_count = 0;
original_ssl_client Cstatic_var::test_ssl_client;

map<string,shared_ptr<Cmachine_info>> Cstatic_var::map_phone;
map<string,shared_ptr<Cmachine_info_language>> Cstatic_var::map_phone_language;
map<string,shared_ptr<list<Cphone_info>>> Cstatic_var::map_machine;

map<string,shared_ptr<list<Calarm_event_cid_info>>> Cstatic_var::map_alarm_cid;

map<string,shared_ptr<list<Cmachine_05_00_cid_info>>> Cstatic_var::map_event_cid_05_00;


int Cstatic_var::socket_fd_jiaxing = -1;
unsigned int Cstatic_var::time_calculate_three_second = 0;
unsigned int Cstatic_var::time_calculate_three_second2 = 0;


struct epoll_event Cstatic_var::events_jiaxing[MAX_EVENTS];

/////////////////////////////////////////////////////////////
struct server_info Cstatic_var::ServerInfo[MAX_USER_NUMBER];


time_t Cstatic_var::time_nghttp2_ping_send = time((time_t *)NULL);
time_t Cstatic_var::time_nghttp2_ping_recv = time((time_t *)NULL);

//////////////////////////////////////////////////////////////

Cstatic_func *Cstatic_var::p_static_func = Cstatic_func::get_instance();
person *Cstatic_var::p_static_person = person::get_instance();
csv *Cstatic_var::p_csv = csv::get_instance();

Cstatic_var::Cstatic_var()
{
	
}

Cstatic_var::~Cstatic_var()
{
	
}

void Cstatic_var::server_info_init_time(unsigned int conn_number)
{
	Cstatic_var::ServerInfo[conn_number].time_start_server = time((time_t *)NULL);
	Cstatic_var::ServerInfo[conn_number].time_end_server = time((time_t *)NULL);
}


void Cstatic_var::server_info_init(unsigned int conn_number)
{
	
	memset(Cstatic_var::ServerInfo[conn_number].str_ip_address,0,sizeof(Cstatic_var::ServerInfo[conn_number].str_ip_address));
	Cstatic_var::ServerInfo[conn_number].bHave_server = false;
	Cstatic_var::ServerInfo[conn_number].bUsed = false;
	Cstatic_var::ServerInfo[conn_number].epfd_server = -1;
	Cstatic_var::ServerInfo[conn_number].sockfd_server = - 1;
	server_info_init_time(conn_number);
	
}
void Cstatic_var::server_info_init2(unsigned int conn_number)
{
	if(Cstatic_var::ServerInfo[conn_number].sockfd_server != -1)
	{
		Cstatic_var::Close(Cstatic_var::ServerInfo[conn_number].sockfd_server);
		Cstatic_var::ServerInfo[conn_number].sockfd_server = -1;
	}
	
	
	if(Cstatic_var::ServerInfo[conn_number].epfd_server != -1)
	{
		Cstatic_var::Close(Cstatic_var::ServerInfo[conn_number].epfd_server);
		Cstatic_var::ServerInfo[conn_number].epfd_server = -1;
	}
	//memset(Cstatic_var::ServerInfo[conn_number].str_ip_address,0,sizeof(Cstatic_var::ServerInfo[conn_number].str_ip_address));
	//Cstatic_var::ServerInfo[conn_number].bHave_server = false;
	Cstatic_var::ServerInfo[conn_number].bUsed = false;
	Cstatic_var::ServerInfo[conn_number].epfd_server = -1;
	Cstatic_var::ServerInfo[conn_number].sockfd_server = - 1;
	server_info_init_time(conn_number);
	
}
void Cstatic_var::send_cmd_to_server(unsigned int index,unsigned char *cmd)
{
	int len_std_a = 0;
	int len_std_b = 0;
	if(cmd[7] < 58)
	{
		len_std_a = cmd[7] - 48;
	}
	else if((cmd[7] >= 65) && (cmd[7] <= 70))
	{
		len_std_a = cmd[7] - 55;
	}
	if(cmd[8] < 58)
	{
		len_std_b = cmd[8] - 48;
	}
	else if((cmd[8] >= 65) && (cmd[7] <= 70))
	{
		len_std_b = cmd[8] - 55;
	}
	unsigned int len_standard = len_std_a * 16 + len_std_b;
	unsigned int len_pri = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
	unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;
	
	//printf("len_standard=%d,len_pri=%d,len_total=%d\n",len_standard,len_pri,len_total);
	int len_temp = len_standard + PUBLIC_SIZE + 10;
	//////////////////////////////////////////////////////////////////////////////////
	
	unsigned int big_class = cmd[len_temp];
	unsigned int small_class = cmd[len_temp + 1];
	
	
	//crc_private
	char buf_len[5];
	unsigned int crc_value_private = p_static_func->calcCRC_buf(&cmd[len_standard + 10 + 2],len_pri);
	p_static_func->NumToHex_4(crc_value_private,buf_len);
	for(int i = 0;i < 4;i++)
	{
		cmd[len_total -(4 - i)] = buf_len[i];
	}
	
	
	/////////////////////////////////////////////////////////////
	
	
	int ret2 = send(Cstatic_var::ServerInfo[index].sockfd_server,(char *)cmd,len_total,0);
	printf("send_cmd_to_server,big_class=%02x, small_class=%02x,send to phone,ret2=%d\n",
		   big_class, small_class,ret2);
	
}

void Cstatic_var::send_cmd_to_server_0e_03(int sock_recv,unsigned char *cmd)
{
	int len_std_a = 0;
	int len_std_b = 0;
	if(cmd[7] < 58)
	{
		len_std_a = cmd[7] - 48;
	}
	else if((cmd[7] >= 65) && (cmd[7] <= 70))
	{
		len_std_a = cmd[7] - 55;
	}
	if(cmd[8] < 58)
	{
		len_std_b = cmd[8] - 48;
	}
	else if((cmd[8] >= 65) && (cmd[7] <= 70))
	{
		len_std_b = cmd[8] - 55;
	}
	unsigned int len_standard = len_std_a * 16 + len_std_b;
	unsigned int len_pri = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
	unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;
	
	//printf("len_standard=%d,len_pri=%d,len_total=%d\n",len_standard,len_pri,len_total);
	int len_temp = len_standard + PUBLIC_SIZE + 10;
	//////////////////////////////////////////////////////////////////////////////////
	
	unsigned int big_class = cmd[len_temp];
	unsigned int small_class = cmd[len_temp + 1];
	
	
	//crc_private
	char buf_len[5];
	unsigned int crc_value_private = p_static_func->calcCRC_buf(&cmd[len_standard + 10 + 2],len_pri);
	p_static_func->NumToHex_4(crc_value_private,buf_len);
	for(int i = 0;i < 4;i++)
	{
		cmd[len_total -(4 - i)] = buf_len[i];
	}
	
	
	/////////////////////////////////////////////////////////////
	
	
	int ret2 = send(Cstatic_var::ServerInfo[0].sockfd_server,(char *)cmd,len_total,0);
	int ret3 = send(Cstatic_var::ServerInfo[1].sockfd_server,(char *)cmd,len_total,0);
	//int ret2 = send(sock_recv,(char *)cmd,len_total,0);
	printf("send_cmd_towe_chat,big_class=%02x, small_class=%02x,send to phone,ret2=%d\n",
		   big_class, small_class,ret2);
	printf("send_cmd_towe_chat,big_class=%02x, small_class=%02x,send to phone,ret3=%d\n",
		   big_class, small_class,ret3);
	
}

void Cstatic_var::send_heart_beat_to_server(unsigned int index)
{
	unsigned char buf[1460];
	char buf_len[5];
	int i;
	memset(buf,0,sizeof(buf));
	int len_ip_event = p_static_func->create_ip_standard_event(buf,ACCT_ID,ACCT_SEQ,ACCT_RRCVR,
												ACCT_LPREF,ACCT_MACHINE);
	//printf("len_ip_event=%d\n",len_ip_event);
	if(p_static_func->exception_len_ip_event(len_ip_event,0,"send_connnumber_tophone"))
	{
		return;
	}
	/////////////////////////////////////////////////////////////////////////////////////
	//private public cmd
	int length_private = 29 + 5;
	int len_toacct = len_ip_event;
	p_static_func->create_pricmd_public_29(buf,len_toacct,length_private,
							"FFFFFFFFFFF","123456","FFFFFFFFFFF",2);
	//printf("length_private=%d\n",length_private);
	int len_tolevel = len_toacct + 9 + 9 - 1 + 4 + 2;
	buf[len_tolevel + 8] = 0x0F;
	buf[len_tolevel + 9] = 0x01;
	buf[len_tolevel + 10] = (index >> 16) & 0xff;
	buf[len_tolevel + 11] = (index >> 8) & 0xff;
	buf[len_tolevel + 12] = index & 0xff;
	//crc_private
	unsigned int crc_value_private = p_static_func->calcCRC_buf(&buf[len_toacct + 2],length_private);
	p_static_func->NumToHex_4(crc_value_private,buf_len);
	for(i = 0;i < 4;i++)
	{
		buf[len_tolevel + 13 + i] = buf_len[i];
	}
	send_cmd_to_server(index,buf);
	

	
}
void Cstatic_var::reconn_server()
{
	
//	Ctcp_socket *p_tcp_sock = Ctcp_socket::get_instance();
//	int ret_conn = p_tcp_sock->tcp_connect_timeout (&(Cstatic_var::socket_fd_jiaxing), 6 ,(char*)"192.168.1.129",7894);
//	printf("reconn_server,ret_conn=%d\n",ret_conn);
//	if (ret_conn > 0) {
//		Cstatic_var::bUsing_jiaxing = true;
//		for (int i = 0; i < MAX_USER_NUMBER; i++) {
//			if (!Cstatic_var::ServerInfo[i].bUsed) {
//				Cstatic_var::ServerInfo[i].bUsed = true;
//				Cstatic_var::ServerInfo[i].epfd_server = Cstatic_var::p_static_func->EpollConfig(Cstatic_var::socket_fd_jiaxing,false);;
//				Cstatic_var::ServerInfo[i].sockfd_server = Cstatic_var::socket_fd_jiaxing;
//				Cstatic_var::server_info_init_time(i);
//				printf("reconn_server,i=%d\n",i);
//				break;
//				
//			}
//		}
//	}
	/////////////////////////////////////////////////////////////////////////////////////
}
void Cstatic_var::reconn_server2()
{
	
	////////////////////////////////////////////////////////////////////////////////
	
	
	for (int i = 0; i < MAX_USER_NUMBER; i++)
	{
		if (Cstatic_var::ServerInfo[i].bHave_server) {
			Ctcp_socket *p_tcp_sock = Ctcp_socket::get_instance();
			//int ret_conn = p_tcp_sock->tcp_connect_timeout (&(Cstatic_var::ServerInfo[i].sockfd_server), 6 ,Cstatic_var::ServerInfo[i].str_ip_address,7890);
			int ret_conn = p_tcp_sock->tcp_connect_timeout (&(Cstatic_var::ServerInfo[i].sockfd_server), 6 ,Cstatic_var::ServerInfo[i].str_ip_address,7894);
			printf("reconn_server2,i=%d,ret_conn=%d\n",i,ret_conn);

				
			if (ret_conn > 0) {
				Cstatic_var::ServerInfo[i].bUsed = true;

				Cstatic_var::ServerInfo[i].epfd_server = Cstatic_var::p_static_func->EpollConfig(Cstatic_var::ServerInfo[i].sockfd_server,false);;
				Cstatic_var::server_info_init_time(i);
				
			}else{
				Cstatic_var::server_info_init2(i);
			}
			/////////////////////////////////////////////
			if (!Cstatic_var::ServerInfo[i].bHave_server) {
				break;
			}
		}
		
	}
	
	/////////////////////////////////////////////////////////////////////////////////////
}
void Cstatic_var::res_release_apns_server()
{
	
	int i;
	time_t seconds_interval = 0;
	for(i=0;i<MAX_USER_NUMBER_APNS;i++)
	{
		if (i < 2) {
			//printf("res_release_apns_server,Cstatic_var::ServerInfo[%d].bUsed=%d\n",i,Cstatic_var::ServerInfo[i].bUsed);
		}
		
		if(Cstatic_var::ServerInfo[i].bUsed)
		{
			
			Cstatic_var::ServerInfo[i].time_end_server = time((time_t *)NULL);
			seconds_interval = Cstatic_var::ServerInfo[i].time_end_server - Cstatic_var::ServerInfo[i].time_start_server;
			//printf("res_release_apns_server,i=%d,seconds_interval=%ld\n",i,seconds_interval);
			if(seconds_interval >= HEARTBEAT_INTERVAL_APNS_THREE_THIME)
			{
				
				if ((Cstatic_var::ServerInfo[i].bHave_server) && (Cstatic_var::ServerInfo[i].bUsed))
				{
					Cstatic_var::server_info_init2(i);
					
				}
	
			}
		}
		

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Cstatic_var::apns_connection_cleanup()
{
	try{
		connection_cleanup(&conn);

	}
	catch(...){
		printf("apns_connection_cleanup,catch error...\n");
	}
	
	
}
void Cstatic_var::apns_push(char *device_token,char *payload,int num)
//void Cstatic_var::apns_push()
{
	//printf("%s\n",__FUNCTION__);
	char * array1 = alloc_string("{\"aps\":{\"alert\":");
	//char * array2 = alloc_string("\"wangyuhong...\"");
	//char * array3 = alloc_string(",\"badge\":\"...\",\"sound\":\"default\",\"content-available\":1}}");
//	int num = 99;
//	char str4[6];
//	memset(str4,0,sizeof(str4));
//	string str_num = std::to_string(num);
	string str_num = std::to_string(1);

//	char * array3 = alloc_string(",\"badtege\":");
	char * array3 = alloc_string(",\"badge\":");
//	char * array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
//    char * array3 = alloc_string(",\"badge\":");
//	char * array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
    char * array5;
    if(num == -1){
        array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
    }else if(num == 1){
        array5 = alloc_string(",\"sound\":\"sound_fire.wav\",\"content-available\":0}}");
    }else if(num == 2){
        array5 = alloc_string(",\"sound\":\"sound_gas.wav\",\"content-available\":0}}");
    }else if(num == 3){
        array5 = alloc_string(",\"sound\":\"sound_water.wav\",\"content-available\":0}}");
    }else if(num == 99){
        array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
    }else{
        array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
    }
//    char * array5 = alloc_string(",\"sound\":\"sos2.wav\",\"content-available\":0}}");

	//char * array2 = "\"wangyuhong...\"";
	opt.token = alloc_string(device_token);
	check_and_make_opt(&opt);
	//init_global_library();
	//	opt.payload  = alloc_string("{\"aps\":{\"alert\":\"wangyuhong...\",\"sound\":\"default\"}}");
	char str[1024];
	memset(str,0,sizeof(str));
	strcat(str,array1);
	//strcat(str,array2);
	strcat(str,"\"");
	strcat(str,payload);
	strcat(str,"\"");
	strcat(str,array3);
	/////////////////////////
	strcat(str,str_num.c_str());
	strcat(str,array5);
	opt.payload  = alloc_string(str);
	blocking_post(&loop, &conn, &opt);
	
}


void Cstatic_var::apns_push_yfn(char *device_token,char *payload,int event_type,int num)
//void Cstatic_var::apns_push()
{
	//printf("%s\n",__FUNCTION__);
	char * array1 = alloc_string("{\"aps\":{\"alert\":");
	//char * array2 = alloc_string("\"wangyuhong...\"");
	//char * array3 = alloc_string(",\"badge\":\"...\",\"sound\":\"default\",\"content-available\":1}}");
//	int num = 99;
//	char str4[6];
//	memset(str4,0,sizeof(str4));
//	string str_num = std::to_string(num);
	string str_num = std::to_string(num);

//	char * array3 = alloc_string(",\"badtege\":");
	char * array3 = alloc_string(",\"badge\":");
//	char * array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
//    char * array3 = alloc_string(",\"badge\":");
//	char * array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
    char * array5;
    if(event_type == -1){
        array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
    }else if(event_type == 1){
        array5 = alloc_string(",\"sound\":\"sound_fire.wav\",\"content-available\":0}}");
    }else if(event_type == 2){
        array5 = alloc_string(",\"sound\":\"sound_gas.wav\",\"content-available\":0}}");
    }else if(event_type == 3){
        array5 = alloc_string(",\"sound\":\"sound_water.wav\",\"content-available\":0}}");
    }else if(event_type == 4){
        array5 = alloc_string(",\"sound\":\"hb_52.wav\",\"content-available\":0}}");
    }else if(event_type == 5){
        array5 = alloc_string(",\"sound\":\"sos.wav\",\"content-available\":0}}");
    }else if(event_type == 99){
        array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
    }else{
        array5 = alloc_string(",\"sound\":\"default\",\"content-available\":0}}");
    }
//    char * array5 = alloc_string(",\"sound\":\"sos2.wav\",\"content-available\":0}}");

	//char * array2 = "\"wangyuhong...\"";
	opt.token = alloc_string(device_token);
	check_and_make_opt(&opt);
	//init_global_library();
	//	opt.payload  = alloc_string("{\"aps\":{\"alert\":\"wangyuhong...\",\"sound\":\"default\"}}");
	char str[1024];
	memset(str,0,sizeof(str));
	strcat(str,array1);
	//strcat(str,array2);
	strcat(str,"\"");
	strcat(str,payload);
	strcat(str,"\"");
	strcat(str,array3);
    strcat(str,str_num.c_str());
	/////////////////////////

	strcat(str,array5);
	printf("apns_push_yfn,str=%s\n",str);
	opt.payload  = alloc_string(str);
	blocking_post(&loop, &conn, &opt);

}

void Cstatic_var::apns_connect()
{
	printf("%s\n",__FUNCTION__);
	debug("apns2-test version: %s\n", APNS2_TEST_VERSION);
	debug("nghttp2 version: %s\n", NGHTTP2_VERSION);
	debug("tls/ssl version: %s\n", SSL_TXT_TLSV1_2);
	(&opt)->token    = alloc_string("e1af8514bb66cd8c52c9a74523292ea08395ad7a6688e250c386839761cba13c");
	check_and_make_opt(&opt);
	init_global_library();
	
	bool bool_flag = socket_connect(opt.uri, opt.port, &conn);
	if (!bool_flag) {
		printf("apns_connect fail......\n");
		return;
	}
	if(!ssl_connect(opt.cert, opt.pkey, &conn))
		die("ssl connect fail.");
	set_nghttp2_session_info(&conn);
	Cstatic_var::apns_push(alloc_string("dc17a00ccd89103b7a265b831f8a059ce1845ebd35141413402a13fd84008133"),alloc_string("asdfghjkl"),1);
	create_thread_recv_epool_nghttp2();
	create_thread_nghttp2_ping();
//	Cstatic_var::apns_push(alloc_string("dc17a00ccd89103b7a265b831f8a059ce1845ebd35141413402a13fd84008133"),alloc_string("asdfghjkl"));
//	if(tmp == 0)
//	{
//		
//		printf("%s,tmp=%d\n",__FUNCTION__,tmp);
//		tmp++;
//		event_loop(&loop,&conn);
//		
//	}
	//blocking_post(&loop, &conn, &opt);
	
}
void Cstatic_var::nghttp2_ping_init_time()
{
	Cstatic_var::time_nghttp2_ping_send = time((time_t *)NULL);
	Cstatic_var::time_nghttp2_ping_recv = time((time_t *)NULL);
}
void Cstatic_var::nghttp2_reconnect()
{
	//printf("%s\n",__FUNCTION__);
	try{
		time_t time_temp = time((time_t *)NULL);
		time_t time_several = time_temp - Cstatic_var::time_nghttp2_ping_recv;
		//printf("nghttp2_reconnect,time_several=%lu\n",time_several);
		if((time_several) >= HEARTBEAT_INTERVAL_APNS_THREE_THIME)
		{
			Cstatic_var::release_resource_apns_session();
		}
		
	}
	catch(...){
		printf("nghttp2_reconnect,catch error...\n");
	}
	
	
	
}
int  Cstatic_var::query_machine_push_status(string str_machine_account)
{
	int m_count_machine_map = Cstatic_var::map_machine.size();
	//printf("apns_push_message,m_count_machine_map=%d\n",m_count_machine_map);
	string s = str_machine_account;
	
	map<string,shared_ptr<list<Cphone_info>>>::iterator it2;
	it2 = Cstatic_var::map_machine.find(s);
	int length = Cstatic_var::map_machine.count(s);
	//printf("apns_push_message,length=%d\n",length);
	int count_temp = -1;
	if (length > 0) {
		//printf("apns_push_message,machine_account=%s\n",it2->first.c_str());
		shared_ptr<list<Cphone_info>> plist_temp22 = it2->second;
		int size_list = plist_temp22->size();
		if (size_list >= 0) {
			count_temp = 1;
		}
			
		
	}
	return count_temp;
	
	
}
void Cstatic_var::apns_push_message(string str_machine_account,char * chstr_cid)
{
	int m_count_machine_map = Cstatic_var::map_machine.size();
	//printf("apns_push_message,m_count_machine_map=%d\n",m_count_machine_map);
	string s = str_machine_account;

	map<string,shared_ptr<list<Cphone_info>>>::iterator it2;
	it2 = Cstatic_var::map_machine.find(s);
	int length = Cstatic_var::map_machine.count(s);
	//printf("apns_push_message,length=%d\n",length);
	if (length > 0) {
		//printf("apns_push_message,machine_account=%s\n",it2->first.c_str());
		shared_ptr<list<Cphone_info>> plist_temp22 = it2->second;
		for (list<Cphone_info>::iterator it22 = plist_temp22->begin(); it22!=plist_temp22->end(); it22++) {
			string  str_device_tocken = it22->phone_device_tocken;
			string  str_phone_account = it22->phone_account;

			//printf("apns_push_message,phone_account=%s\n",it22->phone_account.c_str());
			//printf("apns_push_message,phone_device_tocken=%s\n",it22->phone_device_tocken.c_str());
		
			string str_cid = chstr_cid;
			string str_cid_chinese_or_english = "";
			string str_language = "";



			if (1) {
				lock_guard<mutex> guard(std::mutex mutex_map_language);
				str_language = Cstatic_var::p_static_person->get_language_from_map_phone(it22->phone_device_tocken);
			}


            int type_event = 0;
            type_event = Cstatic_var::p_static_person->get_event_type(str_cid,str_language);
            if (str_machine_account == "866569060902449") {
                printf("apns_push_message,type_event=%d\n",type_event);
                printf("apns_push_message,str_cid=%s\n",str_cid.c_str());
                printf("apns_push_message,str_language=%s\n",str_language.c_str());

            }


//			Cstatic_var::p_static_person->cid_to_chinese_or_english_cid(str_cid,str_cid_chinese_or_english,str_language);
			Cstatic_var::p_static_person->cid_to_chinese_or_english_cid_yfn(str_cid,str_cid_chinese_or_english,str_language);
			//printf("apns_push_message,str_language=%s\n",str_language.c_str());
			printf("apns_push_message,str_cid_chinese_or_english=%s\n",str_cid_chinese_or_english.c_str());
			int num = 0;
			if (1)
			{
				lock_guard<mutex> guard(std::mutex mutex_map_phone);
				
				string str_badge_identification = Cstatic_var::p_static_person->get_badge_identification_from_map_phone(str_device_tocken);
				if (str_badge_identification != "") {
					istringstream iss(str_badge_identification);
					
					iss >> num;
					//printf("apns_push_message,num=%d\n",num);
				}
				num++;
			}
			
			if (1)
			{



				lock_guard<mutex> guard(std::mutex mutex_map_phone);
				Cstatic_var::p_static_person->delete_from_map_phone(str_device_tocken);
				
				Cstatic_var::p_static_person->insert_phone_map(str_device_tocken,str_phone_account,str_machine_account,std::to_string(num));
				
//				Cstatic_var::apns_push(alloc_string(it22->phone_device_tocken.c_str()),(char *)str_cid_chinese_or_english.c_str(),type_event);
				Cstatic_var::apns_push_yfn(alloc_string(it22->phone_device_tocken.c_str()),(char *)str_cid_chinese_or_english.c_str(),type_event,num);

//				if (num >= 1) {
//					Cstatic_var::apns_push(alloc_string(it22->phone_device_tocken.c_str()),(char *)str_cid_chinese_or_english.c_str(),1);
//				}
				
			}
			
			
		}
	}
	
	
	
}
void Cstatic_var::handle_feedback()
{
	//if(Cstatic_var::tmie_count == 86400)
	if(Cstatic_var::tmie_count == 15)
	{
		Cstatic_var::tmie_count = 0;
		char chstr_device_tocken[65];
		memset(chstr_device_tocken,0,sizeof(chstr_device_tocken));
		int len_feedback = Cstatic_var::test_ssl_client.ssl_read_data(chstr_device_tocken);
		printf("handle_feedback,len_feedback=%d,chstr_device_tocken=%s\n",len_feedback,chstr_device_tocken);
		if (len_feedback == 38) {
			string str_device_tocken = chstr_device_tocken;
			printf("handle_feedback,len_feedback=%d,str_device_tocken=%s\n",len_feedback,str_device_tocken.c_str());
			string str_mahcine_acocunt = Cstatic_var::p_static_person->get_mahcine_account_from_map_phone(str_device_tocken);
			if (str_mahcine_acocunt != "") {
				lock_guard<mutex> guard(std::mutex mutex_map_machine);
				Cstatic_var::p_static_person->delete_from_map_machine(str_mahcine_acocunt,str_device_tocken);
				Cstatic_var::p_static_person->delete_from_map_phone(str_device_tocken);
			}
			
		}
		while (len_feedback != 0) {
			printf("handle_feedback,while......\n");
			len_feedback = Cstatic_var::test_ssl_client.ssl_read_data(chstr_device_tocken);
			printf("handle_feedback,len_feedback=%d,chstr_device_tocken=%s\n",len_feedback,chstr_device_tocken);
			if (len_feedback == 38) {
				string str_device_tocken = chstr_device_tocken;
				string str_mahcine_acocunt = Cstatic_var::p_static_person->get_mahcine_account_from_map_phone(str_device_tocken);
				if (str_mahcine_acocunt != "") {
					lock_guard<mutex> guard(std::mutex mutex_map_machine);
					Cstatic_var::p_static_person->delete_from_map_machine(str_mahcine_acocunt,str_device_tocken);
					Cstatic_var::p_static_person->delete_from_map_phone(str_device_tocken);
				}
				
			}
		}
		
	}
	Cstatic_var::tmie_count++;
}
void Cstatic_var::release_resource_apns_session(){
	
	/////////////////////////////////////////////
	Cstatic_var::bool_thread_epool_recv = false;
	Cstatic_var::bool_thread_ping = false;
	if (Cstatic_var::bool_connect_apns_status_ping)
	{
		int res;
		printf("nghttp2_reconnect，aaa......\n");
		try{
			void *thread_result;
			if(pthreadid_recv_epool != (pthread_t)NULL){
				
				int res = pthread_cancel(pthreadid_recv_epool);
				if (res != 0) {
					perror("cancel thread failure...");
					//exit(EXIT_FAILURE);
				}
				printf("wait thread failure...\n");
				res = pthread_join(pthreadid_recv_epool, &thread_result);
				if (res != 0) {
					perror("end thread failure...");
					//exit(EXIT_FAILURE);
				}
				else{
					printf("end thread success...\n");
				}
			}
			
		}
		catch(...){
			printf("apns_connection_cleanup,catch error...\n");
		}
		printf("nghttp2_reconnect，bbb......\n");
		////////////////////////////////////////////////////////
		try{
			void *thread_result2;
			if(pthreadid_nghttp2_ping != (pthread_t)NULL){
				
				res = pthread_cancel(pthreadid_nghttp2_ping);
				if (res != 0) {
					perror("cancel thread failure...");
					//exit(EXIT_FAILURE);
				}
				printf("wait thread failure...\n");
				res = pthread_join(pthreadid_nghttp2_ping, &thread_result2);
				if (res != 0) {
					perror("end thread failure...");
					//exit(EXIT_FAILURE);
				}
				else{
					printf("end thread success...\n");
				}
				////////////////////////////////////////////////////////
				printf("nghttp2_reconnect，fff......\n");
			}
		}
		catch(...){
			printf("apns_connection_cleanup,catch error...\n");
		}
		
	}
	Cstatic_var::bool_connect_apns_status_ping = false;
	Cstatic_var::bool_connect_apns_status_ssl_handshake = false;
	Cstatic_var::bool_thread_epool_recv = true;
	Cstatic_var::bool_thread_ping = true;
	
	//if (Cstatic_var::bool_connect_apns_status_ssl_handshake)
	{
		
		tmp = 0;
		Cstatic_var::nghttp2_ping_init_time();
		if (Cstatic_var::bool_connect_apns_status_ping)
		{
			Cstatic_var::apns_connection_cleanup();
		}
		
		Cstatic_var::apns_connect();
	}

}

void Cstatic_var::send_delete_success_to_app_0f_02(unsigned int conn_number,int sock_recv,int para)
{
	unsigned char buf[1460];
	char buf_len[5];
	int i;
	memset(buf,0,sizeof(buf));
	int len_ip_event = p_static_func->create_ip_standard_event(buf,ACCT_ID,ACCT_SEQ,ACCT_RRCVR,
															   ACCT_LPREF,ACCT_MACHINE);
	//printf("len_ip_event=%d\n",len_ip_event);
	if(p_static_func->exception_len_ip_event(len_ip_event,0,"send_connnumber_tophone"))
	{
		return;
	}
	/////////////////////////////////////////////////////////////////////////////////////
	//private public cmd
	int length_private = 29 + 6;
	int len_toacct = len_ip_event;
	p_static_func->create_pricmd_public_29(buf,len_toacct,length_private,
										   "FFFFFFFFFFF","123456","FFFFFFFFFFF",2);
	//printf("length_private=%d\n",length_private);
	int len_tolevel = len_toacct + 9 + 9 - 1 + 4 + 2;
	buf[len_tolevel + 8] = 0x0F;
	buf[len_tolevel + 9] = 0x02;
	buf[len_tolevel + 10] = (conn_number >> 16) & 0xff;
	buf[len_tolevel + 11] = (conn_number >> 8) & 0xff;
	buf[len_tolevel + 12] = conn_number & 0xff;
	buf[len_tolevel + 13] = para & 0xff;
	//crc_private
	unsigned int crc_value_private = p_static_func->calcCRC_buf(&buf[len_toacct + 2],length_private);
	p_static_func->NumToHex_4(crc_value_private,buf_len);
	for(i = 0;i < 4;i++)
	{
		buf[len_tolevel + 14 + i] = buf_len[i];
	}
	send_cmd_to_server_0e_03(sock_recv,buf);
	
	
	
}
void Cstatic_var::send_clear_badges_to_app_0f_03(unsigned int conn_number,int sock_recv,int para)
{
	unsigned char buf[1460];
	char buf_len[5];
	int i;
	memset(buf,0,sizeof(buf));
	int len_ip_event = p_static_func->create_ip_standard_event(buf,ACCT_ID,ACCT_SEQ,ACCT_RRCVR,
															   ACCT_LPREF,ACCT_MACHINE);
	//printf("len_ip_event=%d\n",len_ip_event);
	if(p_static_func->exception_len_ip_event(len_ip_event,0,"send_connnumber_tophone"))
	{
		return;
	}
	/////////////////////////////////////////////////////////////////////////////////////
	//private public cmd
	int length_private = 29 + 6;
	int len_toacct = len_ip_event;
	p_static_func->create_pricmd_public_29(buf,len_toacct,length_private,
										   "FFFFFFFFFFF","123456","FFFFFFFFFFF",2);
	//printf("length_private=%d\n",length_private);
	int len_tolevel = len_toacct + 9 + 9 - 1 + 4 + 2;
	buf[len_tolevel + 8] = 0x0F;
	buf[len_tolevel + 9] = 0x03;
	buf[len_tolevel + 10] = (conn_number >> 16) & 0xff;
	buf[len_tolevel + 11] = (conn_number >> 8) & 0xff;
	buf[len_tolevel + 12] = conn_number & 0xff;
	buf[len_tolevel + 13] = para & 0xff;
	//crc_private
	unsigned int crc_value_private = p_static_func->calcCRC_buf(&buf[len_toacct + 2],length_private);
	p_static_func->NumToHex_4(crc_value_private,buf_len);
	for(i = 0;i < 4;i++)
	{
		buf[len_tolevel + 14 + i] = buf_len[i];
	}
	send_cmd_to_server_0e_03(sock_recv,buf);
	
	
	
}
void Cstatic_var::send_clear_badges_to_app_0f_04(unsigned int conn_number,int sock_recv,unsigned int nums_cid,char *buf_cid)
{
	unsigned char buf[1460];
	char buf_len[5];
	int i;
	memset(buf,0,sizeof(buf));
	int len_ip_event = p_static_func->create_ip_standard_event(buf,ACCT_ID,ACCT_SEQ,ACCT_RRCVR,
															   ACCT_LPREF,ACCT_MACHINE);
	//printf("len_ip_event=%d\n",len_ip_event);
	if(p_static_func->exception_len_ip_event(len_ip_event,0,"send_connnumber_tophone"))
	{
		return;
	}
	/////////////////////////////////////////////////////////////////////////////////////
	//private public cmd
	int length_private = 29 + 6 + nums_cid * 38;
	int len_toacct = len_ip_event;
	p_static_func->create_pricmd_public_29(buf,len_toacct,length_private,
										   "FFFFFFFFFFF","123456","FFFFFFFFFFF",2);
	//printf("length_private=%d\n",length_private);
	int len_tolevel = len_toacct + 9 + 9 - 1 + 4 + 2;
	buf[len_tolevel + 8] = 0x0F;
	buf[len_tolevel + 9] = 0x04;
	buf[len_tolevel + 10] = (conn_number >> 16) & 0xff;
	buf[len_tolevel + 11] = (conn_number >> 8) & 0xff;
	buf[len_tolevel + 12] = conn_number & 0xff;
	buf[len_tolevel + 13] = nums_cid & 0xff;
	memcpy(&buf[len_tolevel + 14],buf_cid,nums_cid * 38);
	//crc_private
	unsigned int crc_value_private = p_static_func->calcCRC_buf(&buf[len_toacct + 2],length_private);
	p_static_func->NumToHex_4(crc_value_private,buf_len);
	for(i = 0;i < 4;i++)
	{
		buf[len_tolevel + 14 + nums_cid * 38 + i] = buf_len[i];
	}
	send_cmd_to_server_0e_03(sock_recv,buf);
	
	
	
}
void Cstatic_var::Close(int fd)
{
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	///////////////////////////////////////////////
	if (close(fd) == -1)
	{
		perror("close error");
	}
	else
	{
		//printf("socket release success!\n");
	}
}



