//
//  csv.cpp
//  test_map
//
//  Created by wangyuhong2267 on 17/3/14.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#include "csv.hpp"
#include "static_var.hpp"
csv::csv ()
{
	u_first = 0;
	
}
csv::~csv(){
	
}

csv* csv::p_inst = NULL;




csv * csv::get_instance()
{
	if(p_inst == NULL)
	{
		p_inst = new csv();
	}
	return p_inst;
}
void csv::write_phone(string str){
	//printf("csv::write......\n");
	string str1 = "";
	if (u_first == 0) {
		str1 = str;
		u_first = 1;
	}else {
		str1 = "\n" + str;
	}
	
	outfile_phone<<str1;
	
}
void csv::write_phone_language(string str){
	//printf("csv::write......\n");
	string str1 = "";
	if (u_first == 0) {
		str1 = str;
		u_first = 1;
	}else {
		str1 = "\n" + str;
	}
	
	outfile_phone<<str1;
	
}
void csv::write_machine(string str){
	//printf("csv::write......\n");
	string str1 = "";
	if (u_first == 0) {
		str1 = str;
		u_first = 1;
	}else {
		str1 = "\n" + str;
	}
	
	outfile_machine<<str1;
	
}
void csv::read_phone()
{
	int count = 0;
	string value;
	string str_device_token = "";
	string str_acct_machine = "";
	string str_acct_phone = "";
	string str_badge_identification = "";
	
	while(infile.good()){
		//.csv文件用","作为分隔符
		//getline(infile,value,',');
		getline(infile,value);
		//printf("csv::read_phone,count=%d\n",count);
		count++;
		//cout<<value<<endl;
		get_str_phone_csv(value,str_device_token,str_acct_machine,str_acct_phone,str_badge_identification);
//		printf("read_phone,str_device_token=%s\n",str_device_token.c_str());
//		printf("read_phone,str_acct_machine=%s\n",str_acct_machine.c_str());
//		printf("read_phone,str_acct_phone=%s\n",str_acct_phone.c_str());
//		printf("read_phone,str_badge_identification=%s\n",str_badge_identification.c_str());
		
		Cstatic_var::p_static_person->insert_phone_map(str_device_token,str_acct_phone,str_acct_machine,str_badge_identification);
	}

}

void csv::read_phone_language()
{
	int count = 0;
	string value;
	string str_device_token = "";
	string str_acct_machine = "";
	string str_acct_phone = "";
	string str_language = "";
	
	while(infile.good()){
		//.csv文件用","作为分隔符
		//getline(infile,value,',');
		getline(infile,value);
		//printf("csv::read_phone,count=%d\n",count);
		count++;
		//cout<<value<<endl;
		get_str_phone_csv_language(value,str_device_token,str_acct_machine,str_acct_phone,str_language);
//		printf("read_phone_language,str_device_token=%s\n",str_device_token.c_str());
//		printf("read_phone_language,str_acct_machine=%s\n",str_acct_machine.c_str());
//		printf("read_phone_language,str_acct_phone=%s\n",str_acct_phone.c_str());
//		printf("read_phone_language,str_language=%s\n",str_language.c_str());

		Cstatic_var::p_static_person->insert_phone_map_language(str_device_token,str_acct_phone,str_acct_machine,str_language);
	}
	
}

