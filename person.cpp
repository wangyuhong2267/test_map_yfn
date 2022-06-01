//
//  person.cpp
//  test_map
//
//  Created by wangyuhong2267 on 17/2/26.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#include "person.h"
#include "static_var.hpp"
person::person (string name_temp = "wangyuholng",int age_temp = 44)
{
	name = name_temp;
	age = age_temp;
	cout<<"person..."<<endl;
	cout<<"person...name="<<name<<endl;
	cout<<"person...age="<<age<<endl;
}
person::~person(){
	name = "www";
	age = 22;
	cout<<"~person..."<<endl;
}

person* person::p_inst = NULL;




person * person::get_instance()
{
	if(p_inst == NULL)
	{
		p_inst = new person();
	}
	return p_inst;
}


void person::test_fun0(){
	
//	list<string> *l = new list<string>;
//	shared_ptr<list<string>> plist(l);
//	plist->push_back("151");
//	plist->push_back("152");
//	plist->push_back("153");
//	int count_l = l->size();
//	cout<<"count_l="<<count_l<<endl;
//	
//	for (list<string>::iterator it = plist->begin(); it!=plist->end(); it++) {
//		cout<<*it<<"\n";
//	}
//	//plist.reset();
//	///////////////////////////////////////////////////
//	list<string> *l2 = new list<string>;
//	shared_ptr<list<string>> plist2(l2);
//	plist2->push_back("161");
//	plist2->push_back("162");
//	plist2->push_back("163");
//	for (list<string>::iterator it2 = plist2->begin(); it2!=plist2->end(); it2++) {
//		cout<<*it2<<"\n";
//	}
//	//	///////////////////////////////////////////////////
//	list<string> *l3 = new list<string>;
//	shared_ptr<list<string>> plist3(l3);
//	plist3->push_back("171");
//	plist3->push_back("172");
//	plist3->push_back("173");
//	for (list<string>::iterator it2 = plist3->begin(); it2!=plist3->end(); it2++) {
//		cout<<*it2<<"\n";
//	}
//	
//	
//	
//	map<string,shared_ptr<list<string>>> m;
//	m.insert(make_pair("15934928373", plist));
//	m.insert(make_pair("15934928174", plist2));
//	m.insert(make_pair("15934928275", plist3));
//	
//	
//	
//	
//	int m_count = m.size();
//	cout<<"m_count="<<m_count<<endl;
//	map<string,shared_ptr<list<string>>>::iterator it_temp=m.begin();
//	
//	for (; it_temp!=m.end(); ++it_temp)
//	{
//		cout<<it_temp->first<<endl;
//		
//		
//		shared_ptr<list<string>> plist_temp = it_temp->second;
//		for (list<string>::iterator it2 = plist_temp->begin(); it2!=plist_temp->end(); it2++) {
//			cout<<*it2<<"\n";
//		}
//		
//		
//	}
	
	
	
	
}
void person::test_fun5(){
	
	string str_machine_account = "863977035369995";
	string str_alarm_event_cid = "wangyuhong";
	Cstatic_var::p_static_person->insert_alarm_event_cid_map(str_machine_account,str_alarm_event_cid,"2017-08-03 00:01:02");
	 //////////////////////////////////////////////////////////////
	string str_machine_account2 = "863977035369997";
	string str_alarm_event_cid2 = "wangyuhong2";
	Cstatic_var::p_static_person->insert_alarm_event_cid_map(str_machine_account2,str_alarm_event_cid2,"2017-08-03 00:01:02");
	//////////////////////////////////////////////////////////////

	string str_machine_account3 = "863977035369998";
	string str_alarm_event_cid3 = "wangyuhong3";
	Cstatic_var::p_static_person->insert_alarm_event_cid_map(str_machine_account3,str_alarm_event_cid3,"2017-08-03 00:01:02");
	//////////////////////////////////////////////////////////////

	Cstatic_var::p_static_person->traversing_alarm_event_cid_map();
	
}
void person::test_fun(){
	list<string> *l = new list<string>;
	shared_ptr<list<string>> plist(l);
	plist->push_back("151");
	plist->push_back("152");
	plist->push_back("153");
	int count_l = l->size();
	cout<<"count_l="<<count_l<<endl;
	
	for (list<string>::iterator it = plist->begin(); it!=plist->end(); it++) {
		cout<<*it<<"\n";
	}
	//plist.reset();
	///////////////////////////////////////////////////
	list<string> *l2 = new list<string>;
	shared_ptr<list<string>> plist2(l2);
	plist2->push_back("161");
	plist2->push_back("162");
	plist2->push_back("163");
	for (list<string>::iterator it2 = plist2->begin(); it2!=plist2->end(); it2++) {
		cout<<*it2<<"\n";
	}
	//	///////////////////////////////////////////////////
	list<string> *l3 = new list<string>;
	shared_ptr<list<string>> plist3(l3);
	plist3->push_back("171");
	plist3->push_back("172");
	plist3->push_back("173");
	for (list<string>::iterator it2 = plist3->begin(); it2!=plist3->end(); it2++) {
		cout<<*it2<<"\n";
	}
	
	
	
	
	
	
	cout<<"end......"<<endl;
}
void person::test_fun2(){
	
	traversing_machine_map();


	
	traversing_machine_map();
	
	

	////////////////////////////////////////////////////////////////
	if (Cstatic_var::map_machine.empty()) {
		printf("test_fun2,m_count_machine_map=%d\n",0);
		return;
	}
	string s = "15934928374";

	map<string,shared_ptr<list<Cphone_info>>>::iterator it2;
	it2 = Cstatic_var::map_machine.find(s);
	int length = Cstatic_var::map_machine.count(s);
	printf("test_fun2,length=%d\n",length);
	//cout<<length<<"\n";
	printf("test_fun2,machine_account=%s\n",it2->first.c_str());
	//cout<<it2->first<<"-----"<<it2->second<<"\n";
	shared_ptr<list<Cphone_info>> plist_temp22 = it2->second;
	for (list<Cphone_info>::iterator it22 = plist_temp22->begin(); it22!=plist_temp22->end(); it22++) {
		printf("test_fun2,phone_account=%s\n",it22->phone_account.c_str());
		printf("test_fun2,phone_device_tocken=%s\n",it22->phone_device_tocken.c_str());
		
		
		//cout<<it2->phone_account<<"  "<<it2->phone_device_tocken<<"\n";
	}
	

	int max_numbers = Cstatic_var::map_machine.max_size();
	cout<<max_numbers<<"\n";
}
void person::test_fun3(){
	
//	multimap<string, string> m_map;
//	string s("abcd012345678901234567890123456789012345678901234567890123456789");
//	cout<<s.length()<<"\n";
//	string s1("152");
//	
//	m_map.insert(make_pair(s,"251"));
//	
//	m_map.insert(make_pair(s,"253"));
//	
//	m_map.insert(make_pair(s1,"255"));
//	m_map.insert(make_pair(s1,"256"));
//	m_map.insert(make_pair(s1,"257"));
//	m_map.insert(make_pair(s,"254"));
//	m_map.insert(make_pair(s1,"258"));
//	m_map.insert(make_pair(s,"252"));
//	
//	int k;
//	multimap<string,string>::iterator it2;
//	it2 = m_map.find(s);
//	int length = m_map.count(s);
//	cout<<length<<"\n";
//	for (k = 0; k != length;k++, it2++) {
//		cout<<it2->first<<"-----"<<it2->second<<"\n";
//	}
//	int max_numbers = m_map.max_size();
//	cout<<max_numbers<<"\n";
//	
//
//	
//	
//	cout<<"end......"<<endl;
}
void person::test_fun4(){
	cout<<"end......"<<endl;
	
}
void person::insert_phone_map(string str_device_tocken,string str_phone_account,string str_machine_account,string badge_identification)
{
	//printf("insert_phone_map,str_phone_account=%s\n",str_phone_account.c_str());
	//printf("insert_phone_map,str_machine_account=%s\n",str_machine_account.c_str());
	///////////////////////////////////////////////////
	Cmachine_info *list_machine_info = new Cmachine_info();
	list_machine_info->phone_account = "";
	list_machine_info->machine_account = "";
	list_machine_info->badge_identification = "";
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	list_machine_info->phone_account = str_phone_account;
	list_machine_info->machine_account = str_machine_account;
	list_machine_info->badge_identification = badge_identification;
	
	
	//auto list_machine_info2 = std::make_shared<Cmachine_info>(list_machine_info);
	auto list_machine_info2 = std::shared_ptr<Cmachine_info>(list_machine_info);
	Cstatic_var::map_phone.insert(make_pair(str_device_tocken, list_machine_info2));
	
}
void person::insert_phone_map_language(string str_device_tocken,string str_phone_account,string str_machine_account,string str_language)
{
	//printf("insert_phone_map,str_phone_account=%s\n",str_phone_account.c_str());
	//printf("insert_phone_map,str_machine_account=%s\n",str_machine_account.c_str());
	///////////////////////////////////////////////////
	Cmachine_info_language *list_machine_info = new Cmachine_info_language();
	list_machine_info->phone_account = "";
	list_machine_info->machine_account = "";
	list_machine_info->language = "";
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	list_machine_info->phone_account = str_phone_account;
	list_machine_info->machine_account = str_machine_account;
	list_machine_info->language = str_language;
	
	auto list_machine_info2 = std::shared_ptr<Cmachine_info_language>(list_machine_info);
	Cstatic_var::map_phone_language.insert(make_pair(str_device_tocken, list_machine_info2));
	
}
void person::insert_machine_map(string str_machine_account,string str_device_tocken,string str_phone_account)
{
	list<Cphone_info> *ll = new list<Cphone_info>;
	shared_ptr<list<Cphone_info>> plist_my(ll);
	///////////////////////////////////////////////////
	Cphone_info list_phone_info;
	list_phone_info.phone_device_tocken = "";
	list_phone_info.phone_account = "";

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	list_phone_info.phone_device_tocken = str_device_tocken;
	list_phone_info.phone_account = str_phone_account;

	
	////////////////////////////////////////////////////////////////
	string s = str_machine_account;
	
	map<string,shared_ptr<list<Cphone_info>>>::iterator it2;
	it2 = Cstatic_var::map_machine.find(s);
	int length = Cstatic_var::map_machine.count(s);
	//printf("insert_machine_map,length=%d\n",length);
	//cout<<length<<"\n";
	if (length <= 0) {
		plist_my->push_back(list_phone_info);
		//auto plist_my2 = std::make_shared<Cphone_info>(plist_my);
		Cstatic_var::map_machine.insert(make_pair(str_machine_account, plist_my));
	}else{
		shared_ptr<list<Cphone_info>> plist_temp22 = it2->second;
	
		plist_temp22->push_back(list_phone_info);
	}


	
}
void person::insert_event_cid_05_00_map(string str_machine_account,string str_alarm_event_cid)
{
	list<Cmachine_05_00_cid_info> *ll = new list<Cmachine_05_00_cid_info>;
	shared_ptr<list<Cmachine_05_00_cid_info>> plist_my(ll);
	///////////////////////////////////////////////////
	Cmachine_05_00_cid_info list_alarm_event_cid_info;
	list_alarm_event_cid_info.event_cid_05_00 = "";
	list_alarm_event_cid_info.time_start_05_00 = time((time_t *)NULL);
	
	list_alarm_event_cid_info.event_cid_05_00 = str_alarm_event_cid;
	
	////////////////////////////////////////////////////////////////
	string s = str_machine_account;
	
	map<string,shared_ptr<list<Cmachine_05_00_cid_info>>>::iterator it2;
	it2 = Cstatic_var::map_event_cid_05_00.find(s);
	int length = Cstatic_var::map_event_cid_05_00.count(s);
	//printf("insert_machine_map,length=%d\n",length);
	//cout<<length<<"\n";
	if (length <= 0) {
		plist_my->push_back(list_alarm_event_cid_info);
		//auto plist_my2 = std::make_shared<Cphone_info>(plist_my);
		Cstatic_var::map_event_cid_05_00.insert(make_pair(str_machine_account, plist_my));
	}else{
		shared_ptr<list<Cmachine_05_00_cid_info>> plist_temp22 = it2->second;
		
		plist_temp22->push_back(list_alarm_event_cid_info);
	}
	
	
	
}
void person::insert_alarm_event_cid_map(string str_machine_account,string str_alarm_event_cid,string str_date_time_cid)
{
	list<Calarm_event_cid_info> *ll = new list<Calarm_event_cid_info>;
	shared_ptr<list<Calarm_event_cid_info>> plist_my(ll);
	///////////////////////////////////////////////////
	Calarm_event_cid_info list_alarm_event_cid_info;
	list_alarm_event_cid_info.alarm_cid = "";
	list_alarm_event_cid_info.date_time_cid = "";
	list_alarm_event_cid_info.alarm_cid = str_alarm_event_cid;
	list_alarm_event_cid_info.date_time_cid = str_date_time_cid;
	////////////////////////////////////////////////////////////////
	string s = str_machine_account;
	
	map<string,shared_ptr<list<Calarm_event_cid_info>>>::iterator it2;
	it2 = Cstatic_var::map_alarm_cid.find(s);
	int length = Cstatic_var::map_alarm_cid.count(s);
	//printf("insert_machine_map,length=%d\n",length);
	//cout<<length<<"\n";
	if (length <= 0) {
		plist_my->push_back(list_alarm_event_cid_info);
		//auto plist_my2 = std::make_shared<Cphone_info>(plist_my);
		Cstatic_var::map_alarm_cid.insert(make_pair(str_machine_account, plist_my));
	}else{
		shared_ptr<list<Calarm_event_cid_info>> plist_temp22 = it2->second;
		
		plist_temp22->push_back(list_alarm_event_cid_info);
	}
	
	
	
}



