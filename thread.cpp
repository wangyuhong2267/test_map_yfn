//
//  thread.cpp
//  test_map
//
//  Created by wangyuhong2267 on 17/3/1.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#include "thread.hpp"

#include "tcp_socket.hpp"
//////////////////////////////////////////////////////////////////////
#include "static_var.hpp"
#include "huawei_client.h"

//////////////////////////////////////////////////////////////////////
Cthread* Cthread::p_inst = NULL;

Cthread::Cthread()
{
	
}

Cthread::~Cthread()
{
	
}


Cthread* Cthread::get_instance()
{
	if(p_inst == NULL)
	{
		p_inst = new Cthread();
	}
	return p_inst;
}

void Cthread::test_print()
{

	printf("Cthread......function_name:%s\n",__func__);
	
}

void Cthread::create_thread_jiaxing()
{
	
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	/////////////////////////////////////////////////
	printf("tttttttttttttttttttttttt \n");
	pthread_attr_init(&attr_jiaxing);
	pthread_attr_setdetachstate(&attr_jiaxing,PTHREAD_CREATE_DETACHED);
	if (pthread_create(&pthreadid_jiaxing, &attr_jiaxing, ThreadHandle_jiaxing,NULL) == 0)
	{
		printf("pthreadid_jiaxing %lu\n",pthreadid_jiaxing);
		
	}
	pthread_attr_destroy(&attr_jiaxing);
}

void* Cthread::ThreadHandle_jiaxing(void *args)
{
	
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	///////////////////////////////////////////////
	int len_recv = 0;
	
	signal(SIGPIPE, SIG_IGN);

	
	int len_standard = 0;
	int len_pri = 0;
	//int len_total = 0;
	
	int j = 0;


	unsigned char *pos;
	unsigned char buf[1460];
	pos = buf;
	char buf_small[10];
	char buf_id[3];
	int i_13 = 0;
	int a = 7;
	int b = 8;
	bool b_find_thread = true;
	
	while(1)
	{
		//printf("ThreadHandle_jiaxing,aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		//int len_requote = 0;
		for(j = 0;j < MAX_USER_NUMBER;j++)
		{
			int nfds=epoll_wait(Cstatic_var::ServerInfo[j].epfd_server,Cstatic_var::events_jiaxing,MAX_EVENTS,0);
			if(nfds > 0)
			{
				//printf("ThreadHandle_jiaxing,nfds=%d\n",nfds);
			}
			int i;
			for(i=0;i<nfds;++i)
			{
				if(Cstatic_var::events_jiaxing[i].data.fd == Cstatic_var::ServerInfo[j].sockfd_server)
				{
					
					
					if(Cstatic_var::events_jiaxing[i].events & EPOLLIN)
					{
						while(b_find_thread)
						{
							
							int i_t1 = i_13 %10;
							
							len_recv = recv(Cstatic_var::ServerInfo[j].sockfd_server,&buf_small[i_t1],1,MSG_WAITALL);
							if((len_recv == -1))
							{
								break;
							}
							if((len_recv == 0))
							{
								printf("ThreadHandle_jiaxing,socket release,Cstatic_var::ServerInfo[j].sockfd_server=%d\n", Cstatic_var::ServerInfo[j].sockfd_server);
								Cstatic_var::server_info_init2(j);
								break;
							}
							if(len_recv > 0)
							{
								i_13++;
								if(buf_small[i_t1] == '"')
								{
									len_recv = recv(Cstatic_var::ServerInfo[j].sockfd_server,buf_id,3,MSG_WAITALL);
									if((len_recv <= 0) || (len_recv == -1))
									{
										
										break;
									}
									if(len_recv == 3)
									{
										if(!((0 ==strcmp(buf_id,"ACK")) || (0 ==strcmp(buf_id,"HEN")) || (0 ==strcmp(buf_id,"NUL"))))
										{
											break;
										}
									}else
									{
										break;
									}
									////////////////////////////////////////////////////////////////////////
									//printf("j=%d\n", j);
									//int len_requote = 13;
									i_13 = 0;
									if(i_t1 == 9)
									{
										memcpy(buf,buf_small,10);
									}
									else// if(i_t1 < 12)
									{
										//printf("i_t1=%d\n",i_t1);
										memcpy(pos,buf_small + i_t1 + 1,(9 - i_t1));
										memcpy(pos + 9 - i_t1,buf_small,(i_t1 + 1));
									}
									len_standard = Cstatic_var::p_static_func->handle_len_standard(buf,a,b);
									if(buf[0] == 0x0a)
									{
										memcpy(pos + 10,buf_id,3);
										len_recv = recv(Cstatic_var::ServerInfo[j].sockfd_server,pos + 13,len_standard - 1,MSG_WAITALL);
										if((len_recv <= 0) || (len_recv == -1))
										{
											//printf("len_recv=%d\n",len_recv);
											break;
										}
										if(len_recv == (len_standard - 1))
										{
											len_pri = buf[len_standard + 10] * 256 + buf[len_standard + 10 + 1];
											//int len_total = len_standard + len_pri + 10 + 2 + 4;
											
											if(Cstatic_var::p_static_func->exception_handle_cmd_format("phone len_pri",3,len_pri,MAX_LEN_PRI))
											{
												break;
											}
											len_recv = recv(Cstatic_var::ServerInfo[j].sockfd_server,pos + len_standard + 10 + 2,len_pri + 4,MSG_WAITALL);
											if((len_recv <= 0) || (len_recv == -1))
											{
												break;
											}
											if(len_recv == (len_pri + 4))
											{
												//printf("ThreadHandle_jiaxing,len_total=%d\n",len_total);
												//Cstatic_var::p_static_func->printf_cmd_client_hex((unsigned char*)buf,len_total);
												pos = buf;
												if(!Cstatic_var::p_static_func->crc_check_std((unsigned char*)buf,0))
												{
													break;
												}
												if(!Cstatic_var::p_static_func->crc_check_pri((unsigned char*)buf,0))
												{
													break;
													
												}
												//unsigned int len_temp = len_standard + PUBLIC_SIZE + 10;
												
												if(Cstatic_var::p_static_func->exception_handle_cmd_format_detail(buf,1)){
													
													break;
												}
												
												
												//Cstatic_var::p_static_func->printf_cmd_client((unsigned char*)buf,len_total);
												command_handle_apns((unsigned char *)buf,Cstatic_var::ServerInfo[j].sockfd_server);
												break;
												
											}
										}
									}
								}
							}
							
							
						}
					}
				}
			}
		}
		
		
	}
}

