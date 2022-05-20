//
//  person.hpp
//  test_map
//
//  Created by wangyuhong2267 on 17/2/26.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#ifndef person_hpp
#define person_hpp
#include "const.h"
class person
{
public:
	
	
	string name;
	int age;
	
	
	static person* p_inst;
	static person *get_instance();
	
	person (string name_temp,int age_temp);
	~person();
	void test_fun0();
	void test_fun();
	void test_fun2();
	void test_fun3();
	void test_fun4();
	void test_fun5();
	void insert_phone_map(string str_device_tocken,string str_phone_account,string str_machine_account,string badge_identification);
	void insert_phone_map_language(string str_device_tocken,string str_phone_account,string str_machine_account,string str_language);
	void insert_machine_map(string str_machine_account,string str_device_tocken,string str_phone_account);
	void insert_alarm_event_cid_map(string str_machine_account,string str_alarm_event_cid,string str_date_time_cid);
	void insert_event_cid_05_00_map(string str_machine_account,string str_alarm_event_cid);
	
	
	void delete_from_map_event_cid_05_00(string str_machine_account,string str_event_cid_05_00);
	void delete_from_map_machine(string str_machine_account,string str_device_tocken);
	void delete_from_map_phone(string str_device_tocken);
	void delete_from_map_phone_language(string str_device_tocken);
	void delete_list_element_from_map_machine(string str_machine_account,string str_device_tocken);
	
	string get_mahcine_account_from_map_phone(string str_device_tocken);
	string get_badge_identification_from_map_phone(string str_device_tocken);
	string get_language_from_map_phone(string str_device_tocken);
	
	void pop_pront_alarm_event_cid_map(string str_machine_account);
	void send_history_alarm_event_cid_map(string str_machine_account);
	void send_history_alarm_event_cid_map_0f_04(string str_machine_account,unsigned int conn_number,int sock_recv);
	
	
	void release_event_cid_05_00_map();
	void traversing_event_cid_05_00_map();
	void traversing_alarm_event_cid_map();
	void traversing_machine_map();
	void traversing_phone_map();
	void traversing_phone_map_language();
	/////////////////////////////////////////////////
	void csv_write_phone_map();
	void csv_write_phone_map_language();
	void csv_read_phone_map();
	void csv_read_phone_map_language();
	void csv_write_machine_map();
	void csv_read_machine_map();
	
	
	int query_status_from_machine_05_00_cid_map(string str_machine_account,string str_event_cid_05_00);
	int query_status_from_machine_map(string str_machine_account,string str_device_tocken,string str_phone_account);
	int query_status_from_phone_map(string str_device_tocken);
	int query_status_from_phone_map_language(string str_device_tocken);
	int get_event_type(string str_cid,string str_language);
	int query_status_from_machine_map_0e_02(string str_machine_account,string str_device_tocken,string str_phone_account);
	void cid_to_chinese_or_english_cid(string  str_cid,string &str_cid_chinese,string str_language);
	void cid_to_chinese_or_english_cid_yfn(string  str_cid,string &str_cid_chinese,string str_language);

};
#endif /* person_hpp */