void csv::read_machine()
{
	int count = 0;
	string value;
	string str_device_token = "";
	string str_acct_machine = "";
	string str_acct_phone = "";

	
	while(infile.good()){
		//.csv文件用","作为分隔符
		//getline(infile,value,',');
		getline(infile,value);
		//printf("read_machine,count=%d\n",count);
		count++;
		//cout<<value<<endl;
		int index_comma1 = value.find(",");
		int index_comma2 = value.find(",",index_comma1 + 1);
		//printf("read_machine,index_comma1=%d\n",index_comma1);
		//printf("read_machine,index_comma2=%d\n",index_comma2);
		str_acct_machine = value.substr(0,(index_comma1));
		string str_nums_list = value.substr((index_comma1 + 1),(index_comma2 - index_comma1 - 1));
		int i_nums_list = std::atoi(str_nums_list.c_str());
		//printf("read_machine,str_acct_machine=%s\n",str_acct_machine.c_str());
		//printf("read_machine,str_nums_list=%s\n",str_nums_list.c_str());
		//printf("read_machine,i_nums_list=%d\n",i_nums_list);
		//////////////////////////////////////////////////////////////////
		int length = value.size();
		string str_list = value.substr((index_comma2 + 1),(length - index_comma2 + 1));
		//printf("read_machine,str_list=%s\n",str_list.c_str());
		for (int i = 0; i < i_nums_list; i++) {
			index_comma1 = str_list.find(",");
			index_comma2 = str_list.find(",",index_comma1 + 1);
			int index_comma3 = str_list.find(",",index_comma2 + 1);
			int index_comma4 = str_list.find(",",index_comma3 + 1);
			str_acct_phone = str_list.substr(0,(index_comma1));
			str_device_token = str_list.substr((index_comma1 + 1),(index_comma2 - index_comma1 - 1));
			
			//printf("read_machine,str_acct_machine=%s\n",str_acct_machine.c_str());
			//printf("read_machine,str_acct_phone=%s\n",str_acct_phone.c_str());
			//printf("read_machine,str_device_token=%s\n",str_device_token.c_str());

			Cstatic_var::p_static_person->insert_machine_map(str_acct_machine,str_device_token,str_acct_phone);
			int length = str_list.size();
			str_list = str_list.substr((index_comma2 + 1),(length - index_comma2 + 1));
			//printf("read_machine,str_list=%s\n",str_list.c_str());
		}
//		get_str_phone_csv(value,str_device_token,str_acct_machine,str_acct_phone);
//		printf("csv::read,str_device_token=%s",str_device_token.c_str());
//		printf("csv::read,str_acct_machine=%s",str_acct_machine.c_str());
//		printf("csv::read,str_acct_phone=%s",str_acct_phone.c_str());
//		Cstatic_var::p_static_person->insert_phone_map(str_device_token,str_acct_phone,str_acct_machine);
	}
	
}
void csv::createfile_phone (string str_filename)
{
	u_first = 0;
	outfile_phone.open(str_filename.c_str(),ios::out);
}
void csv::createfile_machine(string str_filename)
{
	u_first = 0;
	outfile_machine.open(str_filename.c_str(),ios::out);
}
void csv::createfile_read (string str_filename)
{
	u_first = 0;
	infile.open(str_filename.c_str(),ios::in);
}
void csv::get_str_phone_csv(string str_value,string &str_device_token,string &str_acct_machine,string &str_acct_phone,string &badge_identification)
{
//	int len_value = str_value.length();
//	int index_first = str_value.find_first_of(",");
//	//printf("get_str_phone_csv,index_first=%d",index_first);
//	int index_last = str_value.find_last_of(",");
//	//printf("get_str_phone_csv,index_last=%d",index_last);
//	str_device_token = str_value.substr(0,index_first);
//	str_acct_machine = str_value.substr((index_first + 1),(index_last - index_first - 1));
//	str_acct_phone = str_value.substr((index_last + 1),(len_value - index_last + 1));
	
	
	
		int index_comma1 = str_value.find(",");
		int index_comma2 = str_value.find(",",index_comma1 + 1);
		int index_comma3 = str_value.find(",",index_comma2 + 1);
		int index_comma4 = str_value.find(",",index_comma3 + 1);
		str_device_token = str_value.substr(0,(index_comma1));
		str_acct_machine = str_value.substr((index_comma1 + 1),(index_comma2 - index_comma1 - 1));
		str_acct_phone = str_value.substr((index_comma2 + 1),(index_comma3 - index_comma2 - 1));
		badge_identification = str_value.substr((index_comma3 + 1),(index_comma4 - index_comma3 - 1));
//		printf("get_str_phone_csv,str_device_token=%s\n",str_device_token.c_str());
//		printf("get_str_phone_csv,str_acct_machine=%s\n",str_acct_machine.c_str());
//		printf("get_str_phone_csv,str_acct_phone=%s\n",str_acct_phone.c_str());
//		printf("get_str_phone_csv,badge_identification=%s\n",badge_identification.c_str());

	
	
}


void csv::get_str_phone_csv_language(string str_value,string &str_device_token,string &str_acct_machine,string &str_acct_phone,string &str_language)
{

	
	
	
	int index_comma1 = str_value.find(",");
	int index_comma2 = str_value.find(",",index_comma1 + 1);
	int index_comma3 = str_value.find(",",index_comma2 + 1);
	int index_comma4 = str_value.find(",",index_comma3 + 1);
	str_device_token = str_value.substr(0,(index_comma1));
	str_acct_machine = str_value.substr((index_comma1 + 1),(index_comma2 - index_comma1 - 1));
	str_acct_phone = str_value.substr((index_comma2 + 1),(index_comma3 - index_comma2 - 1));
	str_language = str_value.substr((index_comma3 + 1),(index_comma4 - index_comma3 - 1));
//	printf("get_str_phone_csv_language,str_device_token=%s\n",str_device_token.c_str());
//	printf("get_str_phone_csv_language,str_acct_machine=%s\n",str_acct_machine.c_str());
//	printf("get_str_phone_csv_language,str_acct_phone=%s\n",str_acct_phone.c_str());
//	printf("get_str_phone_csv_language,str_language=%s\n",str_language.c_str());
	
	
	
}