void person::delete_from_map_event_cid_05_00(string str_machine_account,string str_event_cid_05_00)
{
	string s = str_machine_account;
	
	map<string,shared_ptr<list<Cmachine_05_00_cid_info>>>::iterator it2;
	it2 = Cstatic_var::map_event_cid_05_00.find(s);
	int length = Cstatic_var::map_event_cid_05_00.count(s);
	//printf("delete_from_map_event_cid_05_00,length=%d\n",length);
	//cout<<length<<"\n";
	if (length <= 0) {
		
	}else{
		shared_ptr<list<Cmachine_05_00_cid_info>> plist_temp22 = it2->second;
		int size_list = plist_temp22->size();
		//printf("delete_from_map_event_cid_05_00,size_list=%d\n",size_list);
		//plist_temp22->push_back(list_phone_info);
		for (list<Cmachine_05_00_cid_info>::iterator it = plist_temp22->begin(); it!=plist_temp22->end(); it++) {
//			cout<<it->event_cid_05_00<<"\n";
			string str_temp = it->event_cid_05_00;
			if (str_temp == str_event_cid_05_00) {
				it = plist_temp22->erase(it);
				size_list = plist_temp22->size();
				//printf("delete_from_map_event_cid_05_00,size_list=%d\n",size_list);
				break;
			}
		}
		if (size_list == 0) {
			it2 = Cstatic_var::map_event_cid_05_00.erase(it2);
		}
		
	}
	
}
void person::delete_from_map_machine(string str_machine_account,string str_device_tocken)
{
	string s = str_machine_account;

	map<string,shared_ptr<list<Cphone_info>>>::iterator it2;
	it2 = Cstatic_var::map_machine.find(s);
	int length = Cstatic_var::map_machine.count(s);
	printf("delete_from_map_machine,length=%d\n",length);
	//cout<<length<<"\n";
	if (length <= 0) {

	}else{
		shared_ptr<list<Cphone_info>> plist_temp22 = it2->second;
		int size_list = plist_temp22->size();
		printf("delete_from_map_machine,size_list=%d\n",size_list);
		//plist_temp22->push_back(list_phone_info);
		for (list<Cphone_info>::iterator it = plist_temp22->begin(); it!=plist_temp22->end(); it++) {
//			cout<<it->phone_device_tocken<<"\n";
			string str_temp = it->phone_device_tocken;
			if (str_temp == str_device_tocken) {
				it = plist_temp22->erase(it);
				size_list = plist_temp22->size();
				printf("delete_from_map_machine,size_list=%d\n",size_list);
				break;
			}
		}
		if (size_list == 0) {
			it2 = Cstatic_var::map_machine.erase(it2);
		}
		
	}
	
}


