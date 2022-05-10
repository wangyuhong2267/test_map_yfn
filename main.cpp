//
//  m_mapain.cpp
//  test_map
//
//  Created by wangyuhong2267 on 17/2/24.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//



#include "const.h"
#include "person.h"
#include "static_var.hpp"
#include "tcp_socket.hpp"
#include "thread.hpp"
#include "csv.hpp"
#include "huawei_client.h"

//////////////////////////////////////////////////////////////////////





int main(int argc, const char * argv[]) {




//	csv *p_csv = csv::get_instance();
//	p_csv->write("aaa");
//	p_csv->write("bbb");
//	p_csv->write("ccc");
//	p_csv->outfile.close();
//	Cstatic_var::p_csv->createfile_phone("map_phone.csv");
//	Cstatic_var::p_csv->createfile_machine("map_machine.csv");
//	return 0;
	
	char buf_temp[255];
	memset(buf_temp,0,sizeof(buf_temp));
	Cstatic_var::p_static_func->get_time_log(buf_temp);
	
	Clog::flog=fopen(buf_temp,"wb+");
	
	///////////////////////////////////////////////////////
	
		/*Cstatic_var::test_ssl_client.init_openssl();
		Cstatic_var::test_ssl_client.init_tcp_connect("feedback.sandbox.push.apple.com",2196);
		Cstatic_var::test_ssl_client.init_ssl_context("PushChatCert.pem","PushChatKey.pem","hb2353","ck.pem");
		Cstatic_var::test_ssl_client.ssl_connect();
		Cstatic_var::test_ssl_client.verify_connection(NULL);*/
	/////////////////////////////////////////////////////
	
	if(1){
		person *pPerson = new person("ddd",33);
		unique_ptr<person> pAuto1(pPerson);
		cout<<pPerson<<endl;
		cout<<pAuto1.get()<<endl;
		pAuto1->test_fun0();
		pAuto1.reset();
		cout<<"ending......"<<endl;
		
	}

	//Cstatic_var::p_static_person->traversing_phone_map();
	Cstatic_var::p_static_person->csv_read_phone_map();
	//Cstatic_var::p_static_person->traversing_phone_map();
	
	/////////////////////////////////////////////////////////////////////////////
	//Cstatic_var::p_static_person->traversing_machine_map();
	Cstatic_var::p_static_person->csv_read_machine_map();
	//Cstatic_var::p_static_person->traversing_machine_map();
	
	/////////////////////////////////////////////////////////////////////////////
	//Cstatic_var::p_static_person->traversing_phone_map_language();
	Cstatic_var::p_static_person->csv_read_phone_map_language();
	//Cstatic_var::p_static_person->traversing_phone_map_language();
	
	
	


	/////////////////////////////////////////////
	int i;
	for(i=0;i<MAX_USER_NUMBER;i++)
	{
		Cstatic_var::server_info_init(i);
        Chuawei_client::huawei_server_info_init(i);
	}




    Cthread *p_thread = Cthread::get_instance();
	
	


    Chuawei_client::huaweiServerInfo[0].huawei_bHave_server = true;
//	char * str_ip_temp2 = (char*)"192.168.2.203";
//	char * str_ip_temp2 = (char*)"192.168.2.108";
//	char * str_ip_temp2 = (char*)"192.168.2.213";
//	char * str_ip_temp2 = (char*)"111.231.83.129";
	char * str_ip_temp2 = (char*)"170.106.153.215";
	memcpy(Chuawei_client::huaweiServerInfo[0].huawei_str_ip_address,str_ip_temp2,strlen(str_ip_temp2));



    Chuawei_client *p_thread_huawei = Chuawei_client::get_instance();
    p_thread_huawei->create_thread_huawei_handle();
    p_thread_huawei->create_thread_huawei_conn();


    /////////////////////////////////////////////




//	p_thread->test_print();

    Cstatic_var::ServerInfo[0].bHave_server = true;
    char * str_ip_temp1 = (char*)"122.152.205.226";
    memcpy(Cstatic_var::ServerInfo[0].str_ip_address,str_ip_temp1,strlen(str_ip_temp1));

    Cstatic_var::ServerInfo[1].bHave_server = true;
    char * str_ip_temp = (char*)"47.100.103.247";
    memcpy(Cstatic_var::ServerInfo[1].str_ip_address,str_ip_temp,strlen(str_ip_temp));

    Cstatic_var::ServerInfo[2].bHave_server = true;
    char * str_ip_temp22 = (char*)"162.62.61.164";
    memcpy(Cstatic_var::ServerInfo[2].str_ip_address,str_ip_temp22,strlen(str_ip_temp22));

    Cstatic_var::ServerInfo[3].bHave_server = true;
    char * str_ip_temp222 = (char*)"49.51.35.75";
    memcpy(Cstatic_var::ServerInfo[3].str_ip_address,str_ip_temp222,strlen(str_ip_temp222));

	p_thread->create_thread_jiaxing();
	p_thread->create_thread_ninghai();
	p_thread->create_thread_cid_05_00();


	p_thread->create_thread_time();
	
	Ctcp_socket *p_tcp_sock = Ctcp_socket::get_instance();
	p_tcp_sock->test_print();

    Cstatic_var::apns_connect();
	
	
	//Cstatic_var::p_static_func->test_print();



	while (1) {
		sleep(3);
		//cout<<"while......"<<endl;
		
		
		

	}
    return 0;
}