void Cthread::create_thread_ninghai()
{
	
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	/////////////////////////////////////////////////
	printf("tttttttttttttttttttttttt \n");
	pthread_attr_init(&attr_ninghai);
	pthread_attr_setdetachstate(&attr_jiaxing,PTHREAD_CREATE_DETACHED);
	if (pthread_create(&pthreadid_ninghai, &attr_ninghai, ThreadHandle_ninghai,NULL) == 0)
	{
		printf("pthreadid_ninghai %lu\n",pthreadid_ninghai);
		
	}
	pthread_attr_destroy(&attr_jiaxing);
}

void* Cthread::ThreadHandle_ninghai(void *args)
{
	
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	///////////////////////////////////////////////
	

	signal(SIGPIPE, SIG_IGN);

	
	
	Ctcp_socket *p_tcp_sock = Ctcp_socket::get_instance();
	while(1)
	{
		//printf("ThreadHandle_ninghai,aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
		
		int i;
		for(i=0;i<MAX_USER_NUMBER_APNS;i++)
		{
			
			if (i < 2) {
				//printf("ThreadHandle_ninghai,Cstatic_var::ServerInfo[%d].bUsed=%d\n",i,Cstatic_var::ServerInfo[i].bUsed);
			}
			if ((Cstatic_var::ServerInfo[i].bHave_server) && (!Cstatic_var::ServerInfo[i].bUsed)) {
				Cstatic_var::server_info_init2(i);
				//int ret_conn = p_tcp_sock->tcp_connect_timeout (&(Cstatic_var::ServerInfo[i].sockfd_server), 6 ,Cstatic_var::ServerInfo[i].str_ip_address,7890);
				int ret_conn = p_tcp_sock->tcp_connect_timeout (&(Cstatic_var::ServerInfo[i].sockfd_server), 3 ,Cstatic_var::ServerInfo[i].str_ip_address,7894);
				//int ret_conn = p_tcp_sock->tcp_connect_timeout (&(Cstatic_var::ServerInfo[i].sockfd_server), 10 ,Cstatic_var::ServerInfo[i].str_ip_address,9800);
				printf("ThreadHandle_ninghai,i=%d,ret_conn=%d\n",i,ret_conn);
				printf("ThreadHandle_ninghai,Cstatic_var::ServerInfo[%d].str_ip_address=%s\n",i,Cstatic_var::ServerInfo[i].str_ip_address);
				
				if (ret_conn > 0) {
					Cstatic_var::ServerInfo[i].bUsed = true;
					
					Cstatic_var::ServerInfo[i].epfd_server = Cstatic_var::p_static_func->EpollConfig(Cstatic_var::ServerInfo[i].sockfd_server,false);;
					Cstatic_var::server_info_init_time(i);
					
				}else{
					
				}
				//sleep(1);
				/////////////////////////////////////////////
				if (!Cstatic_var::ServerInfo[i].bHave_server) {
					//break;
				}
			}
		}
		usleep(10000000);
		
	}
}