void person::delete_from_map_phone(string str_device_tocken)
{
	string s = str_device_tocken;

	map<string,shared_ptr<Cmachine_info>>::iterator it2;
	it2 = Cstatic_var::map_phone.find(s);
	int length = Cstatic_var::map_phone.count(s);
	//printf("delete_from_map_phone,length=%d\n",length);

	if (length <= 0) {
		
	}else{
		
		int size_list = Cstatic_var::map_phone.size();
		//printf("delete_from_map_phone,size_list=%d\n",size_list);
		//cout<<it2->first<<endl;
		shared_ptr<Cmachine_info> plist_temp22 = it2->second;
		//cout<<(plist_temp22->phone_account)<<"  "<<(plist_temp22->machine_account)<<"\n";
		//printf("delete_from_map_phone,phone_account=%s,machine_account=%s\n",
			   //plist_temp22->phone_account.c_str(),plist_temp22->machine_account.c_str());
		
		it2 = Cstatic_var::map_phone.erase(it2);
		
		size_list = Cstatic_var::map_phone.size();
		//printf("delete_from_map_phone,size_list=%d\n",size_list);
	}
	
}

void person::delete_from_map_phone_language(string str_device_tocken)
{
	string s = str_device_tocken;
	
	map<string,shared_ptr<Cmachine_info_language>>::iterator it2;
	it2 = Cstatic_var::map_phone_language.find(s);
	int length = Cstatic_var::map_phone_language.count(s);
	printf("delete_from_map_phone_language,length=%d\n",length);
	
	if (length <= 0) {
		
	}else{
		
		int size_list = Cstatic_var::map_phone_language.size();
		printf("delete_from_map_phone_language,size_list=%d\n",size_list);
		//cout<<it2->first<<endl;
		shared_ptr<Cmachine_info_language> plist_temp22 = it2->second;
		//cout<<(plist_temp22->phone_account)<<"  "<<(plist_temp22->machine_account)<<"\n";
		printf("delete_from_map_phone_language,phone_account=%s,machine_account=%s\n",
			   plist_temp22->phone_account.c_str(),plist_temp22->machine_account.c_str());
		
		it2 = Cstatic_var::map_phone_language.erase(it2);
		
		size_list = Cstatic_var::map_phone_language.size();
		printf("delete_from_map_phone_language,size_list=%d\n",size_list);
	}
	
}

string person::get_mahcine_account_from_map_phone(string str_device_tocken)
{
	string s = str_device_tocken;
	
	map<string,shared_ptr<Cmachine_info>>::iterator it2;
	it2 = Cstatic_var::map_phone.find(s);
	int length = Cstatic_var::map_phone.count(s);
	printf("get_mahcine_account_from_map_phone,length=%d\n",length);
	
	if (length <= 0) {
		
	}else{
		
		int size_list = Cstatic_var::map_phone.size();
		printf("get_mahcine_account_from_map_phone,size_list=%d\n",size_list);
//		cout<<it2->first<<endl;
		shared_ptr<Cmachine_info> plist_temp22 = it2->second;
		//cout<<(plist_temp22->phone_account)<<"  "<<(plist_temp22->machine_account)<<"\n";
		printf("delete_from_map_phone,phone_account=%s,machine_account=%s,badge_identification=%s\n",
			   plist_temp22->phone_account.c_str(),plist_temp22->badge_identification.c_str());
		return plist_temp22->machine_account;
		
		
	}
	return "";
}
string person::get_badge_identification_from_map_phone(string str_device_tocken)
{
	string s = str_device_tocken;
	
	map<string,shared_ptr<Cmachine_info>>::iterator it2;
	it2 = Cstatic_var::map_phone.find(s);
	int length = Cstatic_var::map_phone.count(s);
	//printf("get_badge_identification_from_map_phone,length=%d\n",length);
	
	if (length <= 0) {
		
	}else{
		
		int size_list = Cstatic_var::map_phone.size();
		//printf("get_badge_identification_from_map_phone,size_list=%d\n",size_list);
		shared_ptr<Cmachine_info> plist_temp22 = it2->second;
		//cout<<(plist_temp22->phone_account)<<"  "<<(plist_temp22->machine_account)<<"\n";
		//printf("get_badge_identification_from_map_phone,phone_account=%s,machine_account=%s,badge_identification=%s\n",
			   //plist_temp22->phone_account.c_str(),plist_temp22->machine_account.c_str(),plist_temp22->badge_identification.c_str());
		return plist_temp22->badge_identification;
		
		
	}
	return "";
}

string person::get_language_from_map_phone(string str_device_tocken)
{
	string s = str_device_tocken;
	
	map<string,shared_ptr<Cmachine_info_language>>::iterator it2;
	it2 = Cstatic_var::map_phone_language.find(s);
	int length = Cstatic_var::map_phone_language.count(s);
	//printf("get_language_from_map_phone,length=%d\n",length);
	
	if (length <= 0) {
		
	}else{
		
		int size_list = Cstatic_var::map_phone_language.size();
		//printf("get_language_from_map_phone,size_list=%d\n",size_list);
		shared_ptr<Cmachine_info_language> plist_temp22 = it2->second;
		//cout<<(plist_temp22->phone_account)<<"  "<<(plist_temp22->machine_account)<<"\n";
		//printf("get_language_from_map_phone,phone_account=%s,machine_account=%s,language=%s\n",
			  // plist_temp22->phone_account.c_str(),plist_temp22->machine_account.c_str(),plist_temp22->language.c_str());
		return plist_temp22->language;
		
		
	}
	return "";
}

void person::traversing_machine_map()
{
	if (Cstatic_var::map_machine.empty()) {
		//printf("traversing_machine_map,m_count_machine_map=%d\n",0);
		return;
	}
	//int m_count_machine_map = Cstatic_var::map_machine.size();
	
	//printf("traversing_machine_map,m_count_machine_map=%d\n",m_count_machine_map);
	if(1){
		lock_guard<mutex> guard(std::mutex mutex_map_machine);
		map<string,shared_ptr<list<Cphone_info>>>::iterator it_temp22=Cstatic_var::map_machine.begin();
		
		for (; it_temp22!=Cstatic_var::map_machine.end(); ++it_temp22)
		{
			//printf("traversing_machine_map,machine_account=%s\n",it_temp22->first.c_str());
			//cout<<it_temp22->first<<endl;
			
			
			shared_ptr<list<Cphone_info>> plist_temp22 = it_temp22->second;
			//int count_list = it_temp22->second->size();
			//printf("traversing_machine_map,count_list=%d\n",count_list);
			for (list<Cphone_info>::iterator it2 = plist_temp22->begin(); it2!=plist_temp22->end(); it2++) {
				//printf("traversing_machine_map,phone_account=%s\n",it2->phone_account.c_str());
				//printf("traversing_machine_map,phone_device_tocken=%s\n",it2->phone_device_tocken.c_str());
				
			}
			
			
		}
	}
	
}

void person::release_event_cid_05_00_map()
{
	if (Cstatic_var::map_event_cid_05_00.empty()) {
		//printf("release_event_cid_05_00_map,m_count_alarm_event_cid_map=%d\n",0);
		return;
	}
	int m_count_machine_map = Cstatic_var::map_event_cid_05_00.size();
	
	//printf("traversing_machine_map,m_count_machine_map=%d\n",m_count_machine_map);
	if(1){
		lock_guard<mutex> guard(std::mutex mutex_map_event_cid_05_00);
		map<string,shared_ptr<list<Cmachine_05_00_cid_info>>>::iterator it_temp22=Cstatic_var::map_event_cid_05_00.begin();
		
		for (; it_temp22!=Cstatic_var::map_event_cid_05_00.end(); ++it_temp22)
		{
			//printf("release_event_cid_05_00_map,machine_account=%s\n",it_temp22->first.c_str());
			//cout<<it_temp22->first<<endl;
			
			
			shared_ptr<list<Cmachine_05_00_cid_info>> plist_temp22 = it_temp22->second;
			int count_list = it_temp22->second->size();
			//printf("traversing_machine_map,count_list=%d\n",count_list);
			if (count_list > 0) {
				for (list<Cmachine_05_00_cid_info>::iterator it2 = plist_temp22->begin(); it2!=plist_temp22->end(); it2++) {
					
					//printf("release_event_cid_05_00_map,alarm_cid_05_00=%s,m_count_machine_map=%d,count_list=%d\n",it2->event_cid_05_00.c_str(),m_count_machine_map,count_list);
					
					time_t time_temp = time((time_t *)NULL);
					time_t seconds_interval = time_temp - it2->time_start_05_00;
					if (seconds_interval > 3) {
						it2 = plist_temp22->erase(it2);
					}
					
				}
			}else if (count_list == 0) {
				it_temp22 = Cstatic_var::map_event_cid_05_00.erase(it_temp22);
			}
			
			
			
		}
	}
	
}

