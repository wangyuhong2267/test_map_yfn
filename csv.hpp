//
//  csv.hpp
//  test_map
//
//  Created by wangyuhong2267 on 17/3/14.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#ifndef csv_hpp
#define csv_hpp

#include <stdio.h>
#include "const.h"
class csv
{
public:
	unsigned long u_first;
	ofstream outfile_phone;
	ofstream outfile_machine;
	ifstream infile;
	static csv* p_inst;
	static csv *get_instance();
	
	csv ();
	~csv();
	void write_phone(string str);
	void write_phone_language(string str);
	void write_machine(string str);

	void read_phone();
	void read_phone_language();
	void read_machine();
	void createfile_phone (string str_filename);
	void createfile_machine (string str_filename);
	void createfile_read (string str_filename);
	
	
	void get_str_phone_csv(string str_value,string &str_device_token,string &str_acct_machine,string &str_acct_phone,string &badge_identification);
	void get_str_phone_csv_language(string str_value,string &str_device_token,string &str_acct_machine,string &str_acct_phone,string &str_language);
	
	
};
#endif /* csv_hpp */