void Cthread::command_handle_apns(unsigned char *cmd,int sock_recv)
{
	char buf_id[256];
	memset(buf_id,0,sizeof(buf_id));
	memcpy(buf_id,&cmd[9],9);
	//printf("buf_id=%s\n",buf_id);
	/////////////////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////////////////////////////////
	unsigned int len_standard = len_std_a * 16 + len_std_b;
	//printf("len_standard=%d,len_std_a=%d,len_std_b=%d",len_standard,len_std_a,len_std_b);
	if((len_standard > MAX_LEN_STD) || (len_standard <= 0))
	{
		printf("ip event report protocol,len is except len_standard=%d",len_standard);
		return;
	}
	
	unsigned int len_pri = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
	if((len_pri > MAX_LEN_PRI) || (len_pri <= 0))
	{
		printf("private cmd,len is except len_pri=%d",len_pri);
		return;
	}
	unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;
	if((len_total > (MAX_LEN_STD + MAX_LEN_PRI)) || (len_total <= 0))
	{
		printf("private cmd plus ip event report ,len is except len_total=%d",len_total);
		return;
	}
	
	//printf("len_standard=%d,len_pri=%d,len_total=%d\n",len_standard,len_pri,len_total);
	unsigned int len_temp = len_standard + PUBLIC_SIZE + 10;
	if(len_temp > 1460)
	{
		printf("private cmd plus ip event report ,len is except len_temp=%d",len_temp);
		return;
	}
	if((len_temp > (MAX_LEN_STD + MAX_LEN_PRI - 6)) || (len_temp <= 0))
	{
		printf("private cmd plus ip event report ,len is except len_temp=%d",len_temp);
		return;
	}
	
	//printf("len_standard=%d,len_pri=%d,len_total=%d\n",len_standard,len_pri,len_total);
	//////////////////////////////////////////////////////////////////////////////////
	unsigned int big_class = cmd[len_temp];
	unsigned int small_class = cmd[len_temp + 1];
	unsigned int conn_number = cmd[len_temp + 2] * 65536 + cmd[len_temp + 3] * 256 + cmd[len_temp + 4];
	if(!((big_class == 0x05)
	|| ((big_class == 0x0e) && (small_class == 0x03))
	|| ((big_class == 0x00) && (small_class == 0x02))
         || ((big_class == 0x00) && (small_class == 0x04))
	|| ((big_class == 0x00) && (small_class == 0x03)))
	)
	{
		if(conn_number >= MAX_USER_NUMBER_APNS)
		{
			printf("big_class=%02x, small_class=%02x\n",big_class, small_class);
			printf("apns conn_number=%d is out of max conn_number\n",conn_number);
			return;
		}
	}
	

	//printf("command_handle_apns,big_class=%02x, small_class=%02x,conn_number=%d\n",big_class, small_class,conn_number);
	
	
	
	switch(big_class)
	{
		case 0x00:
		{
			if (small_class == 0x02) {//clear badges
				try{
					char buf_device_token[65];
					memset(buf_device_token, 0,sizeof(buf_device_token));
					memcpy(buf_device_token,&cmd[len_temp + 5],64);
					printf("command_handle_apns,00 02,apns_device_token=%s\n",buf_device_token);
					
					/////////////////////////////////////////////////
					char account_number_phone[18];
					memset(account_number_phone,0,sizeof(account_number_phone));
					char *account_number_phone2;
					account_number_phone2 = Cstatic_var::p_static_func->HexByteToNumString((char *)&cmd[len_standard + 25],9);
					memcpy(account_number_phone,account_number_phone2,18);
					
					///////////////////////////////////////////////////////////////////
					char account_number_machine2[18];
					memset(account_number_machine2,0,sizeof(account_number_machine2));
					char *account_number_machine_temp;
					account_number_machine_temp = Cstatic_var::p_static_func->HexByteToNumString((char *)&cmd[len_standard + 12],9);
					memcpy(account_number_machine2,account_number_machine_temp,18);
					printf("command_handle_apns,00 02,account_number_phone=%s\n",account_number_phone);
					printf("command_handle_apns,00 02,account_number_machine2=%s\n",account_number_machine2);
					/////////////////////////////////////////////////////////////////////
					string str_phone = account_number_phone;
					string str_machine = account_number_machine2;
					string str_device_tocken = buf_device_token;
					if (1) {
						lock_guard<mutex> guard(std::mutex mutex_map_phone);
						Cstatic_var::p_static_person->delete_from_map_phone(str_device_tocken);
						Cstatic_var::p_static_person->insert_phone_map(str_device_tocken,str_phone,str_machine,"0");
						unsigned int conn_number = cmd[len_temp + 2] * 65536 + cmd[len_temp + 3] * 256 + cmd[len_temp + 4];
						printf("command_handle_apns,00 02,conn_number=%d\n",conn_number);
						Cstatic_var::send_clear_badges_to_app_0f_03(conn_number,sock_recv,1);
						
						Cstatic_var::p_static_person->send_history_alarm_event_cid_map_0f_04(str_machine,conn_number,sock_recv);
					}
					
				}
				catch(...){
					printf("command_handle_apns,00 02,catch error...\n");
				}
				
			}
			if (small_class == 0x03) {//android deviceToken
				try{
//                    Cstatic_var::p_static_func->printf_cmd_client((unsigned char*)cmd,len_total);
					char buf_device_token[131];
					memset(buf_device_token, 0,sizeof(buf_device_token));
					memcpy(buf_device_token,&cmd[len_temp + 5],130);
//					printf("command_handle_apns,00 03,apns_device_token=%s\n",buf_device_token);
                    int ret2 = send(Chuawei_client::huaweiServerInfo[0].huawei_sockfd_server,(char *)cmd,len_total,0);
//                    printf("command_handle_apns,00 03,ret2=%d\n",ret2);


				}
				catch(...){
					printf("command_handle_apns,00 02,catch error...\n");
				}

			}if (small_class == 0x04) {//android deviceToken
				try{
                    Cstatic_var::p_static_func->printf_cmd_client((unsigned char*)cmd,len_total);
					char buf_device_token[163];
					memset(buf_device_token, 0,sizeof(buf_device_token));
					memcpy(buf_device_token,&cmd[len_temp + 5],163);
					printf("command_handle_apns,00 04,apns_device_token=%s\n",buf_device_token);
                    int ret2 = send(Chuawei_client::huaweiServerInfo[0].huawei_sockfd_server,(char *)cmd,len_total,0);
                    printf("command_handle_apns,00 04,ret2=%d\n",ret2);


				}
				catch(...){
					printf("command_handle_apns,00 02,catch error...\n");
				}

			}
		}
			
		break;
		case 0x0e://phone send to netserver
		{
			
			if(small_class == 0x00)//apple app online and china or english
			{
				Cstatic_var::p_static_func->printf_cmd_client((unsigned char*)cmd,len_total);
				try{
					char chstr_phone[19];
					memset(chstr_phone,0,sizeof(chstr_phone));
					char chstr_machine[19];
					memset(chstr_machine,0,sizeof(chstr_machine));
					char chstr_device_tocken[65];
					memset(chstr_device_tocken,0,sizeof(chstr_device_tocken));
					
					memcpy(chstr_phone,&cmd[len_standard + 13 + 33],18);
					memcpy(chstr_machine,&cmd[len_standard + 13 + 33 + 18],18);
					memcpy(chstr_device_tocken,&cmd[len_standard + 13 + 33 + 18 + 18],64);
					//				printf("command_handle_apns,0e 00,chstr_phone=%s\n",chstr_phone);
					//				printf("command_handle_apns,0e 00,chstr_machine=%s\n",chstr_machine);
					unsigned int app_language_temp = cmd[len_temp - 2];
					printf("command_handle_apns,0e 00,app_language_temp=%d\n",app_language_temp);
					string str_language = "";
					if (app_language_temp == 1) {
						str_language = "English";
					}else{
						str_language = "China";
					}
					printf("command_handle_apns,0e 00,chstr_device_tocken=%s\n",chstr_device_tocken);
					
					string str_phone = chstr_phone;
					string str_machine = chstr_machine;
					string str_device_tocken = chstr_device_tocken;
					int status_machine = Cstatic_var::p_static_person->query_status_from_machine_map(str_machine,str_device_tocken,str_phone);
					//printf("command_handle_apns,0e 00,status_machine=%d\n",status_machine);
					if (status_machine == -1) {
						return;
					}
					
					if(status_machine == 1){//have machine and have devicetocken
						lock_guard<mutex> guard(std::mutex mutex_map_machine);
						Cstatic_var::p_static_person->delete_list_element_from_map_machine(str_machine,str_device_tocken);
						Cstatic_var::p_static_person->insert_machine_map(str_machine,str_device_tocken,str_phone);
						//Cstatic_var::p_static_person->traversing_machine_map();
						Cstatic_var::p_static_person->csv_write_machine_map();
					}else if(status_machine == 2){////have machine and no devicetocken
						lock_guard<mutex> guard(std::mutex mutex_map_machine);
						//Cstatic_var::p_static_person->delete_list_element_from_map_machine(str_machine,str_device_tocken,str_language_no_used);
						Cstatic_var::p_static_person->insert_machine_map(str_machine,str_device_tocken,str_phone);
						//Cstatic_var::p_static_person->traversing_machine_map();
						Cstatic_var::p_static_person->csv_write_machine_map();
					}else if(status_machine == 3){//no this device_tocken
						lock_guard<mutex> guard(std::mutex mutex_map_machine);
						//Cstatic_var::p_static_person->delete_list_element_from_map_machine(str_machine,str_device_tocken,str_language_no_used);
						Cstatic_var::p_static_person->insert_machine_map(str_machine,str_device_tocken,str_phone);
						//Cstatic_var::p_static_person->traversing_machine_map();
						Cstatic_var::p_static_person->csv_write_machine_map();
					}
					int status_phone = Cstatic_var::p_static_person->query_status_from_phone_map(str_device_tocken);
					printf("command_handle_apns,0e 00,status_phone=%d\n",status_phone);
					
					if (status_phone != 0) {
						lock_guard<mutex> guard(std::mutex mutex_map_phone);
						Cstatic_var::p_static_person->insert_phone_map(str_device_tocken,str_phone,str_machine,"0");
						//Cstatic_var::p_static_person->traversing_phone_map();
						Cstatic_var::p_static_person->csv_write_phone_map();
					}
					//////////////////////////////////////////////////////////
					int status_phone_language = Cstatic_var::p_static_person->query_status_from_phone_map_language(str_device_tocken);
					printf("command_handle_apns,0e 00,status_phone_language=%d\n",status_phone_language);
					
					if (status_phone_language == -1) {
						lock_guard<mutex> guard(std::mutex mutex_map_language);
						
						Cstatic_var::p_static_person->insert_phone_map_language(str_device_tocken,str_phone,str_machine,str_language);
						//Cstatic_var::p_static_person->traversing_phone_map_language();
						Cstatic_var::p_static_person->csv_write_phone_map_language();
					}else if (status_phone_language == 0) {
						lock_guard<mutex> guard(std::mutex mutex_map_language);
						Cstatic_var::p_static_person->delete_from_map_phone_language(str_device_tocken);
						Cstatic_var::p_static_person->insert_phone_map_language(str_device_tocken,str_phone,str_machine,str_language);
						//Cstatic_var::p_static_person->traversing_phone_map_language();
						Cstatic_var::p_static_person->csv_write_phone_map_language();
					}
					//////////////////////////////////////////////////////////////////////
					//Cstatic_var::p_static_person->send_history_alarm_event_cid_map(str_machine);
					
					
				}
				catch(...){
					printf("command_handle_apns,0e 00,catch error...\n");
				}
				
				
			}else if (small_class == 0x01){//heartbeat
				
				if(conn_number >= MAX_USER_NUMBER_APNS)
				{
					//printf("big_class=%02x, small_class=%02x\n",big_class, small_class);
					//printf("apns conn_number=%d is out of max conn_number\n",conn_number);
					return;
				}
				
				//printf("conn_number=%d\n",conn_number);
				Cstatic_var::server_info_init_time(conn_number);
			}else if (small_class == 0xff){//temp
//				try{
//					printf("command_handle_apns,details,big_class=%02x, small_class=%02x,conn_number=%d\n",big_class, small_class,conn_number);
//					Cstatic_var::p_static_person->csv_write_phone_map();
//					Cstatic_var::p_static_person->csv_write_machine_map();
//				}
//				catch(...){
//					printf("command_handle_apns,0e ff,catch error...\n");
//				}
				
			}else if (small_class == 0x03){//delete app info
				//printf("big_class=%02x, small_class=%02x\n",big_class, small_class);
				Cstatic_var::p_static_func->printf_cmd_client((unsigned char*)cmd,len_total);
				try{
					char buf_device_token[65];
					memset(buf_device_token, 0,sizeof(buf_device_token));
					memcpy(buf_device_token,&cmd[len_temp + 5],64);
					printf("command_handle_apns,00 03,apns_device_token=%s\n",buf_device_token);
					
					/////////////////////////////////////////////////
					char account_number_phone[18];
					memset(account_number_phone,0,sizeof(account_number_phone));
					char *account_number_phone2;
					account_number_phone2 = Cstatic_var::p_static_func->HexByteToNumString((char *)&cmd[len_standard + 25],9);
					memcpy(account_number_phone,account_number_phone2,18);
					
					///////////////////////////////////////////////////////////////////
					char account_number_machine2[18];
					memset(account_number_machine2,0,sizeof(account_number_machine2));
					char *account_number_machine_temp;
					account_number_machine_temp = Cstatic_var::p_static_func->HexByteToNumString((char *)&cmd[len_standard + 12],9);
					memcpy(account_number_machine2,account_number_machine_temp,18);
					printf("command_handle_apns,00 03,account_number_phone=%s\n",account_number_phone);
					printf("command_handle_apns,00 03,account_number_machine2=%s\n",account_number_machine2);
					/////////////////////////////////////////////////////////////////////
					string str_phone = account_number_phone;
					string str_machine = account_number_machine2;
					string str_device_tocken = buf_device_token;
					
					
					int status_machine = Cstatic_var::p_static_person->query_status_from_machine_map(str_machine,str_device_tocken,str_phone);
					//printf("command_handle_apns,0e 00,status_machine=%d\n",status_machine);
					if (status_machine == -1) {
						return;
					}
					
					if(status_machine == 1){//have machine and have devicetocken
						lock_guard<mutex> guard(std::mutex mutex_map_machine);
						Cstatic_var::p_static_person->delete_list_element_from_map_machine(str_machine,str_device_tocken);
						Cstatic_var::p_static_person->csv_write_machine_map();
						Cstatic_var::send_delete_success_to_app_0f_02(conn_number,sock_recv,1);
					}else{
						Cstatic_var::send_delete_success_to_app_0f_02(conn_number,sock_recv,0);
					}
				}
				catch(...){
					printf("command_handle_apns,0e 03,catch error...\n");
				}
				
				
			}

		}
		break;
		case 0x05:
		{
			try{
				if (small_class == 0x00) {//handle alarm event
//                    Chuawei_client::send_cmd_to_server_huawei(0,cmd);
					int place_bracket_left = Cstatic_var::p_static_func->find_place((char*)&cmd[0],'[',len_standard);
					//printf("05 00,place_bracket_left=%d\n",place_bracket_left);
					int place_bracket_right = Cstatic_var::p_static_func->find_place((char*)&cmd[0],']',len_standard);
					//printf("05 00,place_bracket_right=%d\n",place_bracket_right);
					if(place_bracket_right <= place_bracket_left)
					{
						return;
					}
					char account_number_machine[18];
					memset(account_number_machine,0,sizeof(account_number_machine));
					char * account_number_machine_05_00 = Cstatic_var::p_static_func->HexByteToNumString((char *)&cmd[len_standard + 12],9);
					memcpy(account_number_machine,account_number_machine_05_00,sizeof(account_number_machine));
					///////////////////////////////////////////////////////////////
					char array_date_time[32];
					memset(array_date_time,0,sizeof(array_date_time));
					memcpy(array_date_time,(char*)&cmd[place_bracket_right + 1],20);
					//printf("command_handle_apns,05 00 ,array_date_time=%s,account_number_machine=%s\n",array_date_time,account_number_machine);
					string str_date_time = array_date_time;
					string str_year = str_date_time.substr(16,4);
					string str_month = str_date_time.substr(10,2);
					string str_day = str_date_time.substr(13,2);
					//printf("command_handle_apns,05 00 ,str_year=%s,account_number_machine=%s\n",str_year.c_str(),account_number_machine);
					//printf("command_handle_apns,05 00 ,str_month=%s,account_number_machine=%s\n",str_month.c_str(),account_number_machine);
					//printf("command_handle_apns,05 00 ,str_day=%s,account_number_machine=%s\n",str_day.c_str(),account_number_machine);
					string str_time = str_date_time.substr(1,8);
					//printf("command_handle_apns,05 00 ,str_time=%s,account_number_machine=%s\n",str_time.c_str(),account_number_machine);
					string str_date_time_real = str_year + "-" + str_month + "-" + str_day + " " + str_time;
					//printf("command_handle_apns,05 00 ,str_date_time_real=%s,account_number_machine=%s\n",str_date_time_real.c_str(),account_number_machine);
					////////////////////////////////////////////////////////////////
					char array_cid[256];
					memset(array_cid,0,sizeof(array_cid));
					memcpy(array_cid,(char*)&cmd[place_bracket_left + 1],
						   (place_bracket_right - place_bracket_left - 1));
					if((0 == strcmp(account_number_machine,"863977035369995"))
					   || (0 == strcmp(account_number_machine,"863977035485684"))
					   || (0 == strcmp(account_number_machine,"865740032019478")))
					{
						printf("command_handle_apns,05 00 ,array_cid=%s,account_number_machine=%s,sock_recv=%d\n",array_cid,account_number_machine,sock_recv);
					}
					
					char str_temp[18];
					memset(str_temp,0,sizeof(str_temp));
					if(0 == strncmp(account_number_machine,str_temp,18))
					{
						printf("command_handle_apns,account_number_machine is error，05 00 ,return,,array_cid=%s,account_number_machine=%s\n",array_cid,account_number_machine);
						return;
					}else {
                        string str_machine_account = account_number_machine;
                        string str_alarm_event_cid = array_cid;

                        int status_machine_05_00_cid = -1;
                        status_machine_05_00_cid = Cstatic_var::p_static_person->query_status_from_machine_05_00_cid_map(
                                account_number_machine, str_alarm_event_cid);


                        if (status_machine_05_00_cid == 3) {
                            Chuawei_client::send_cmd_to_server_huawei(0, cmd);
                            Cstatic_var::p_static_person->insert_event_cid_05_00_map(account_number_machine,


                                                                                     str_alarm_event_cid);

                            int num = str_alarm_event_cid.find("756");
                            if (num > 0) {
//                            printf("found 756,command_handle_apns,array_cid=%s,account_number_machine=%s\n",array_cid,account_number_machine);
                                return;
                            }

                            Cstatic_var::p_static_person->insert_alarm_event_cid_map(str_machine_account,
                                                                                     str_alarm_event_cid,
                                                                                     str_date_time_real);
                            Cstatic_var::p_static_person->pop_pront_alarm_event_cid_map(str_machine_account);

                            //////////////////////////////////////////////////////////
                            int status_machine_push = Cstatic_var::query_machine_push_status(account_number_machine);
                            if (status_machine_push == 1) {
                                Cstatic_var::apns_push_message(account_number_machine, array_cid);
                            }
                        } else if (status_machine_05_00_cid == 1) {

                            Cstatic_var::p_static_person->delete_from_map_event_cid_05_00(account_number_machine,
                                                                                          str_alarm_event_cid);
                            if ((0 == strcmp(account_number_machine, "865740032019478"))) {
                                Cstatic_var::p_static_person->traversing_event_cid_05_00_map();
                            }
                        }
					}
				}
			}
			catch(...){
				printf("command_handle_apns,05 00,catch error...\n");
			}
			
				
			
		}
		
			break;
			
		default:
			break;
	}
	
	
	
}
void Cthread::create_thread_cid_05_00()
{
	
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	/////////////////////////////////////////////////
	printf("tttttttttttttttttttttttt \n");
	pthread_attr_init(&attr_cid_05_00);
	pthread_attr_setdetachstate(&attr_cid_05_00,PTHREAD_CREATE_DETACHED);
	if (pthread_create(&pthreadid_cid_05_00, &attr_cid_05_00, ThreadHandle_cid_05_00,NULL) == 0)
	{
		printf("pthreadid_cid_05_00 %lu\n",pthreadid_cid_05_00);
		
	}
	pthread_attr_destroy(&attr_cid_05_00);
	
}
void* Cthread::ThreadHandle_cid_05_00(void* args)
{
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	///////////////////////////////////////////////
	//Ctcp_socket *p_tcp_sock = Ctcp_socket::get_instance();
	
	
	signal(SIGPIPE, SIG_IGN);
	while(1)
	{
		//printf("ThreadHandle_cid_05_00............................ \n");
		Cstatic_var::p_static_person->release_event_cid_05_00_map();
		usleep(1000000);
		
		
	}
	printf("ThreadHandle_time exit!\n");
	
}