void person::traversing_event_cid_05_00_map()
{
	if (Cstatic_var::map_event_cid_05_00.empty()) {
		printf("traversing_event_cid_05_00_map,m_count_alarm_event_cid_map=%d\n",0);
		return;
	}
	int m_count_machine_map = Cstatic_var::map_event_cid_05_00.size();
	
	//printf("traversing_machine_map,m_count_machine_map=%d\n",m_count_machine_map);
	if(1){
		lock_guard<mutex> guard(std::mutex mutex_map_event_cid_05_00);
		map<string,shared_ptr<list<Cmachine_05_00_cid_info>>>::iterator it_temp22=Cstatic_var::map_event_cid_05_00.begin();
		
		for (; it_temp22!=Cstatic_var::map_event_cid_05_00.end(); ++it_temp22)
		{
			printf("traversing_event_cid_05_00_map,machine_account=%s\n",it_temp22->first.c_str());
			//cout<<it_temp22->first<<endl;
			
			
			shared_ptr<list<Cmachine_05_00_cid_info>> plist_temp22 = it_temp22->second;
			int count_list = it_temp22->second->size();
			//printf("traversing_machine_map,count_list=%d\n",count_list);
			for (list<Cmachine_05_00_cid_info>::iterator it2 = plist_temp22->begin(); it2!=plist_temp22->end(); it2++) {
				//printf("traversing_machine_map,phone_account=%s\n",it2->phone_account.c_str());
				printf("traversing_event_cid_05_00_map,alarm_cid_05_00=%s,m_count_machine_map=%d,count_list=%d\n",it2->event_cid_05_00.c_str(),m_count_machine_map,count_list);
				
			}
			
			
		}
	}
	
}
void person::traversing_alarm_event_cid_map()
{
	if (Cstatic_var::map_alarm_cid.empty()) {
		printf("traversing_alarm_event_cid_map,m_count_alarm_event_cid_map=%d\n",0);
		return;
	}
	int m_count_machine_map = Cstatic_var::map_machine.size();
	
	//printf("traversing_machine_map,m_count_machine_map=%d\n",m_count_machine_map);
	if(1){
		lock_guard<mutex> guard(std::mutex mutex_map_alarm_event_cid);
		map<string,shared_ptr<list<Calarm_event_cid_info>>>::iterator it_temp22=Cstatic_var::map_alarm_cid.begin();
		
		for (; it_temp22!=Cstatic_var::map_alarm_cid.end(); ++it_temp22)
		{
			printf("traversing_alarm_event_cid_map,machine_account=%s\n",it_temp22->first.c_str());
			//cout<<it_temp22->first<<endl;
			
			
			shared_ptr<list<Calarm_event_cid_info>> plist_temp22 = it_temp22->second;
			int count_list = it_temp22->second->size();
			//printf("traversing_machine_map,count_list=%d\n",count_list);
			for (list<Calarm_event_cid_info>::iterator it2 = plist_temp22->begin(); it2!=plist_temp22->end(); it2++) {
				//printf("traversing_machine_map,phone_account=%s\n",it2->phone_account.c_str());
				printf("traversing_alarm_event_cid_map,alarm_cid=%s,m_count_machine_map=%d,count_list=%d\n",it2->alarm_cid.c_str(),m_count_machine_map,count_list);
				printf("traversing_alarm_event_cid_map,date_time_cid=%s,m_count_machine_map=%d,count_list=%d\n",it2->date_time_cid.c_str(),m_count_machine_map,count_list);
			}
			
			
		}
	}
	
}
void person::pop_pront_alarm_event_cid_map(string str_machine_account)
{
	if (Cstatic_var::map_alarm_cid.empty()) {
		printf("pop_pront_alarm_event_cid_map,m_count_alarm_event_cid_map=%d\n",0);
		return;
	}
	int m_count_machine_map = Cstatic_var::map_machine.size();
	
	//printf("traversing_machine_map,m_count_machine_map=%d\n",m_count_machine_map);
	///////////////////////////////////////////////////////////////////////////////
	string s = str_machine_account;
	map<string,shared_ptr<list<Calarm_event_cid_info>>>::iterator it2;
	it2 = Cstatic_var::map_alarm_cid.find(s);
	int length = Cstatic_var::map_alarm_cid.count(s);
	//printf("pop_pront_alarm_event_cid_map,length=%d\n",length);
	if (length > 0) {
		//printf("pop_pront_alarm_event_cid_map,machine_account=%s\n",it2->first.c_str());
		shared_ptr<list<Calarm_event_cid_info>> plist_temp22 = it2->second;
		
		int count_list = plist_temp22->size();
		//printf("pop_pront_alarm_event_cid_map,count_list=%d\n",count_list);
		if (count_list >= 21) {
			plist_temp22->pop_front();
		}
//		for (list<Calarm_event_cid_info>::iterator it22 = plist_temp22->begin(); it22!=plist_temp22->end(); it22++) {
//			//printf("traversing_machine_map,phone_account=%s\n",it2->phone_account.c_str());
//			printf("pop_pront_alarm_event_cid_map,alarm_cid=%s,m_count_machine_map=%d,count_list=%d\n",it22->alarm_cid.c_str(),m_count_machine_map,count_list);
//			Cstatic_var::apns_push_message(it2->first,(char *)it22->alarm_cid.c_str());
//			
//		}
		
	}
	////////////////////////////////////////////////////////////////////////////
	
}
void person::send_history_alarm_event_cid_map(string str_machine_account)
{
	if (Cstatic_var::map_alarm_cid.empty()) {
		printf("send_history_alarm_event_cid_map,m_count_alarm_event_cid_map=%d\n",0);
		return;
	}
	int m_count_machine_map = Cstatic_var::map_machine.size();
	
	//printf("traversing_machine_map,m_count_machine_map=%d\n",m_count_machine_map);
	///////////////////////////////////////////////////////////////////////////////
	string s = str_machine_account;
	map<string,shared_ptr<list<Calarm_event_cid_info>>>::iterator it2;
	it2 = Cstatic_var::map_alarm_cid.find(s);
	int length = Cstatic_var::map_alarm_cid.count(s);
	printf("send_history_alarm_event_cid_map,length=%d\n",length);
	if (length > 0) {
		printf("send_history_alarm_event_cid_map,machine_account=%s\n",it2->first.c_str());
		shared_ptr<list<Calarm_event_cid_info>> plist_temp22 = it2->second;
		
		int count_list = plist_temp22->size();
		printf("send_history_alarm_event_cid_map,count_list=%d\n",count_list);
		if (count_list > 0) {
			for (list<Calarm_event_cid_info>::iterator it22 = plist_temp22->begin(); it22!=plist_temp22->end(); it22++) {
				//printf("traversing_machine_map,phone_account=%s\n",it2->phone_account.c_str());
				printf("send_history_alarm_event_cid_map,alarm_cid=%s,m_count_machine_map=%d,count_list=%d\n",it22->alarm_cid.c_str(),m_count_machine_map,count_list);
				Cstatic_var::apns_push_message(it2->first,(char *)it22->alarm_cid.c_str());
				
			}
		}
		
		
	}
	////////////////////////////////////////////////////////////////////////////
	
}

