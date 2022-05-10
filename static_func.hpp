//
//  static_func.hpp
//  test_map
//
//  Created by wangyuhong2267 on 17/3/1.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#ifndef static_func_hpp
#define static_func_hpp

/*  And data-independent classes  */

#include <stdio.h>
#include "const.h"
//#include "static_var.hpp"
class Cstatic_func
{
public:
	
	
	
	
	Cstatic_func();
	virtual ~Cstatic_func();
	
	static Cstatic_func* p_inst;
	static Cstatic_func *get_instance();
	void test_print();
	
	
	int EpollConfig(int listenfd, bool enable_et);
	void setnonblocking2(int sock);
	int setnonblocking( int fd );
	
	void get_time(char *buf_out);
	void get_time_log(char *buf_out);
	unsigned int ascll_to_hex(unsigned char asc);
	void printf_cmd_client(unsigned char *buf,unsigned int len);
	void printf_cmd_client_hex(unsigned char *buf,unsigned int len);
	void printf_cmd_client_asc(unsigned char *buf,unsigned int len);
	////////////////////////////////////////////////////////////////////
	

	unsigned int handle_len_standard(unsigned char *buf,int a,int b);
	bool exception_handle_cmd_format(const char *note,unsigned int type,unsigned int para1,unsigned int para2);
	bool exception_handle_cmd_format_machine(unsigned char *buf,const char *note,unsigned int type,unsigned int para1,unsigned int para2,unsigned int len_quote);
	bool exception_handle_cmd_format_detail(unsigned char *cmd,unsigned int type);
	
	
	
	bool exception_center_conn_number(unsigned int conn_number);
	bool exception_machine_conn_number(unsigned int conn_number,const char *str_val,unsigned char *cmd);
	bool exception_phone_conn_number(unsigned int conn_number,const char *str_val);
	bool exception_phone_conn_number_0b_0b(unsigned int conn_number,const char *str_val);
	bool exception_handle_machine_online(unsigned int conn_number,unsigned int type);
	bool crc_check_pri(unsigned char *cmd,int para);
	bool crc_check_pri_machine_asc(unsigned char *cmd,int para,unsigned int len_total_real);
	bool crc_check_std(unsigned char *cmd,int para);
	bool crc_check_std_machine(unsigned char *cmd,int para,unsigned int len_total_real);
	bool std_format_check(unsigned char *cmd);
	
	int find_place(char *buf,char ch,int len);
	int find_place_L(char *buf,char ch,int len);
	int find_place_second(char *buf,char ch,int len);
	
	unsigned int calcCRC_buf(unsigned char *buf,int len);
	void NumToHex(int Num,char *lpHex);
	void NumToHex_4(int Num,char *lpHex);
	unsigned int calcCRC(unsigned CRC, int ch);
	unsigned int calcCRC2(unsigned int CRC, int ch) ;
	//////////////////////////////////////////////////////////////////////
	
	
	
	int create_ip_standard_event(unsigned char * buf, const char *acct_id, const char * acct_seq,
										const char * acct_Rrcvr, const char * acct_Lpref, const char * acct_machine);
	int create_ip_standard_event_center(unsigned char * buf, const char *acct_id, const char * acct_seq,
											   const char * acct_Rrcvr, const char * acct_Lpref, const char * acct_machine);
	
	void create_pricmd_public_29_wifi(unsigned char *buf,int len_toacct,int len_pri,const char *acct_machine,const char *psw,
											 const char *acct_phone,int level,int dest_type);
	
	void create_pricmd_public_29(unsigned char *buf,int len_toacct,int len_pri,const char *acct_machine,const char *psw,
										const char *acct_phone,int level);
	int level_to_wifi(int level,int dest_type);
	void level_transfer_to_wifi(int dest_type,unsigned char *cmd);
	void NumCStringToHexByte(char *phone, char *buf);
	void NumCStringToHexByte_8(char *phone, char *buf);
	char * HexByteToNumString(const char *hex, unsigned char len);
	bool exception_len_ip_event(unsigned int len_ip_event,int type,const char *str);
	
};

#endif /* static_func_hpp */