void Cthread::create_thread_time()
{
	
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	/////////////////////////////////////////////////
	printf("tttttttttttttttttttttttt \n");
	pthread_attr_init(&attr_time);
	pthread_attr_setdetachstate(&attr_time,PTHREAD_CREATE_DETACHED);
	if (pthread_create(&pthreadid_time, &attr_time, ThreadHandle_time,NULL) == 0)
	{
		printf("pthreadid_time %lu\n",pthreadid_time);
		
	}
	pthread_attr_destroy(&attr_time);
	
}

void* Cthread::ThreadHandle_time(void* args)
{
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	///////////////////////////////////////////////
	//Ctcp_socket *p_tcp_sock = Ctcp_socket::get_instance();
	

	signal(SIGPIPE, SIG_IGN);
	while(1)
	{
//		printf("ThreadHandle_time............................ \n");
		
		/////////////////////////////////////////////////////////////
		
		if (Cstatic_var::time_calculate_three_second2 == HEARTBEAT_INTERVAL_APNS_ONE_TIME) {
			for (int i = 0; i < MAX_USER_NUMBER; i++) {
				if(Cstatic_var::ServerInfo[i].bUsed){
				    printf("Cstatic_var::ServerInfo[i].bUsed,i=%d\n",i);
					Cstatic_var::send_heart_beat_to_server(i);
					
				}
			}
			Cstatic_var::time_calculate_three_second2 = 0;
		}
		//printf("ThreadHandle_time,Cstatic_var::time_calculate_three_second_transfer=%d\n",Cstatic_var::time_calculate_three_second_transfer);
		Cstatic_var::time_calculate_three_second2++;
		////////////////////////////////////////////////////////////////////////////
		//Cstatic_var::handle_feedback();
		
		Cstatic_var::nghttp2_reconnect();
		usleep(1000000);
		
		//////////////////////////////////////////////////////////////////////////////
	}
	printf("ThreadHandle_time exit!\n");
	
}