void person::send_history_alarm_event_cid_map_0f_04(string str_machine_account,unsigned int conn_number,int sock_recv)
{
	if (Cstatic_var::map_alarm_cid.empty()) {
		//printf("send_history_alarm_event_cid_map_0f_04,m_count_alarm_event_cid_map=%d\n",0);
		return;
	}
	int m_count_machine_map = Cstatic_var::map_machine.size();
	
	//printf("traversing_machine_map,m_count_machine_map=%d\n",m_count_machine_map);
	///////////////////////////////////////////////////////////////////////////////
	string s = str_machine_account;
	map<string,shared_ptr<list<Calarm_event_cid_info>>>::iterator it2;
	it2 = Cstatic_var::map_alarm_cid.find(s);
	int length = Cstatic_var::map_alarm_cid.count(s);
	//printf("send_history_alarm_event_cid_map_0f_04,length=%d\n",length);
	if (length > 0) {
		//printf("send_history_alarm_event_cid_map_0f_04,machine_account=%s\n",it2->first.c_str());
		shared_ptr<list<Calarm_event_cid_info>> plist_temp22 = it2->second;
		
		int count_list = plist_temp22->size();
		//printf("send_history_alarm_event_cid_map_0f_04,count_list=%d\n",count_list);
		string str_cid = "";
		if (count_list > 0) {
			for (list<Calarm_event_cid_info>::iterator it22 = plist_temp22->begin(); it22!=plist_temp22->end(); it22++) {
				//printf("traversing_machine_map,phone_account=%s\n",it2->phone_account.c_str());
				//printf("send_history_alarm_event_cid_map_0f_04,alarm_cid=%s,m_count_machine_map=%d,count_list=%d\n",it22->alarm_cid.c_str(),m_count_machine_map,count_list);
				//printf("send_history_alarm_event_cid_map_0f_04,date_time_cid=%s,m_count_machine_map=%d,count_list=%d\n",it22->date_time_cid.c_str(),m_count_machine_map,count_list);
				
				str_cid = str_cid + it22->alarm_cid + it22->date_time_cid;
			}
		}
        printf("send_history_alarm_event_cid_map_0f_04,str_cid=%s\n",(char*)str_cid.c_str());
		Cstatic_var::send_clear_badges_to_app_0f_04(conn_number,sock_recv,count_list,(char*)str_cid.c_str());
		
		
	}
	////////////////////////////////////////////////////////////////////////////
	
}

void person::csv_read_phone_map()
{
	Cstatic_var::p_csv->createfile_read("map_phone.csv");
	//string str_get_line = "";
	Cstatic_var::p_csv->read_phone();
	
	Cstatic_var::p_csv->infile.close();
	
}
void person::csv_read_phone_map_language()
{
	Cstatic_var::p_csv->createfile_read("map_phone_language.csv");
	//string str_get_line = "";
	Cstatic_var::p_csv->read_phone_language();
	
	Cstatic_var::p_csv->infile.close();
	
}
void person::csv_read_machine_map()
{
	Cstatic_var::p_csv->createfile_read("map_machine.csv");
	//string str_get_line = "";
	Cstatic_var::p_csv->read_machine();
	
	Cstatic_var::p_csv->infile.close();
	
}
void person::csv_write_phone_map()
{
	Cstatic_var::p_csv->createfile_phone("map_phone.csv");
	//int m_count_map_phone = Cstatic_var::map_phone.size();
	//printf("csv_write_phone_map,m_count_map_phone=%d\n",m_count_map_phone);
	//cout<<"test_fun4,m_count_map_phone="<<m_count_map_phone<<endl;
	map<string,shared_ptr<Cmachine_info>>::iterator it_temp22=Cstatic_var::map_phone.begin();
	
	for (; it_temp22!=Cstatic_var::map_phone.end(); ++it_temp22)
	{
		//printf("csv_write_phone_map,phone_device_tocken=%s\n",it_temp22->first.c_str());
		//cout<<it_temp22->first<<endl;
		
		shared_ptr<Cmachine_info> plist_temp22 = it_temp22->second;
		//printf("csv_write_phone_map,phone_account=%s\n",plist_temp22->phone_account.c_str());
		//printf("csv_write_phone_map,machine_account=%s\n",plist_temp22->machine_account.c_str());
		//printf("csv_write_phone_map,badge_identification=%s\n",plist_temp22->badge_identification());
		string str_csv_write = it_temp22->first + "," + plist_temp22->phone_account + "," + plist_temp22->machine_account + "," + plist_temp22->badge_identification;
		Cstatic_var::p_csv->write_phone(str_csv_write);
		
	}
	
	Cstatic_var::p_csv->outfile_phone.close();
	
}


void person::csv_write_phone_map_language()
{
	Cstatic_var::p_csv->createfile_phone("map_phone_language.csv");
	//int m_count_map_phone = Cstatic_var::map_phone.size();
	//printf("csv_write_phone_map,m_count_map_phone=%d\n",m_count_map_phone);
	//cout<<"test_fun4,m_count_map_phone="<<m_count_map_phone<<endl;
	map<string,shared_ptr<Cmachine_info_language>>::iterator it_temp22=Cstatic_var::map_phone_language.begin();
	
	for (; it_temp22!=Cstatic_var::map_phone_language.end(); ++it_temp22)
	{
		//printf("csv_write_phone_map,phone_device_tocken=%s\n",it_temp22->first.c_str());
		//cout<<it_temp22->first<<endl;
		
		shared_ptr<Cmachine_info_language> plist_temp22 = it_temp22->second;
		//printf("csv_write_phone_map,phone_account=%s\n",plist_temp22->phone_account.c_str());
		//printf("csv_write_phone_map,machine_account=%s\n",plist_temp22->machine_account.c_str());
		//printf("csv_write_phone_map,badge_identification=%s\n",plist_temp22->badge_identification());
		string str_csv_write = it_temp22->first + "," + plist_temp22->phone_account + "," + plist_temp22->machine_account + "," + plist_temp22->language;
		Cstatic_var::p_csv->write_phone(str_csv_write);
		
	}
	
	Cstatic_var::p_csv->outfile_phone.close();
	
}

void person::csv_write_machine_map()
{
	Cstatic_var::p_csv->createfile_machine("map_machine.csv");
	//int m_count_machine_map = Cstatic_var::map_machine.size();
	//printf("csv_write_machine_map,m_count_machine_map=%d\n",m_count_machine_map);
	map<string,shared_ptr<list<Cphone_info>>>::iterator it_temp22=Cstatic_var::map_machine.begin();
	
	
	string str_csv_write = "";
	int ii = 0;
	for (; it_temp22!=Cstatic_var::map_machine.end(); ++it_temp22)
	{
		//printf("csv_write_machine_map,machine_account=%s\n",it_temp22->first.c_str());
		//cout<<it_temp22->first<<endl;
		
		str_csv_write = it_temp22->first + ",";
		shared_ptr<list<Cphone_info>> plist_temp22 = it_temp22->second;
		int count_list = it_temp22->second->size();
		//printf("csv_write_machine_map,count_list=%d\n",count_list);
		str_csv_write = str_csv_write + std::to_string(count_list) + ",";
		//////////////////////////
		for (list<Cphone_info>::iterator it2 = plist_temp22->begin(); it2!=plist_temp22->end(); it2++) {
			//			printf("csv_write_machine_map,phone_account=%s\n",it2->phone_account.c_str());
			//			printf("csv_write_machine_map,phone_device_tocken=%s\n",it2->phone_device_tocken.c_str());
			
			//cout<<it2->phone_account<<"  "<<it2->phone_device_tocken<<"\n";
			ii++;
			if (ii == count_list) {
				str_csv_write = str_csv_write + it2->phone_account + "," + it2->phone_device_tocken ;
				ii = 0;
			}else if (ii < count_list)
			{
				str_csv_write = str_csv_write + it2->phone_account + "," + it2->phone_device_tocken + ",";
			}
			
		}
		//printf("csv_write_machine_map,str_csv_write=%s\n",str_csv_write.c_str());
		Cstatic_var::p_csv->write_machine(str_csv_write);
		
	}
	//Cstatic_var::p_csv->write("111,222,333");
	Cstatic_var::p_csv->outfile_machine.close();
	
}

int person::query_status_from_machine_05_00_cid_map(string str_machine_account,string str_event_cid_05_00)
{
	int status = -1;
	string s = str_machine_account;
	map<string,shared_ptr<list<Cmachine_05_00_cid_info>>>::iterator it2;
	it2 = Cstatic_var::map_event_cid_05_00.find(s);
	int length = Cstatic_var::map_event_cid_05_00.count(s);
	//printf("query_status_from_machine_05_00_cid_map,length=%d\n",length);
	if (length <= 0) {
		status = 3;//no machine
	}else{
		status = 1;//have machine
		shared_ptr<list<Cmachine_05_00_cid_info>> plist_temp22 = it2->second;
		bool bool_flag = false;
		for (list<Cmachine_05_00_cid_info>::iterator it = plist_temp22->begin(); it!=plist_temp22->end(); it++) {
		
			string str_temp = it->event_cid_05_00;
			
			if (str_temp == str_event_cid_05_00) {
				
				{
					status = 1;//have machine and have cid
					bool_flag = true;
					break;
					
				}
			}
		}
		if (!bool_flag) {
			status = 3;//have machine and no cid
		}
		
		
	}
	return status;
	
}
int person::query_status_from_machine_map(string str_machine_account,string str_device_tocken,string str_phone_account)
{
	int status = -1;
	string s = str_machine_account;
	map<string,shared_ptr<list<Cphone_info>>>::iterator it2;
	it2 = Cstatic_var::map_machine.find(s);
	int length = Cstatic_var::map_machine.count(s);
	//printf("query_status_from_machine_map,length=%d\n",length);
	if (length <= 0) {
		status = 3;//no machine
	}else{
		status = 0;//have machine
		shared_ptr<list<Cphone_info>> plist_temp22 = it2->second;
		bool bool_flag = false;
		for (list<Cphone_info>::iterator it = plist_temp22->begin(); it!=plist_temp22->end(); it++) {
			//cout<<it->phone_device_tocken<<"\n";
			string str_temp = it->phone_device_tocken;
			
			if (str_temp == str_device_tocken) {
				
				{
					status = 1;//have machine and have devicetocken
					bool_flag = true;
					break;
					
				}
			}
		}
		if (!bool_flag) {
			status = 2;//have machine and no devicetocken
		}
		
		
	}
	return status;
	
}
int person::query_status_from_phone_map(string str_device_tocken)
{
	int status = -1;
	string s = str_device_tocken;
	
	map<string,shared_ptr<Cmachine_info>>::iterator it2;
	it2 = Cstatic_var::map_phone.find(s);
	int length = Cstatic_var::map_phone.count(s);
	//printf("query_status_from_phone_map,length=%d\n",length);
	
	if (length == 0) {
		status = -1;
	}else{
		
		status = 0;//have devicetocken
	}
	
	return status;
}

int person::query_status_from_phone_map_language(string str_device_tocken)
{
	int status = -1;
	string s = str_device_tocken;
	
	map<string,shared_ptr<Cmachine_info_language>>::iterator it2;
	it2 = Cstatic_var::map_phone_language.find(s);
	int length = Cstatic_var::map_phone_language.count(s);
	//printf("query_status_from_phone_map,length=%d\n",length);
	
	if (length == 0) {
		status = -1;
	}else{
		
		status = 0;//have devicetocken
	}
	
	return status;
}

void person::delete_list_element_from_map_machine(string str_machine_account,string str_device_tocken)
{
	string s = str_machine_account;
	
	map<string,shared_ptr<list<Cphone_info>>>::iterator it2;
	it2 = Cstatic_var::map_machine.find(s);
	int length = Cstatic_var::map_machine.count(s);
	//printf("delete_from_map_machine,length=%d\n",length);
	//cout<<length<<"\n";
	if (length <= 0) {
		
	}else{
		shared_ptr<list<Cphone_info>> plist_temp22 = it2->second;
		//int size_list = plist_temp22->size();
		//printf("delete_from_map_machine,size_list=%d\n",size_list);
		//plist_temp22->push_back(list_phone_info);
		for (list<Cphone_info>::iterator it = plist_temp22->begin(); it!=plist_temp22->end(); it++) {
			//cout<<it->phone_device_tocken<<"\n";
			string str_temp = it->phone_device_tocken;
			if (str_temp == str_device_tocken) {
				
				it = plist_temp22->erase(it);
				//int size_list = plist_temp22->size();
				//printf("delete_from_map_machine,size_list=%d\n",size_list);
				break;
			}
		}
		
	}
	
}

int person::query_status_from_machine_map_0e_02(string str_machine_account,string str_device_tocken,string str_phone_account)
{
	int status = -1;
	string s = str_machine_account;
	map<string,shared_ptr<list<Cphone_info>>>::iterator it2;
	it2 = Cstatic_var::map_machine.find(s);
	int length = Cstatic_var::map_machine.count(s);
	//printf("query_status_from_machine_map,length=%d\n",length);
	if (length <= 0) {
		status = 3;//no machine
	}else{
		status = 0;//have machine
		shared_ptr<list<Cphone_info>> plist_temp22 = it2->second;
		bool bool_flag = false;
		for (list<Cphone_info>::iterator it = plist_temp22->begin(); it!=plist_temp22->end(); it++) {
			//cout<<it->phone_device_tocken<<"\n";
			string str_temp = it->phone_device_tocken;
			
			if (str_temp == str_device_tocken){
				status = 4;//have machine and have devicetocken
				bool_flag = true;
				break;
			}
		}
		if (!bool_flag) {
			status = 2;//have machine and no devicetocken
		}
		
		
	}
	return status;
	
}

int person::get_event_type(string str_cid,string str_language){
    string str_cid_event = str_cid.substr(8,4);

    if (str_language == "China") {
        if (str_cid_event =="1110") {
            return 1;
        }else if (str_cid_event =="1131") {//Perimeter
            return 4;
        }else if (str_cid_event =="1130") {//Emergency
            return 4;
        }else if (str_cid_event =="1120") {//Burglar
            return 5;
        }else if (str_cid_event =="1121") {//Help
            return 5;
        }else if (str_cid_event =="1151") {//Gas
            return 2;
        }else if (str_cid_event =="1113") {//Water
            return 3;
        }else if (str_cid_event =="1380") {//Abnormal Detector
            return 99;
        }else if (str_cid_event =="1384") {//Low Battery
            return 99;
        }else if (str_cid_event =="1383") {//Tamper
            return 99;
        }else if (str_cid_event =="1100") {//Medical
            return 99;
        }else if (str_cid_event =="1400") {//Disarm
            return 99;
        }else if (str_cid_event =="3400") {//All Arm
            return 99;
        }else if (str_cid_event =="1456") {//Part Arm
            return 99;
        }else if (str_cid_event =="1301") {//Electric City Low Battery
            return 99;
        }else if (str_cid_event =="1302") {//Spare battery Low Battery
            return 99;
        }else if (str_cid_event =="3301") {//Electric City Low Battery Restore
            return 99;
        }else if (str_cid_event =="3302") {//Spare battery Low Battery Restore
            return 99;
        }

    }else{
        if (str_cid_event =="1110") {
            return 1;
        }else if (str_cid_event =="1131") {
            return 4;
        }else if (str_cid_event =="1130") {
            return 4;
        }else if (str_cid_event =="1120") {
            return 5;
        }else if (str_cid_event =="1121") {
            return 5;
        }else if (str_cid_event =="1151") {//Gas
            return 2;
        }else if (str_cid_event =="1113") {//Water
            return 3;
        }else if (str_cid_event =="1380") {//Abnormal Detector
            return 99;
        }else if (str_cid_event =="1384") {//Low Battery
            return 99;
        }else if (str_cid_event =="1383") {//Tamper
            return 99;
        }else if (str_cid_event =="1100") {//Medical
            return 99;
        }else if (str_cid_event =="1400") {//Disarm
            return 99;
        }else if (str_cid_event =="3400") {//All Arm
            return 99;
        }else if (str_cid_event =="1456") {//Part Arm
            return 99;
        }else if (str_cid_event =="1301") {//Electric City Low Battery
            return 99;
        }else if (str_cid_event =="1302") {//Spare battery Low Battery
            return 99;
        }else if (str_cid_event =="3301") {//Electric City Low Battery Restore
            return 99;

        }else if (str_cid_event =="3302") {//Spare battery Low Battery Restore
            return 99;

        }

    }
    return -1;
}

void  person::cid_to_chinese_or_english_cid(string  str_cid,string &str_cid_chinese_or_english,string str_language)
{
	string str_cid_event_temp = "";
	string str_cid_event = str_cid.substr(8,4);
	//printf("cid_to_chinese_or_english_cid,str_cid_event=%s\n",str_cid_event.c_str());
	string str_cid_defence_area_number = str_cid.substr(16,3);
	//printf("cid_to_chinese_or_english_cid,str_cid_defence_area_number=%s\n",str_cid_defence_area_number.c_str());
	int i_cid_defence_area_number = std::atoi(str_cid_defence_area_number.c_str());
	string str_cid_defence_area_number2 = std::to_string(i_cid_defence_area_number);
	//printf("cid_to_chinese_or_english_cid,str_cid_defence_area_number2=%s\n",str_cid_defence_area_number2.c_str());
	//printf("cid_to_chinese_or_english_cid,str_language=%s\n",str_language.c_str());
	if (str_language == "China") {
		if (str_cid_event =="1110") {
			str_cid_event_temp = "火警";
		}else if (str_cid_event =="1131") {
			str_cid_event_temp = "周界报警";
		}else if (str_cid_event =="1120") {
			str_cid_event_temp = "紧急报警";
		}else if (str_cid_event =="1130") {
			str_cid_event_temp = "盗警";
		}else if (str_cid_event =="1121") {
			str_cid_event_temp = "胁迫";
		}else if (str_cid_event =="1151") {
			str_cid_event_temp = "煤气";
		}else if (str_cid_event =="1113") {
			str_cid_event_temp = "水警";
		}else if (str_cid_event =="1380") {
			str_cid_event_temp = "探头异常";
		}else if (str_cid_event =="1384") {
			str_cid_event_temp = "电源故障低电";
		}else if (str_cid_event =="1383") {
			str_cid_event_temp = "防拆";
		}else if (str_cid_event =="1110") {
			str_cid_event_temp = "医疗";
		}else if (str_cid_event =="1400") {
			str_cid_event_temp = "撤防";
		}else if (str_cid_event =="3400") {
			str_cid_event_temp = "全局布防";
		}else if (str_cid_event =="1456") {
			str_cid_event_temp = "半布防";
		}else if (str_cid_event =="1301") {
			str_cid_event_temp = "市电掉电";
		}else if (str_cid_event =="1302") {
			str_cid_event_temp = "备用电池低电";
		}else if (str_cid_event =="3301") {
			str_cid_event_temp = "市电掉电恢复";
		}else if (str_cid_event =="3302") {
			str_cid_event_temp = "备用电池低电恢复";
		}
		if (str_cid_defence_area_number2 == "0") {
			str_cid_defence_area_number2 = "主机";
		}else{
			str_cid_defence_area_number2 = str_cid_defence_area_number2 + "号防区";
		}
	}else{
		if (str_cid_event =="1110") {
			str_cid_event_temp = "Fire";
		}else if (str_cid_event =="1131") {
			str_cid_event_temp = "Perimeter";
		}else if (str_cid_event =="1120") {
			str_cid_event_temp = "Emergency";
		}else if (str_cid_event =="1130") {
			str_cid_event_temp = "Burglar";
		}else if (str_cid_event =="1121") {
			str_cid_event_temp = "Help";
		}else if (str_cid_event =="1151") {
			str_cid_event_temp = "Gas";
		}else if (str_cid_event =="1113") {
			str_cid_event_temp = "Water";
		}else if (str_cid_event =="1380") {
			str_cid_event_temp = "Abnormal Detector";
		}else if (str_cid_event =="1384") {
			str_cid_event_temp = "Low Battery";
		}else if (str_cid_event =="1383") {
			str_cid_event_temp = "Tamper";
		}else if (str_cid_event =="1110") {
			str_cid_event_temp = "Medical";
		}else if (str_cid_event =="1400") {
			str_cid_event_temp = "Disarm";
		}else if (str_cid_event =="3400") {
			str_cid_event_temp = "All Arm";
		}else if (str_cid_event =="1456") {
			str_cid_event_temp = "Part Arm";
		}else if (str_cid_event =="1301") {
			str_cid_event_temp = "Electric City Low Battery";
		}else if (str_cid_event =="1302") {
			str_cid_event_temp = "Spare battery Low Battery";
		}else if (str_cid_event =="3301") {
			str_cid_event_temp = "Electric City Low Battery Restore";
		}else if (str_cid_event =="3302") {
			str_cid_event_temp = "Spare battery Low Battery Restore";
		}
		if (str_cid_defence_area_number2 == "0") {
			str_cid_defence_area_number2 = "Alarm Panel";
		}else{
			str_cid_defence_area_number2 = "Zone No." + str_cid_defence_area_number2;
		}
	}
	
	//string str_temp =
	str_cid_chinese_or_english = str_cid_event_temp + "," + str_cid_defence_area_number2 + "  " + str_cid;
	
}

void  person::cid_to_chinese_or_english_cid_yfn(string  str_cid,string &str_cid_chinese_or_english,string str_language)
{
	string str_cid_event_temp = "";
	string str_cid_event = str_cid.substr(8,4);
	printf("cid_to_chinese_or_english_cid,str_cid_event=%s\n",str_cid_event.c_str());
	string str_cid_defence_area_number = str_cid.substr(16,3);
	string str_cid_defence_area_number_remote = str_cid.substr(18,1);
	string str_cid_defence_area_number_two = str_cid.substr(17,2);
	printf("cid_to_chinese_or_english_cid,str_cid_defence_area_number=%s\n",str_cid_defence_area_number.c_str());
	int i_cid_defence_area_number = std::atoi(str_cid_defence_area_number.c_str());
	string str_cid_defence_area_number2 = std::to_string(i_cid_defence_area_number);
	printf("cid_to_chinese_or_english_cid,str_cid_defence_area_number2=%s\n",str_cid_defence_area_number2.c_str());
	//printf("cid_to_chinese_or_english_cid,str_language=%s\n",str_language.c_str());





    string str_value_returnString = "";
	if (str_language == "China") {
		if (str_cid_event =="1110") {
			str_cid_event_temp = "火警";
		}else if (str_cid_event =="1131") {
			str_cid_event_temp = "周界报警";
		}else if (str_cid_event =="1120") {
			str_cid_event_temp = "紧急报警";
		}else if (str_cid_event =="1130") {
			str_cid_event_temp = "盗警";
		}else if (str_cid_event =="1121") {
			str_cid_event_temp = "胁迫";
		}else if (str_cid_event =="1151") {
			str_cid_event_temp = "煤气";
		}else if (str_cid_event =="1113") {
			str_cid_event_temp = "水警";
		}else if (str_cid_event =="1380") {
			str_cid_event_temp = "探头异常";
		}else if (str_cid_event =="1384") {
			str_cid_event_temp = "电源故障低电";
		}else if (str_cid_event =="1383") {
			str_cid_event_temp = "防拆";
		}else if (str_cid_event =="1110") {
			str_cid_event_temp = "医疗";
		}else if (str_cid_event =="1400") {
			str_cid_event_temp = "撤防";
		}else if (str_cid_event =="3400") {
			str_cid_event_temp = "全局布防";
		}else if (str_cid_event =="1456") {
			str_cid_event_temp = "半布防";
		}else if (str_cid_event =="1301") {
			str_cid_event_temp = "市电掉电";
		}else if (str_cid_event =="1302") {
			str_cid_event_temp = "备用电池低电";
		}else if (str_cid_event =="3301") {
			str_cid_event_temp = "市电掉电恢复";
		}else if (str_cid_event =="3302") {
			str_cid_event_temp = "备用电池低电恢复";
		}
		if (str_cid_defence_area_number2 == "0") {
			str_cid_defence_area_number2 = "主机";
		}else{
			str_cid_defence_area_number2 = str_cid_defence_area_number2 + "号防区";
		}
	}else{
		if (str_cid_event =="1110") {
//			str_cid_event_temp = "Fire" + string(" Zone No.:") + str_cid_defence_area_number_two;
			str_cid_event_temp = "Fire" + string(" Zone No.:") + str_cid_defence_area_number2;
		}else if (str_cid_event =="1131") {
//			str_cid_event_temp = "Perimeter" + string(" Zone No.:") + str_cid_defence_area_number_two;
			str_cid_event_temp = "Perimeter" + string(" Zone No.:") + str_cid_defence_area_number2;
		}else if (str_cid_event =="1120") {
            int i_controller_source = i_cid_defence_area_number;
            if((i_controller_source >= 1) && (i_controller_source <= 97)){
//                str_cid_event_temp = "Emergency" + string(" Zone No.:") + str_cid_defence_area_number_two;
                str_cid_event_temp = "Help    By User:Remote Control" + string(":") + str_cid_defence_area_number_remote;
            }else if(i_controller_source == 98){
//            str_value_returnString = static_var.str_center_transfer;
            }else if(i_controller_source == 99){
//            str_value_returnString = static_var.str_center_standard;
            }else if((i_controller_source >= 100) && (i_controller_source <= 199)){
                str_cid_event_temp = "Help" + string("    By User:") + str_cid_defence_area_number.substr(1,2);
            }else if((i_controller_source >= 200) && (i_controller_source <= 255)){
//            str_value_returnString = static_var.str_wechat + ":" + str_controller_source;
            }else{
//                str_cid_event_temp = "Help" + string(" Zone No.:") + str_cid_defence_area_number2;
                str_cid_event_temp = "Help" + string(" Zone No.:") + str_cid_defence_area_number_two;
            }
//			str_cid_event_temp = "Emergency" + string(" Zone No.:") + str_cid_defence_area_number;
		}else if (str_cid_event =="1130") {
//			str_cid_event_temp = "Burglar" + string(" Zone No.:") + str_cid_defence_area_number_two;
			str_cid_event_temp = "Burglar" + string(" Zone No.:") + str_cid_defence_area_number2;
		}else if (str_cid_event =="1121") {

            int i_controller_source = i_cid_defence_area_number;
            if((i_controller_source >= 1) && (i_controller_source <= 97)){
//                str_cid_event_temp = "Help" + string(" Zone No.:") + str_cid_defence_area_number_two;
                str_cid_event_temp = "Help" + string(" Zone No.:") + str_cid_defence_area_number2;
            }else if(i_controller_source == 98){
//            str_value_returnString = static_var.str_center_transfer;
            }else if(i_controller_source == 99){
//            str_value_returnString = static_var.str_center_standard;
            }else if((i_controller_source >= 100) && (i_controller_source <= 199)){
                str_cid_event_temp = "Help" + string("    By User:") + str_cid_defence_area_number.substr(1,2);
            }else if((i_controller_source >= 200) && (i_controller_source <= 255)){
//            str_value_returnString = static_var.str_wechat + ":" + str_controller_source;
            }else{
//                str_cid_event_temp = "Help" + string(" Zone No.:") + str_cid_defence_area_number_two;
                str_cid_event_temp = "Help" + string(" Zone No.:") + str_cid_defence_area_number2;
            }
		}else if (str_cid_event =="1151") {
//			str_cid_event_temp = "Gas" + string(" Zone No.:") + str_cid_defence_area_number_two;
			str_cid_event_temp = "Gas" + string(" Zone No.:") + str_cid_defence_area_number2;
		}else if (str_cid_event =="1113") {
//			str_cid_event_temp = "Water" + string(" Zone No.:") + str_cid_defence_area_number_two;
			str_cid_event_temp = "Water" + string(" Zone No.:") + str_cid_defence_area_number2;
		}else if (str_cid_event =="1380") {
			str_cid_event_temp = "Abnormal Detector";
		}else if (str_cid_event =="1384") {
			str_cid_event_temp = "Low Battery";
		}else if (str_cid_event =="1383") {
			str_cid_event_temp = "Tamper";
		}else if (str_cid_event =="1110") {
			str_cid_event_temp = "Medical";
		}else if (str_cid_event =="1400") {
			str_cid_event_temp = "Disarm";
		}else if (str_cid_event =="3400") {
//			str_cid_event_temp = "All Arm";
			str_cid_event_temp = "Arm";
		}else if (str_cid_event =="1456") {
			str_cid_event_temp = "Part Arm";
		}else if (str_cid_event =="1301") {
			str_cid_event_temp = "Electric City Low Battery";
		}else if (str_cid_event =="1302") {
			str_cid_event_temp = "Spare battery Low Battery";
		}else if (str_cid_event =="3301") {
			str_cid_event_temp = "Electric City Low Battery Restore";
		}else if (str_cid_event =="3302") {
			str_cid_event_temp = "Spare battery Low Battery Restore";
		}
		if (str_cid_defence_area_number2 == "0") {
			str_cid_defence_area_number2 = "Alarm Panel";
		}else{
//			str_cid_defence_area_number2 = "Zone No." + str_cid_defence_area_number2;
//			str_cid_defence_area_number2 = "Zone No." + str_cid_defence_area_number_two;
			str_cid_defence_area_number2 = "Zone No." + str_cid_defence_area_number2;
		}
	}

    printf("cid_to_chinese_or_english_cid,str_cid_event_temp=%s\n",str_cid_event_temp.c_str());



    if ((str_cid_event =="1400") || (str_cid_event =="3400") || (str_cid_event =="1456")){
        int i_controller_source = i_cid_defence_area_number;
        printf("cid_to_chinese_or_english_cid,i_controller_source=%d\n",i_controller_source);
        if((i_controller_source >= 1) && (i_controller_source <= 97)){
            str_value_returnString = "    By User:Remote Control" + string(":") + str_cid_defence_area_number_remote;
        }else if(i_controller_source == 98){
//            str_value_returnString = static_var.str_center_transfer;
        }else if(i_controller_source == 99){
//            str_value_returnString = static_var.str_center_standard;
        }else if((i_controller_source >= 100) && (i_controller_source <= 199)){
            str_value_returnString ="    By User:" + str_cid_defence_area_number.substr(1,2);
//			str_value_returnString = "APP:" + static_var.str_last_two_numbers + str_controller_source.substring(1, 3);
//			str_value_returnString = "APP:" + static_var.str_last_two_numbers + static_var.phone_acct_static_username;
//			str_value_returnString = "APP";
        }else if((i_controller_source >= 200) && (i_controller_source <= 255)){
//            str_value_returnString = static_var.str_wechat + ":" + str_controller_source;
        }
    }else{
        str_value_returnString = "";
    }

    printf("cid_to_chinese_or_english_cid,str_value_returnString=%s\n",str_value_returnString.c_str());

	//string str_temp =
//	str_cid_chinese_or_english = str_cid_event_temp + "," + str_cid_defence_area_number2 + "  " + str_cid;
	str_cid_chinese_or_english = str_cid_event_temp + str_value_returnString;

}
void person::traversing_phone_map_language()
{
	if (Cstatic_var::map_phone_language.empty()){
		//printf("traversing_phone_map_language，，，,m_count_map_phone=%d\n",0);
		return;
	}
	if (1 == 1)
	{
		lock_guard<mutex> guard(std::mutex mutex_map_language);
		int m_count_map_phone = Cstatic_var::map_phone_language.size();
		//printf("traversing_phone_map_language,m_count_map_phone=%d\n",m_count_map_phone);
		//cout<<"test_fun4,m_count_map_phone="<<m_count_map_phone<<endl;
		map<string,shared_ptr<Cmachine_info_language>>::iterator it_temp22=Cstatic_var::map_phone_language.begin();
		
		for (; it_temp22!=Cstatic_var::map_phone_language.end(); ++it_temp22)
		{
			//printf("traversing_phone_map_language,phone_device_tocken=%s\n",it_temp22->first.c_str());
			
			
			shared_ptr<Cmachine_info_language> plist_temp22 = it_temp22->second;
//			printf("traversing_phone_map_language,phone_account=%s\n",plist_temp22->phone_account.c_str());
//			printf("traversing_phone_map_language,machine_account=%s\n",plist_temp22->machine_account.c_str());
//			printf("traversing_phone_map_language,language=%s\n",plist_temp22->language.c_str());
			
			
			
			
		}
	}
	
}
void person::traversing_phone_map()
{
	if (Cstatic_var::map_phone.empty()) {
		printf("traversing_phone_map，，，,m_count_map_phone=%d\n",0);
		return;
	}
	if (1)
	{
		lock_guard<mutex> guard(std::mutex mutex_map_phone);
		int m_count_map_phone = Cstatic_var::map_phone.size();
		//printf("traversing_phone_map,m_count_map_phone=%d\n",m_count_map_phone);
	
		map<string,shared_ptr<Cmachine_info>>::iterator it_temp22=Cstatic_var::map_phone.begin();
		
		for (; it_temp22!=Cstatic_var::map_phone.end(); ++it_temp22)
		{
			//printf("traversing_phone_map,phone_device_tocken=%s\n",it_temp22->first.c_str());
			
			
			shared_ptr<Cmachine_info> plist_temp22 = it_temp22->second;
//			printf("traversing_phone_map,phone_account=%s\n",plist_temp22->phone_account.c_str());
//			printf("traversing_phone_map,machine_account=%s\n",plist_temp22->machine_account.c_str());
//			printf("traversing_phone_map,badge_identification=%s\n",plist_temp22->badge_identification.c_str());
			
			
			
			
		}
	}
	
}




	


