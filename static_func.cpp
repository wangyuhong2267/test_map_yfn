//
//  static_func.cpp
//  test_map
//
//  Created by wangyuhong2267 on 17/3/1.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#include "static_func.hpp"

Cstatic_func* Cstatic_func::p_inst = NULL;




Cstatic_func * Cstatic_func::get_instance()
{
	if(p_inst == NULL)
	{
		p_inst = new Cstatic_func();
	}
	return p_inst;
}


void Cstatic_func::test_print()
{
	cout<<"Cstatic_func,terst_print......"<<endl;
}


Cstatic_func::Cstatic_func()
{
	
}

Cstatic_func::~Cstatic_func()
{
	
}

int Cstatic_func::EpollConfig(int listenfd, bool enable_et)
{
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	///////////////////////////////////////////////
	int epfd2_temp;
	
	struct epoll_event ev;
	
	epfd2_temp=epoll_create(MAX_FDS);
	
	
	ev.data.fd=listenfd;
	
	ev.events=EPOLLIN;
	if( enable_et )
	{
		ev.events |= EPOLLET;
	}
	
	epoll_ctl(epfd2_temp,EPOLL_CTL_ADD,listenfd,&ev);
	
	setnonblocking(listenfd);
	return (epfd2_temp);
	
}

void Cstatic_func::setnonblocking2(int sock)
{
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	
	int opts;
	opts=fcntl(sock,F_GETFL);
	if(opts<0)
	{
		perror("fcntl(sock,GETFL)");
	}
	opts = opts|O_NONBLOCK;
	if(fcntl(sock,F_SETFL,opts)<0)
	{
		perror("fcntl(sock,SETFL,opts)");
	}
}

int Cstatic_func::setnonblocking( int fd )
{
	int old_option = fcntl( fd, F_GETFL );
	int new_option = old_option | O_NONBLOCK;
	fcntl( fd, F_SETFL, new_option );
	return old_option;
}
void Cstatic_func::printf_cmd_client_asc(unsigned char *buf,unsigned int len)
{
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	///////////////////////////////////////////////
	//unsigned int mm = 0;
	//unsigned int m = 0;
	char str_temp[1500];
	memset(str_temp,0,sizeof(str_temp));
	memcpy(str_temp, buf, len);
	printf("printf_cmd_client_asc,str_temp2=%s\n",str_temp);
//	unsigned int chushu = (len)/len;
//	unsigned int yushu = (len)%len;
//
//	for(mm =0; mm < chushu; mm++)
//	{
//		char str_temp2[1500];
//		memset(str_temp2,0,sizeof(str_temp2));
//		memcpy(str_temp2," ",1);
//		for(m = 0;m < len;m++)
//		{
//			sprintf(str_temp,"%c",  buf[mm*len + m]);
//			strcat(&str_temp2[1 + m],str_temp);
//		}
//
//		
//	}
//	char str_temp2[1000];
//	memset(str_temp2,0,sizeof(str_temp2));
//	memcpy(str_temp2," ",1);
//	for(m = 0;m < yushu;m++)
//	{
//		sprintf(str_temp,"%c",  buf[chushu*len + m]);
//		strcat(&str_temp2[1],str_temp);
//	}
//	printf("%s ",  str_temp2);
//	printf("printf_cmd_client_asc,len=%d\n",len);
//	printf("printf_cmd_client_asc,str_temp2=%s\n",str_temp2);
	//////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
}
void Cstatic_func::printf_cmd_client_hex(unsigned char *buf,unsigned int len)
{
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	///////////////////////////////////////////////
	unsigned int mm = 0;
	unsigned int m = 0;
	char str_temp[1024];
	memset(str_temp,0,sizeof(str_temp));
	//unsigned int chushu = (nLen - 40)/PRINTF_LINE_BYTES;
	//unsigned int yushu = (nLen - 40)%PRINTF_LINE_BYTES;
	unsigned int chushu = (len)/PRINTF_LINE_BYTES;
	unsigned int yushu = (len)%PRINTF_LINE_BYTES;
	//printf("chushu=%d,yushu=%d\n",chushu,yushu);
	for(mm =0; mm < chushu; mm++)
	{
		char str_temp2[1000];
		memset(str_temp2,0,sizeof(str_temp2));
		for(m = 0;m < PRINTF_LINE_BYTES;m++)
		{
			sprintf(str_temp," 0x%02hhX",  buf[mm*PRINTF_LINE_BYTES + m]);
			strcat(str_temp2,str_temp);
		}
		printf(" %s ",  str_temp2);
		printf("\n");
	}
	char str_temp2[1000];
	memset(str_temp2,0,sizeof(str_temp2));
	for(m = 0;m < yushu;m++)
	{
		sprintf(str_temp," 0x%02hhX",  buf[chushu*PRINTF_LINE_BYTES + m]);
		strcat(str_temp2,str_temp);
	}
	printf(" %s ",  str_temp2);
	printf("\n");
}
void Cstatic_func::printf_cmd_client(unsigned char *buf,unsigned int len)
{
	///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
	printf("......function_name:%s\n",__func__);
#else
#endif
	/////////////////////////////////////////////////////////////////
	int len_std_a = 0;
	int len_std_b = 0;
	if(buf[7] < 58)
	{
		len_std_a = buf[7] - 48;
	}
	else if((buf[7] >= 65) && (buf[7] <= 70))
	{
		len_std_a = buf[7] - 55;
	}
	if(buf[8] < 58)
	{
		len_std_b = buf[8] - 48;
	}
	else if((buf[8] >= 65) && (buf[7] <= 70))
	{
		len_std_b = buf[8] - 55;
	}
	unsigned int len_standard = len_std_a * 16 + len_std_b;
	//unsigned int len_pri = buf[len_standard + 10] * 256 + buf[len_standard + 10 + 1];
	//unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;
//	printf("printf_cmd_client,len_standard=%d\n",len_standard);
//	printf("printf_cmd_client,len_pri=%d\n",len_pri);
//	printf("printf_cmd_client,len_total=%d\n",len_total);
	printf_cmd_client_asc(&buf[1],len_standard + 10);
	////////////////////////////////////////////////////////////////
	char buf_pri[1024];
	memset(buf_pri,0,sizeof(buf_pri));
	memcpy(buf_pri,&buf[len_standard + 10],len - len_standard - 10);
	unsigned int mm = 0;
	unsigned int m = 0;
	char str_temp[256];
	unsigned int chushu = (len - len_standard - 10)/PRINTF_LINE_BYTES;
	unsigned int yushu = (len - len_standard - 10)%PRINTF_LINE_BYTES;
	//printf("chushu=%d,yushu=%d\n",chushu,yushu);
	for(mm =0; mm < chushu; mm++)
	{
		char str_temp2[1000];
		memset(str_temp2,0,sizeof(str_temp2));
		for(m = 0;m < PRINTF_LINE_BYTES;m++)
		{
			sprintf(str_temp," 0x%02hhX",  buf_pri[mm*PRINTF_LINE_BYTES + m]);
			strcat(str_temp2,str_temp);
		}
		printf(" %s ",  str_temp2);
		printf("\n");
	}
	char str_temp2[1000];
	memset(str_temp2,0,sizeof(str_temp2));
	for(m = 0;m < yushu;m++)
	{
		sprintf(str_temp," 0x%02hhX",  buf_pri[chushu*PRINTF_LINE_BYTES + m]);
		strcat(str_temp2,str_temp);
	}
	printf(" %s ",  str_temp2);
	printf("\n");
	int len_temp = len_standard + PUBLIC_SIZE + 10;
	unsigned int big_class = buf[len_temp];
	unsigned int small_class = buf[len_temp + 1];
	printf("big_class=%02x, small_class=%02x\n",big_class, small_class);
	////////////////////////////////////////////////////
	
}
unsigned int Cstatic_func::handle_len_standard(unsigned char *buf,int a,int b)
{
	int len_std_a = 0;
	int len_std_b = 0;
	
	
	if(buf[a] < 58)
	{
		len_std_a = buf[a] - 48;
	}
	else if((buf[a] >= 65) && (buf[a] <= 70))
	{
		len_std_a = buf[a] - 55;
	}
	if(buf[b] < 58)
	{
		len_std_b = buf[b] - 48;
	}
	else if((buf[b] >= 65) && (buf[b] <= 70))
	{
		len_std_b = buf[b] - 55;
	}
	int len_standard = len_std_a * 16 + len_std_b;
	return len_standard;
	
}
bool Cstatic_func::exception_handle_cmd_format(const char *note,unsigned int type,unsigned int para1,unsigned int para2)
{
	
	
	if(type == 0)
	{
		
		
	}
	else if(type == 1)
	{
		
	}
	else if(type == 2)
	{
		if(para1 > (para2))
		{
			
			//printf("%s, len_standard=%d is out of max %d\n",note,para1,para2);
			
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(type == 3)
	{
		if(para1 > (para2))
		{
			
			printf("%s,len_private=%d is out of max %d\n",note,para1,para2);
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return false;
}




bool Cstatic_func::exception_handle_cmd_format_machine(unsigned char *buf,const char *note,unsigned int type,unsigned int para1,unsigned int para2,unsigned int len_quote)
{
	
	
	if(type == 0)
	{
		
		
	}
	else if(type == 1)
	{
		
	}
	else if(type == 2)
	{
		if(para1 > (para2))
		{
			
			printf("%s,len_standard=%d is out of max %d\n",note,para1,para2);
			//printf_cmd_client_asc(buf,len_quote);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(type == 3)
	{
		if(para1 > (para2))
		{
			
			printf("%s,len_private=%d is out of max %d\n",note,para1,para2);
			//printf_cmd_client_asc(buf,len_quote);
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return false;
}

bool Cstatic_func::exception_handle_cmd_format_detail(unsigned char *cmd,unsigned int type)
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
	
	
	////////////////////////////////////////////////////////////////////
	int len_standard = len_std_a * 16 + len_std_b;
	if((len_standard > MAX_LEN_STD) || (len_standard <= 40))
	{
		printf("exception_handle_cmd_format_detail,MAX_LEN_STD,len_standard=%d\n",len_standard);
		return true;
		
	}
	unsigned int len_pri = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
	if((len_pri > MAX_LEN_PRI) || (len_pri <= 31))
	{
		printf("exception_handle_cmd_format_detail,MAX_LEN_PRI,len_pri=%d\n",len_pri);
		return true;;
	}
	unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;
	//printf("len_standard=%d,len_pri=%d,len_total=%d\n",len_standard,len_pri,len_total);
	int len_temp = len_standard + PUBLIC_SIZE + 10;
	unsigned int big_class = cmd[len_temp];
	unsigned int small_class = cmd[len_temp + 1];
	//printf("big_class=%d,small_class=%d\n",big_class,small_class);
	//////////////////////////////////////////////////////////////////////////////////
	//char *account_number;
	//char *account_number = Cstatic_var::HexByteToNumString((char *)&cmd[len_standard + 12],9);
	//printf("account_number=%s\n",account_number);
	
	int place_quote_sencond = find_place_second((char*)&cmd[0],'\"',len_standard + 10);
	if(place_quote_sencond == -1)
	{
		printf("exception_handle_cmd_format_detail,id_token's sencond quote was not found\n");
		//Cstatic_func::printf_cmd_client((unsigned char*)cmd,len_total);
		
		return true;
	}
	int place_R = find_place((char*)&cmd[0],'R',len_standard + 10);
	if(place_R == -1)
	{
		
		printf("Rrecv was not found!\n");
		//Cstatic_func::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	char buf_id[64];
	memset(buf_id,0,sizeof(buf_id));
	memcpy(buf_id,&cmd[10],place_quote_sencond - 10);
	//printf("buf_id=%s\n",buf_id);
	//	if(0 ==strcmp(buf_id,"NAK")){
	//		//printf("buf_id=%s\n",buf_id);
	//
	//
	//        printf("id is NAK !\n");
	//		Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
	//        return true;
	//
	//	}
	/////////////////////////////////////////////////////////////////////////////////////
	
	int place_L = 0;
	if(0 ==strcmp(buf_id,"NULL")){
		//printf("buf_id=%s\n",buf_id);
		place_L = find_place_L((char*)&cmd[0],'L',len_standard + 10);
		if(place_L == -1)
		{
			
			printf("Lpref was not found!\n");
			//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
			return true;
		}
	}
	else {
		place_L = find_place((char*)&cmd[0],'L',len_standard + 10);
		if(place_L == -1)
		{
			
			printf("Lpref was not found!\n");
			//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
			return true;
		}
		
	}
	int place_well = find_place((char*)&cmd[0],'#',len_standard + 10);
	
	if(place_well == -1)
	{
		
		printf("wellnumber_first was not found!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	int place_bracket_front = find_place((char*)&cmd[0],'[',len_standard + 10);
	
	if(place_bracket_front == -1)
	{
		
		printf("place_bracket_front was not found!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	int place_bracket_back = find_place((char*)&cmd[0],']',len_standard + 10);
	if(place_bracket_back == -1)
	{
		
		printf("place_bracket_back was not found!\n");
		//printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	
	
	
	
	//////////////////////////////////////////////////////////////////////////////////////
	if(cmd[0] != 0x0A)
	{
		
		
		printf("ip standard cmd exception,cmd[0] != 0x0A,big_class=%02x, small_class=%02x\n",big_class, small_class);
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	if(cmd[len_standard + 9] != 0x0d)
	{
		
		printf("place_quote_sencond=%d\n",place_quote_sencond);
		printf("place_R=%d\n",place_R);
		printf("place_L=%d\n",place_L);
		printf("place_well=%d\n",place_well);
		printf("place_bracket_front=%d\n",place_bracket_front);
		printf("place_bracket_back=%d\n",place_bracket_back);
		printf("len_standard + 9=%d\n",len_standard + 9);
		printf("cmd[len_standard + 9]=0x%02hhX is not 0x0d,this package is error!\n",cmd[len_standard +10]);
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	if(cmd[9] != '\"')
	{
		printf("cmd[9]=0x%02hhX is not \"_front,this package is error!\n",cmd[9]);
		return true;
	}
	if((place_quote_sencond < 10) || (place_quote_sencond > place_R)
	   || (place_quote_sencond > place_L) || (place_quote_sencond > place_well)
	   || (place_quote_sencond > place_bracket_front) || (place_quote_sencond > place_bracket_back)
	   || (place_quote_sencond > (len_standard + 9))){
		
		printf("place_quote_sencond=%d\n",place_quote_sencond);
		printf("place_R=%d\n",place_R);
		printf("place_L=%d\n",place_L);
		printf("place_well=%d\n",place_well);
		printf("place_bracket_front=%d\n",place_bracket_front);
		printf("place_bracket_back=%d\n",place_bracket_back);
		printf("len_standard + 9=%d\n",len_standard + 9);
		printf("place_quote_sencond's position is wrong!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	if((place_R < 14) || (place_quote_sencond > place_R)
	   || (place_R > place_L) || (place_R > place_well)
	   || (place_R > place_bracket_front) || (place_R > place_bracket_back)
	   || (place_R > (len_standard + 9))){
		
		printf("Rrecv's position is wrong!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	if((place_L < 20) || (place_quote_sencond > place_L)
	   || (place_R > place_L) || (place_L > place_well)
	   || (place_L > place_bracket_front) || (place_L > place_bracket_back)
	   || (place_L > (len_standard + 9))){
		
		printf("Lpref's position is wrong!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	if((place_well < 26) || (place_quote_sencond > place_well)
	   || (place_R > place_well) || (place_L > place_well)
	   || (place_well > place_bracket_front) || (place_well > place_bracket_back)
	   || (place_well > (len_standard + 9))){
		
		printf("well_number's position is wrong!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	if((place_bracket_front < 28) || (place_quote_sencond > place_bracket_front)
	   || (place_R > place_bracket_front) || (place_L > place_bracket_front)
	   || (place_well > place_bracket_front) || (place_bracket_front > place_bracket_back)
	   || (place_bracket_front > (len_standard + 9))){
		
		printf("place_bracket_front's position is wrong!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	if((place_bracket_back < 29) || (place_quote_sencond > place_bracket_back)
	   || (place_R > place_bracket_back) || (place_L > place_bracket_back)
	   || (place_well > place_bracket_back) || (place_bracket_front > place_bracket_back)
	   || (place_bracket_back > (len_standard + 9))){
		
		printf("place_bracket_back's position is wrong!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	if((place_bracket_front - place_well -1) > 18 ){
		
		printf("acct(well_number's back) is too long!\n");
		//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
		
	}
	if((place_bracket_back - place_bracket_front - 1) > 32 ){
		
		printf("the content in the bracket is too long!\n");
		printf_cmd_client((unsigned char*)cmd,len_total);
		return true;
		
	}
	if(type == 0)
	{
		
		int conn_number = cmd[len_temp + 2] * 65536 + cmd[len_temp + 3] * 256 + cmd[len_temp + 4];
		//printf("dddddddddddd conn_number=%d\n",conn_number);
		//printf("machine's big_class is wrong,big_class=%02x\n",big_class);
		if(!exception_machine_conn_number(conn_number,"exception_handle_cmd_format_detail for machine",(unsigned char*)cmd))
		{
			
			return true;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(!((big_class == 0x02) ||  (big_class == 0x0d) || (big_class == 0x05) || (big_class == 0x0b)))
		{
			
			printf("machine's big_class is wrong,big_class=%02x\n",big_class);
			//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
			return true;
			
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x02)//machine_to_server
		{
			if(small_class > 0x06)
			{
				
				printf("machine's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x0d)//machine_to_center
		{
			if(small_class > 0x01)
			{
				
				printf("machine's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x05)//machine_to_phone
		{
			if(small_class > 0x20)
			{
				
				printf("machine's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		if(big_class == 0x0b)
		{
			if(small_class > 0x20)
			{
				
				printf("machine's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
	}
	else if(type == 1)//phone_cmd_limits
	{
		if(!((big_class == 0x00)
		||  (big_class == 0x04)
		||  (big_class == 0x44)
		|| (big_class == 0x0a)
		|| (big_class == 0x05)
		|| (big_class == 0x01)
		|| (big_class == 0x0e)))
		{
			
			printf("phone's big_class is wrong,big_class=%02x\n",big_class);
			//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
			return true;
			
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x00)//machine_to_server
		{
			if(small_class > 0xff)
			{
				
				printf("phone's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x04)//machine_to_center
		{
			if(small_class > 0x20)
			{
				
				printf("phone's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x0a)//machine_to_phone
		{
			if(small_class > 0x20)
			{
				
				printf("phone's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		if(big_class == 0x0e)//machine_to_server
		{
			if(small_class > 0xff)
			{
				
				printf("phone's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		
	}
	
	else if(type == 2)
	{
		if(!((big_class == 0x06) ||  (big_class == 0x0c) || (big_class == 0x0a)))
		{
			
			printf("center's big_class is wrong,big_class=%02x\n",big_class);
			printf_cmd_client((unsigned char*)cmd,len_total);
			return true;
			
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x06)//machine_to_server
		{
			if(small_class > 0x01)
			{
				
				printf("center's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x0c)//machine_to_center
		{
			if(small_class > 0x03)
			{
				
				printf("center's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		if(big_class == 0x0a)//machine_to_phone
		{
			if(!((small_class == 0x0b) ||  (small_class == 0x0c)))
			{
				
				printf("center's small_class is wrong,big_class=%02x,small_class=%02x\n",big_class,small_class);
				//Cstatic_var::printf_cmd_client((unsigned char*)cmd,len_total);
				return true;
				
			}
			
		}
	}
	else if(type == 3)
	{
		
	}
	
	return false;
}



bool Cstatic_func::exception_machine_conn_number(unsigned int conn_number,const char *str_val,unsigned char *cmd)
{
	
	
	if(conn_number >= MAX_USER_NUMBER_MACHINE)
	{
		printf("error machine conn_number=%d is out of max conn_number,position=%s\n",conn_number,str_val);
		return false;
	}
	else
	{
		return true;
	}
}
bool Cstatic_func::exception_phone_conn_number(unsigned int conn_number,const char *str_val)
{
	if(conn_number >= MAX_USER_NUMBER)
	{
		
		printf("error phone conn_number=%d is out of max conn_number,position=%s\n",conn_number,str_val);
		return false;
	}
	else
	{
		return true;
	}
}
bool Cstatic_func::exception_phone_conn_number_0b_0b(unsigned int conn_number,const char *str_val)
{
	if(conn_number >= MAX_USER_NUMBER)
	{
		
		//printf("error phone conn_number=%d is out of max conn_number,position=%s\n",conn_number,str_val);
		return false;
	}
	else
	{
		return true;
	}
}

bool Cstatic_func::exception_center_conn_number(unsigned int conn_number)
{
	if(conn_number == IDLEIDLEIDLE)
	{
		return false;
	}
	
	else if((conn_number >= MAX_USER_NUMBER_ALARM_CENTER))
	{
		printf("error center conn_number=%d is out of max conn_number\n",conn_number);
		return false;
	}
	
	else
	{
		return true;
	}
}




bool Cstatic_func::crc_check_std(unsigned char *cmd,int para)
{
	unsigned char buf[5];
	memset(buf,0,sizeof(buf));
	char buf_id[256];
	memset(buf_id,0,sizeof(buf_id));
	memcpy(buf_id,&cmd[9],9);
	//printf("buf_id=%s\n",buf_id);
	/////////////////////////////////////////////////////////////////
	unsigned int len_std_a = 0;
	unsigned int len_std_b = 0;
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
	//printf("len_standard=%d,len_std_a=%d,len_std_b=%d",len_standard,len_std_a,len_std_b);
	unsigned int crc_value = calcCRC_buf(&cmd[9],len_standard);
	Cstatic_func::NumToHex_4(crc_value,(char *)buf);
	//printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",cmd[1],cmd[2],cmd[3],cmd[4]);
	//printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",buf[0],buf[1],buf[2],buf[3]);
	unsigned int len_bigclass = len_standard + PUBLIC_SIZE + 10;
	unsigned int big_class = cmd[len_bigclass];
	unsigned int small_class = cmd[len_bigclass + 1];
	unsigned int len_temp_crc = len_standard + PUBLIC_SIZE + 10;
	unsigned int conn_number = cmd[len_temp_crc + 2] * 65536 + cmd[len_temp_crc + 3] * 256 + cmd[len_temp_crc + 4];
	//printf("machine conn_number=%d\n",conn_number);
	if((buf[0] == cmd[1]) && (buf[1] == cmd[2]) && (buf[2] == cmd[3]) && (buf[3] == cmd[4]))
	{
		if(para == 0)
		{
			//printf("crc check std right... big_class=%d,small_class=%d,conn_number_machine=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 1)
		{
			//printf("crc check std right... big_class=%d,small_class=%d,conn_number_phone=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 2)
		{
			//printf("crc check std right... big_class=%d,small_class=%d,conn_number_center=%d\n",big_class,small_class,conn_number);
		}
		
		return true;
	}
	else
	{
		//Cstatic_func::printf_cmd_client(cmd,len_total);
		if(para == 0)
		{
			printf("crc check std error... big_class=%d,small_class=%d,conn_number_machine=%d\n",big_class,small_class,conn_number);
			printf_cmd_client((unsigned char*)cmd,len_total);
			
		}
		else if(para == 1)
		{
			printf("crc check std error... big_class=%d,small_class=%d,conn_number_phone=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 2)
		{
			printf("crc check std error... big_class=%d,small_class=%d,conn_number_center=%d\n",big_class,small_class,conn_number);
		}
		return false;
	}
	
}

bool Cstatic_func::crc_check_std_machine(unsigned char *cmd,int para,unsigned int len_total_real)
{
	unsigned char buf[5];
	memset(buf,0,sizeof(buf));
	char buf_id[256];
	memset(buf_id,0,sizeof(buf_id));
	memcpy(buf_id,&cmd[9],9);
	//printf("buf_id=%s\n",buf_id);
	/////////////////////////////////////////////////////////////////
	unsigned int len_std_a = 0;
	unsigned int len_std_b = 0;
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
	//unsigned int len_pri = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
	//unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;
	//printf("len_standard=%d,len_std_a=%d,len_std_b=%d",len_standard,len_std_a,len_std_b);
	unsigned int crc_value = Cstatic_func::calcCRC_buf(&cmd[9],len_standard);
	NumToHex_4(crc_value,(char *)buf);
	//printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",cmd[1],cmd[2],cmd[3],cmd[4]);
	//printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",buf[0],buf[1],buf[2],buf[3]);
	//	unsigned int len_bigclass = len_standard + PUBLIC_SIZE + 10;
	//	unsigned int big_class = cmd[len_bigclass];
	//	unsigned int small_class = cmd[len_bigclass + 1];
	//	unsigned int len_temp_crc = len_standard + PUBLIC_SIZE + 10;
	//	unsigned int conn_number = cmd[len_temp_crc + 2] * 65536 + cmd[len_temp_crc + 3] * 256 + cmd[len_temp_crc + 4];
	//printf("machine conn_number=%d\n",conn_number);
	if((buf[0] == cmd[1]) && (buf[1] == cmd[2]) && (buf[2] == cmd[3]) && (buf[3] == cmd[4]))
	{
		if(para == 0)
		{
			//printf("crc check std right... big_class=%d,small_class=%d,conn_number_machine=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 1)
		{
			//printf("crc check std right... big_class=%d,small_class=%d,conn_number_phone=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 2)
		{
			//printf("crc check std right... big_class=%d,small_class=%d,conn_number_center=%d\n",big_class,small_class,conn_number);
		}
		
		return true;
	}
	else
	{
		
		if(para == 0)
		{
			printf("machine crc check std error...... \n");
			printf_cmd_client_asc(cmd,len_total_real);
			
		}
		else if(para == 1)
		{
			printf("machine crc check std error...... \n");
		}
		else if(para == 2)
		{
			printf("machine crc check std error...... \n");
		}
		return false;
	}
	
}


bool Cstatic_func::crc_check_pri(unsigned char *cmd,int para)
{
	unsigned char buf[5];
	memset(buf,0,sizeof(buf));
	char buf_id[256];
	memset(buf_id,0,sizeof(buf_id));
	memcpy(buf_id,&cmd[9],9);
	//printf("buf_id=%s\n",buf_id);
	/////////////////////////////////////////////////////////////////
	unsigned int len_std_a = 0;
	unsigned int len_std_b = 0;
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
	//printf("len_standard=%d,len_std_a=%d,len_std_b=%d",len_standard,len_std_a,len_std_b);
	///////////////////////////////////////////////////////////////////////////////////
	unsigned int len_pri = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
	//printf("len_pri = %d\n",len_pri);
	unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;
	//printf("len_total = %d\n",len_total);
	
	unsigned int len_temp = len_standard + 10 + 2;
	//printf("len_temp = %d\n",len_temp);
	unsigned int crc_value_private = calcCRC_buf(&cmd[len_temp],len_pri);
	//printf("crc_value_private = %d\n",crc_value_private);
	NumToHex_4(crc_value_private,(char *)buf);
	//printf("cmd[len_temp] = 0x%02hhX\n",cmd[len_temp]);
	//printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",buf[0],buf[1],buf[2],buf[3]);
	//printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",cmd[len_total - 4],
	//cmd[len_total - 3],cmd[len_total - 2],cmd[len_total - 1]);
	unsigned int len_bigclass = len_standard + PUBLIC_SIZE + 10;
	unsigned int big_class = cmd[len_bigclass];
	unsigned int small_class = cmd[len_bigclass + 1];
	unsigned int len_temp_crc = len_standard + PUBLIC_SIZE + 10;
	unsigned int conn_number = cmd[len_temp_crc + 2] * 65536 + cmd[len_temp_crc + 3] * 256 + cmd[len_temp_crc + 4];
	//printf("machine conn_number=%d\n",conn_number);
	if((buf[0] == cmd[len_total - 4]) && (buf[1] == cmd[len_total - 3])
	   && (buf[2] == cmd[len_total - 2]) && (buf[3] == cmd[len_total - 1]))
	{
		if(para == 0)
		{
			//printf("crc check pri right... big_class=%d,small_class=%d,conn_number_machine=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 1)
		{
			//printf("crc check pri right... big_class=%d,small_class=%d,conn_number_phone=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 2)
		{
			//printf("crc check pri right... big_class=%d,small_class=%d,conn_number_center=%d\n",big_class,small_class,conn_number);
		}
		return true;
	}
	else
	{
		printf("crc check pri error... big_class=%d,small_class=%d,conn_number_machine=%d\n",big_class,small_class,conn_number);
		printf_cmd_client(cmd,len_total);
		if(para == 0)
		{
			printf("len_standard=%d,len_std_a=%d,len_std_b=%d",len_standard,len_std_a,len_std_b);
			printf("len_pri = %d\n",len_pri);
			printf("len_total = %d\n",len_total);
			
			unsigned int len_temp = len_standard + 10 + 2;
			printf("len_temp = %d\n",len_temp);
			//printf("crc_value_private = %d\n",crc_value_private);
			//printf("cmd[len_temp] = 0x%02hhX\n",cmd[len_temp]);
			printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",buf[0],buf[1],buf[2],buf[3]);
			printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",cmd[len_total - 4],
				   cmd[len_total - 3],cmd[len_total - 2],cmd[len_total - 1]);
			
		}
		else if(para == 1)
		{
			printf("crc check pri error... big_class=%d,small_class=%d,conn_number_phone=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 2)
		{
			printf("crc check pri error... big_class=%d,small_class=%d,conn_number_center=%d\n",big_class,small_class,conn_number);
		}
		return false;
	}
}
bool Cstatic_func::crc_check_pri_machine_asc(unsigned char *cmd,int para,unsigned int len_total_real)
{
	unsigned char buf[5];
	memset(buf,0,sizeof(buf));
	char buf_id[256];
	memset(buf_id,0,sizeof(buf_id));
	memcpy(buf_id,&cmd[9],9);
	//printf("buf_id=%s\n",buf_id);
	/////////////////////////////////////////////////////////////////
	unsigned int len_std_a = 0;
	unsigned int len_std_b = 0;
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
	
	//printf("len_standard=%d,len_std_a=%d,len_std_b=%d",len_standard,len_std_a,len_std_b);
	///////////////////////////////////////////////////////////////////////////////////
	int len_pri_bb = 0;
	int len_pri_aa = 0;
	int aa = len_standard + 10 + 2;
	int bb = len_standard + 10 + 3;
	if(cmd[aa] < 58)
	{
		len_pri_aa = cmd[aa] - 48;
	}
	else if((cmd[aa] >= 65) && (cmd[aa] <= 70))
	{
		len_pri_aa = cmd[aa] - 55;
	}
	if(cmd[bb] < 58)
	{
		len_pri_bb = cmd[bb] - 48;
	}
	else if((cmd[bb] >= 65) && (cmd[bb] <= 70))
	{
		len_pri_bb = cmd[bb] - 55;
	}
	
	unsigned int len_pri = len_pri_aa * 16 + len_pri_bb;
	
	unsigned int len_total = len_standard + len_pri + 10 + 4 + 4;
	//printf("len_total = %d\n",len_total);
	
	
	unsigned int crc_value_private = calcCRC_buf(&cmd[len_standard + 10 + 4],len_pri);
	//printf("crc_value_private = %d\n",crc_value_private);
	NumToHex_4(crc_value_private,(char *)buf);
	//printf("cmd[len_temp] = 0x%02hhX\n",cmd[len_temp]);
	//printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",buf[0],buf[1],buf[2],buf[3]);
	//printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",cmd[len_total - 4],
	//cmd[len_total - 3],cmd[len_total - 2],cmd[len_total - 1]);
	
	if((buf[0] == cmd[len_total - 4]) && (buf[1] == cmd[len_total - 3])
	   && (buf[2] == cmd[len_total - 2]) && (buf[3] == cmd[len_total - 1]))
	{
		if(para == 0)
		{
			//printf("crc check pri right... big_class=%d,small_class=%d,conn_number_machine=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 1)
		{
			//printf("crc check pri right... big_class=%d,small_class=%d,conn_number_phone=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 2)
		{
			//printf("crc check pri right... big_class=%d,small_class=%d,conn_number_center=%d\n",big_class,small_class,conn_number);
		}
		return true;
	}
	else
	{
		printf("len_total = %d\n",len_total);
		printf("len_standard=%d,len_std_a=%d,len_std_b=%d",len_standard,len_std_a,len_std_b);
		printf("len_pri = %d\n",len_pri);
		printf_cmd_client_asc(cmd,len_total);
		if(para == 0)
		{
			
			unsigned int len_temp = len_standard + 10 + 2;
			printf("len_temp = %d\n",len_temp);
			printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",buf[0],buf[1],buf[2],buf[3]);
			printf("0x%02hhX 0x%02hhX 0x%02hhX 0x%02hhX \n",cmd[len_total - 4],cmd[len_total - 3],cmd[len_total - 2],cmd[len_total - 1]);
			printf("machine crc check pri error...... \n");
		}
		else if(para == 1)
		{
			//printf("crc check pri error... big_class=%d,small_class=%d,conn_number_phone=%d\n",big_class,small_class,conn_number);
		}
		else if(para == 2)
		{
			//printf("crc check pri error... big_class=%d,small_class=%d,conn_number_center=%d\n",big_class,small_class,conn_number);
		}
		return false;
	}
}

int Cstatic_func::find_place(char *buf,char ch,int len)
{
	int i;
	for(i = 0;i < len;i++)
	{
		if(buf[i] == ch)
		{
			return i;
		}
	}
	return -1;
	
}
int Cstatic_func::find_place_L(char *buf,char ch,int len)
{
	int count = 0;
	int i;
	for(i = 0;i < len;i++)
	{
		if(buf[i] == ch)
		{
			count++;
			if(count == 3){
				return i;
			}
			
			
		}
		if(count > 2){
			return -1;
		}
	}
	return -1;
	
}

int Cstatic_func::find_place_second(char *buf,char ch,int len)
{
	int count = 0;
	int i;
	for(i = 0;i < len;i++)
	{
		if(buf[i] == ch)
		{
			count++;
			if(count == 2){
				return i;
			}
			
		}
		if(count > 2){
			return -1;
		}
	}
	return -1;
	
}

unsigned int Cstatic_func::calcCRC2(unsigned int CRC, int ch)
{
	static unsigned int crcTable[]= {
		
		/* DEFINE THE FIRST ORDER POLYINOMIAL TABLE */
		0x0000,0xc0c1,0xc181,0x0140,0xc301,0x03c0,0x0280,0xc241,
		0xc601,0x06c0,0x0780,0xc741,0x0500,0xc5c1,0xc481,0x0440,
		0xcc01,0x0cc0,0x0d80,0xcd41,0x0f00,0xcfc1,0xce81,0x0e40,
		0x0a00,0xcac1,0xcb81,0x0b40,0xc901,0x09c0,0x0880,0xc841,
		0xd801,0x18c0,0x1980,0xd941,0x1b00,0xdbc1,0xda81,0x1a40,
		0x1e00,0xdec1,0xdf81,0x1f40,0xdd01,0x1dc0,0x1c80,0xdc41,
		0x1400,0xd4c1,0xd581,0x1540,0xd701,0x17c0,0x1680,0xd641,
		0xd201,0x12c0,0x1380,0xd341,0x1100,0xd1c1,0xd081,0x1040,
		0xf001,0x30c0,0x3180,0xf141,0x3300,0xf3c1,0xf281,0x3240,
		0x3600,0xf6c1,0xf781,0x3740,0xf501,0x35c0,0x3480,0xf441,
		0x3c00,0xfcc1,0xfd81,0x3d40,0xff01,0x3fc0,0x3e80,0xfe41,
		0xfa01,0x3ac0,0x3b80,0xfb41,0x3900,0xf9c1,0xf881,0x3840,
		0x2800,0xe8c1,0xe981,0x2940,0xeb01,0x2bc0,0x2a80,0xea41,
		0xee01,0x2ec0,0x2f80,0xef41,0x2d00,0xedc1,0xec81,0x2c40,
		0xe401,0x24c0,0x2580,0xe541,0x2700,0xe7c1,0xe681,0x2640,
		0x2200,0xe2c1,0xe381,0x2340,0xe101,0x21c0,0x2080,0xe041,
		0xa001,0x60c0,0x6180,0xa141,0x6300,0xa3c1,0xa281,0x6240,
		0x6600,0xa6c1,0xa781,0x6740,0xa501,0x65c0,0x6480,0xa441,
		0x6c00,0xacc1,0xad81,0x6d40,0xaf01,0x6fc0,0x6e80,0xae41,
		0xaa01,0x6ac0,0x6b80,0xab41,0x6900,0xa9c1,0xa881,0x6840,
		0x7800,0xb8c1,0xb981,0x7940,0xbb01,0x7bc0,0x7a80,0xba41,
		0xbe01,0x7ec0,0x7f80,0xbf41,0x7d00,0xbdc1,0xbc81,0x7c40,
		0xb401,0x74c0,0x7580,0xb541,0x7700,0xb7c1,0xb681,0x7640,
		0x7200,0xb2c1,0xb381,0x7340,0xb101,0x71c0,0x7080,0xb041,
		0x5000,0x90c1,0x9181,0x5140,0x9301,0x53c0,0x5280,0x9241,
		0x9601,0x56c0,0x5780,0x9741,0x5500,0x95c1,0x9481,0x5440,
		0x9c01,0x5cc0,0x5d80,0x9d41,0x5f00,0x9fc1,0x9e81,0x5e40,
		0x5a00,0x9ac1,0x9b81,0x5b40,0x9901,0x59c0,0x5880,0x9841,
		0x8801,0x48c0,0x4980,0x8941,0x4b00,0x8bc1,0x8a81,0x4a40,
		0x4e00,0x8ec1,0x8f81,0x4f40,0x8d01,0x4dc0,0x4c80,0x8c41,
		0x4400,0x84c1,0x8581,0x4540,0x8701,0x47c0,0x4680,0x8641,
		0x8201,0x42c0,0x4380,0x8341,0x4100,0x81c1,0x8081,0x4040,
	};
	
	unsigned char temp;
	
	temp = (unsigned char)ch;
	return (CRC >> 8) ^ (crcTable[temp ^ (CRC & 0xff)]);
	
}
unsigned int Cstatic_func::calcCRC(unsigned CRC, int ch)
{
	int i;
	unsigned char temp;
	temp = (unsigned char)ch;  /* TREAT LOCALLY AS UNSIGNED */
	for (i = 0; i < 8; i++)    /* DO 8 BITS */
	{
		temp ^= CRC & 1;                /* PROCESS LSB */
		CRC >>= 1;                      /* SHIFT RIGHT */
		if (temp & 1)
			CRC ^= 0xA001;        /* IF LSB SET,ADD FEEDBACK */
		temp >>= 1;                     /* GO TO NEXT BIT */
	}
	return CRC;
}
void Cstatic_func::NumToHex_4(int Num,char *lpHex)
{
	int Bit4;
	
	//////////////////////////////////////////////////////////////////////////////////////
	//int Bit4;
	Bit4=0xF000 & Num;/*»°∏ﬂÀƒŒª,»ª∫Û”““∆4Œª,º¥≥˝“‘16*/
	Bit4>>=12;
	if (Bit4>9)        /*‘Ÿ◊™ªª≥…◊÷∑˚¥Æ*/
		Bit4+=55;    /* 'A'-10=55 */
	else
		Bit4+='0';
	*lpHex++=Bit4;    /*¥Ê»Î∏ﬂŒª◊÷∑˚*/
	/**************************************************************/
	Bit4=0x0F00 & Num;/*»°µÕÀƒŒª*/
	Bit4>>=8;
	if (Bit4>9)
		Bit4+=55;
	else
		Bit4+='0';
	*lpHex=Bit4;    /*¥Ê»ÎµÕŒª◊÷∑˚*/
	/////////////////////////////////////////////////////////////////////////////////////////
	Bit4=0x00F0 & Num;/*»°∏ﬂÀƒŒª,»ª∫Û”““∆4Œª,º¥≥˝“‘16*/
	Bit4>>=4;
	if (Bit4>9)        /*‘Ÿ◊™ªª≥…◊÷∑˚¥Æ*/
		Bit4+=55;    /* 'A'-10=55 */
	else
		Bit4+='0';
	*++lpHex=Bit4;    /*¥Ê»Î∏ﬂŒª◊÷∑˚*/
	/**************************************************************/
	Bit4=0x000F & Num;/*»°µÕÀƒŒª*/
	if (Bit4>9)
		Bit4+=55;
	else
		Bit4+='0';
	*++lpHex=Bit4;    /*¥Ê»ÎµÕŒª◊÷∑˚*/
	
}
void Cstatic_func::NumToHex(int Num,char *lpHex)
{
	int Bit4;
	Bit4=0x00F0 & Num;/*»°∏ﬂÀƒŒª,»ª∫Û”““∆4Œª,º¥≥˝“‘16*/
	Bit4>>=4;
	if (Bit4>9)        /*‘Ÿ◊™ªª≥…◊÷∑˚¥Æ*/
		Bit4+=55;    /* 'A'-10=55 */
	else
		Bit4+='0';
	*lpHex++=Bit4;    /*¥Ê»Î∏ﬂŒª◊÷∑˚*/
	/**************************************************************/
	Bit4=0x000F & Num;/*»°µÕÀƒŒª*/
	if (Bit4>9)
		Bit4+=55;
	else
		Bit4+='0';
	*lpHex=Bit4;    /*¥Ê»ÎµÕŒª◊÷∑˚*/
	
}

unsigned int Cstatic_func::calcCRC_buf(unsigned char *buf,int len)
{
	unsigned int CRC;             /* 16 BIT CRC RESULT */
	CRC = 0;
	for(int i = 0;i < len;i++)
	{
		//CRC = calcCRC(CRC, buf[i]);   /* CALL CRC FUNCTION BELOW */
		CRC = calcCRC2(CRC, buf[i]);   /* CALL CRC FUNCTION BELOW */
	}
	return CRC;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////




unsigned int Cstatic_func::ascll_to_hex(unsigned char asc)
{
	if((asc >= 47) && (asc <= 57))
	{
		return (asc - 48);
	}
	if((asc >= 65) && (asc <= 87))
	{
		return (asc - 55);
	}
	if((asc >= 97) && (asc <= 122))
	{
		return (asc - 87);
	}
	return 0xff;
}
int Cstatic_func::create_ip_standard_event(unsigned char * buf,const char  *acct_id, const char  * acct_seq,
										  const char  * acct_Rrcvr, const char * acct_Lpref, const char * acct_machine)
{
	char buf_len[5];
	memset(buf_len,0,sizeof(buf_len));
	int len = 0;
	//unsigned char buf[1460];
	//memset(buf,255,sizeof(buf));
	buf[0] = 0x0A;//<LF>
	//crc final calc
	//0LLL
	//°∞id°±
	//const char * acct_id = "\"HENG-BO\"";
	int len_id = strlen(acct_id);
	
	memcpy(&buf[9],acct_id,len_id);
	//seqence
	//const char * acct_seq = "1111";
	//const char * acct_seq = "FFFF";
	int len_seq = strlen(acct_seq);
	memcpy(&buf[9 + len_id],acct_seq,len_seq);
	//R123ABC
	//const char * acct_Rrcvr = "R123ABC";
	//const char * acct_Rrcvr = "FFFFFFF";
	int len_Rrcvr = strlen(acct_Rrcvr);
	if((len_Rrcvr > 7) || (len_Rrcvr <= 0))
	{
		printf("error,create_ip_standard_event,len_Rrcvr=%d\n",len_Rrcvr);
		return -1;
		
	}
	memcpy(&buf[9 + len_id + len_seq],acct_Rrcvr,len_Rrcvr);
	//int len_Rrcvr = 0;
	//L456DEF
	//const char * acct_Lpref = "L456DEF";
	//const char * acct_Lpref = "L0";
	int len_Lpref = strlen(acct_Lpref);
	if((len_Lpref > 7) || (len_Lpref <= 0))
	{
		printf("error,create_ip_standard_event,len_Lpref=%d\n",len_Lpref);
		return -1;
		
	}
	memcpy(&buf[9 + len_id + len_seq + len_Rrcvr],acct_Lpref,len_Lpref);
	//#13867802353
	//const char * acct_machine = "#13867802353[]";
	//const char * acct_machine = "#FFFFFFFFFFF[]";
	////////////////////////////////////////////////////
	int len_acct = strlen(acct_machine);
	if((len_acct > 18) || (len_acct <= 0))
	{
		printf("error,create_ip_standard_event,len_acct=%d\n",len_acct);
		return -1;
		
	}
	char acct_temp[255];
	memset(acct_temp,0,sizeof(acct_temp));
	acct_temp[0] = '#';
	memcpy(&acct_temp[1],acct_machine,len_acct);
	memcpy(&acct_temp[1 + len_acct],"[]",2);
	int len_acct_temp = strlen(acct_temp);
	len_acct = len_acct_temp;
	////////////////////////////////////////////////////
	//int len_acct = strlen(acct_machine);
	memcpy(&buf[9 + len_id + len_seq + len_Rrcvr + len_Lpref],acct_temp,len_acct);
	int len_toacct = 0;
	len_toacct = 9 + len_id + len_seq + len_Rrcvr + len_Lpref + len_acct;
	////////////////////////////////////////////////////////////////////////////////
	char buf_temp[20];
	memset(buf_temp,0,sizeof(buf_temp));
	get_time(buf_temp);
	//printf("%s\n",buf_temp);
	int i;
	for(i = 0;i < 20;i++)
	{
		buf[len_toacct + i] = buf_temp[i];
	}
	//final calc 0LLL
	len = len_toacct + 20 - 9;
	NumToHex_4(len,buf_len);
	for(i = 0;i < 4;i++)
	{
		buf[5 + i] = buf_len[i];
	}
	//final calc CRC
	unsigned int crc_value = calcCRC_buf(&buf[9],len);
	NumToHex_4(crc_value,buf_len);
	for(i = 0;i < 4;i++)
	{
		buf[1 + i] = buf_len[i];
	}
	buf[len_toacct + 20] = 0x0D;//<CR>
	return (len_toacct + 21);
}
int Cstatic_func::create_ip_standard_event_center(unsigned char * buf,const char  *acct_id, const char  * acct_seq,
												 const char  * acct_Rrcvr, const char * acct_Lpref, const char * acct_machine)
{
	char buf_len[5];
	memset(buf_len,0,sizeof(buf_len));
	int len = 0;
	//unsigned char buf[1460];
	//memset(buf,255,sizeof(buf));
	buf[0] = 0x0A;//<LF>
	//crc final calc
	//0LLL
	//°∞id°±
	//const char * acct_id = "\"HENG-BO\"";
	int len_id = strlen(acct_id);
	memcpy(&buf[9],acct_id,len_id);
	//seqence
	//const char * acct_seq = "1111";
	//const char * acct_seq = "FFFF";
	int len_seq = strlen(acct_seq);
	memcpy(&buf[9 + len_id],acct_seq,len_seq);
	//R123ABC
	//const char * acct_Rrcvr = "R123ABC";
	//const char * acct_Rrcvr = "FFFFFFF";
	int len_Rrcvr = strlen(acct_Rrcvr);
	memcpy(&buf[9 + len_id + len_seq],acct_Rrcvr,len_Rrcvr);
	//int len_Rrcvr = 0;
	//L456DEF
	//const char * acct_Lpref = "L456DEF";
	//const char * acct_Lpref = "L0";
	int len_Lpref = strlen(acct_Lpref);
	memcpy(&buf[9 + len_id + len_seq + len_Rrcvr],acct_Lpref,len_Lpref);
	//#13867802353
	//const char * acct_machine = "#13867802353[]";
	//const char * acct_machine = "#FFFFFFFFFFF[]";
	
	int len_acct = strlen(acct_machine);
	char acct_temp[255];
	memset(acct_temp,0,sizeof(acct_temp));
	acct_temp[0] = '#';
	memcpy(&acct_temp[1],acct_machine,len_acct);
	memcpy(&acct_temp[1 + len_acct],"[]",2);
	int len_acct_temp = strlen(acct_temp);
	len_acct = len_acct_temp;
	
	memcpy(&buf[9 + len_id + len_seq + len_Rrcvr + len_Lpref],acct_temp,len_acct_temp);
	int len_toacct = 0;
	len_toacct = 9 + len_id + len_seq + len_Rrcvr + len_Lpref + len_acct;
	////////////////////////////////////////////////////////////////////////////////
	char buf_temp[20];
	memset(buf_temp,0,sizeof(buf_temp));
	get_time(buf_temp);
	//printf("%s\n",buf_temp);
	int i;
	for(i = 0;i < 20;i++)
	{
		buf[len_toacct + i] = buf_temp[i];
	}
	//final calc 0LLL
	len = len_toacct + 20 - 9;
	NumToHex_4(len,buf_len);
	for(i = 0;i < 4;i++)
	{
		buf[5 + i] = buf_len[i];
	}
	//final calc CRC
	unsigned int crc_value = calcCRC_buf(&buf[9],len);
	NumToHex_4(crc_value,buf_len);
	for(i = 0;i < 4;i++)
	{
		buf[1 + i] = buf_len[i];
	}
	buf[len_toacct + 20] = 0x0D;//<CR>
	return (len_toacct + 21);
}

void Cstatic_func::create_pricmd_public_29_wifi(unsigned char *buf,int len_toacct,int len_pri,const char *acct_machine,const char *psw,
											   const char *acct_phone,int level,int dest_type)
{
	
	int level_final = level_to_wifi(level,dest_type);
	/*if(dest_type == 1){
		level_final = (level) | 0x04;
	 
	 }else if(dest_type == 2){
		level_final = (level) | 0x08;
	 }else if(dest_type == 3){
		level_final = (level) | 0x0c;
	 }
	 //printf("dest_type=%d\n",dest_type);
	 //printf("level_final=%d\n",level_final);*/
	//private cmd length
	int length_private = len_pri;
	//int len_toacct = len_ip_event - 21;
	buf[len_toacct] = (length_private >> 8) & 0xff;
	buf[len_toacct + 1] = length_private & 0xff;
	//amarm machine account
	
	NumCStringToHexByte((char *)acct_machine, (char *)&buf[len_toacct + 2]);
	//alarm machine password
	
	//int len_alarm_psw = 4;
	//printf("len_alarm_psw=%d\n",len_alarm_psw);Cstatic_var:: NumCStringToHexByte_8(char *phone, char *buf)
	NumCStringToHexByte_8((char *)psw, (char *)&buf[len_toacct + 11]);
	//memcpy(&buf[len_toacct + 11],psw,len_alarm_psw);
	/*buf[len_toacct + 32] = '0';
	 buf[len_toacct + 33] = '0';
	 buf[len_toacct + 34] = '0';
	 buf[len_toacct + 35] = '0';*/
	//user mobile phone account
	NumCStringToHexByte((char *)acct_phone, (char *)&buf[len_toacct + 15]);
	//object level
	int len_tolevel = len_toacct + 9 + 9 - 1 + 4 + 2;
	buf[len_tolevel + 1] =  level_final;
	//alarm center ip address and port number
	buf[len_tolevel + 2] = 0;
	buf[len_tolevel + 3] = 0;
	buf[len_tolevel + 4] = 0;
	buf[len_tolevel + 5] = 0;
	buf[len_tolevel + 6] = 0;
	buf[len_tolevel + 7] = 0;
}


void Cstatic_func::create_pricmd_public_29(unsigned char *buf,int len_toacct,int len_pri,const char *acct_machine,const char *psw,
										  const char *acct_phone,int level)
{
	
	
	//private cmd length
	int length_private = len_pri;
	//int len_toacct = len_ip_event - 21;
	buf[len_toacct] = (length_private >> 8) & 0xff;
	buf[len_toacct + 1] = length_private & 0xff;
	//amarm machine account
	
	NumCStringToHexByte((char *)acct_machine, (char *)&buf[len_toacct + 2]);
	//alarm machine password
	
	int len_alarm_psw = 4;
	//printf("len_alarm_psw=%d\n",len_alarm_psw);
	memcpy(&buf[len_toacct + 11],psw,len_alarm_psw);
	/*buf[len_toacct + 32] = '0';
	 buf[len_toacct + 33] = '0';
	 buf[len_toacct + 34] = '0';
	 buf[len_toacct + 35] = '0';*/
	//user mobile phone account
	NumCStringToHexByte((char *)acct_phone, (char *)&buf[len_toacct + 15]);
	//object level
	int len_tolevel = len_toacct + 9 + 9 - 1 + 4 + 2;
	buf[len_tolevel + 1] =  level;
	//alarm center ip address and port number
	buf[len_tolevel + 2] = 0;
	buf[len_tolevel + 3] = 0;
	buf[len_tolevel + 4] = 0;
	buf[len_tolevel + 5] = 0;
	buf[len_tolevel + 6] = 0;
	buf[len_tolevel + 7] = 0;
}
int Cstatic_func::level_to_wifi(int level,int dest_type)
{
	int level_final = 0;
	if(dest_type == 1){
		level_final = (level) | 0x04;
		
	}else if(dest_type == 2){
		level_final = (level) | 0x08;
	}else if(dest_type == 3){
		level_final = (level) | 0x0c;
	}
	return level_final;
	
}

void Cstatic_func::level_transfer_to_wifi(int dest_type,unsigned char *cmd)
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
	unsigned int len_standard = len_std_a * 16 + len_std_b;
	unsigned int len_pri = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
	//unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;
	
	//printf("len_standard=%d,len_pri=%d,len_total=%d\n",len_standard,len_pri,len_total);
	int len_temp = len_standard + PUBLIC_SIZE + 10;
	//////////////////////////////////////////////////////////////////////////////////
	
	int level = cmd[len_temp - 7];
	
	int level_final = 0;
	if(dest_type == 1){
		level_final = (level) | 0x04;
		
	}else if(dest_type == 2){
		level_final = (level) | 0x08;
	}else if(dest_type == 3){
		level_final = (level) | 0x0c;
	}
	///////////////////////////////////////////////
	cmd[len_temp - 7] = level_final;
	//crc_private
	char buf_len[5];
	int length_private = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
	unsigned int crc_value_private = calcCRC_buf(&cmd[len_standard + 10 + 2],length_private);
	
	NumToHex_4(crc_value_private,buf_len);
	for(int i = 0;i < 4;i++)
	{
		cmd[len_standard + len_pri + 10 + 2 + i] = buf_len[i];
	}
	
}

char * Cstatic_func::HexByteToNumString(const char *hex, unsigned char len)
{
	
	int i;
	static char string[24] = {0};
	char num, high, low;
	for(i = 0; i < len; i++)
	{
		num = (unsigned char)hex[i];
		high = (unsigned char)0x0f & (num >> 4);
		low = (unsigned char)0x0f & num;
		
		if(high == 0x0f)
		{
			string[i*2] = '\0';
			break;
		}
		if(high < 0 || high > 9)
			string[i*2] = 'f';
		else
		{
			string[i*2] = high + '0';
		}
		
		if(low == 0x0f)
		{
			string[i*2+1] = '\0';
			break;
		}
		if(low < 0 || low > 9)
			string[i*2+1] = 'f';
		else
		{
			string[i*2+1] = low + '0';
		}
	}
	return string;
	
}
void Cstatic_func:: NumCStringToHexByte_8(char *phone, char *buf)
{
	char phone2[8];
	strcpy(phone2,phone);
	////////////////////////
	int len = strlen(phone2);
	char ch = 0;
	bool bAllNums = true;
	int i;
	for(i = 0; i < len; i++)
	{
		ch = phone2[i];
		if(ch < 48 || ch > 57)
		{
			bAllNums = false;
			break;
		}
	}
	
	if(bAllNums)
	{
		while(len < 8)
		{
			strcat(phone2,"f");
			len = strlen(phone2);
		}
		
		char num = 0;
		char hex[4];
		for(i = 0; i < len; i++)
		{
			ch = phone2[i];
			if(ch == 'f')
			{
				num = (unsigned char)0xff;
			}
			else
			{
				//num = Atoi(ch);
				num = ch - '0';
			}
			
			if(i % 2 == 0)
			{
				hex[i/2] = 0xf0 & (((unsigned char)num) << 4);
			}
			else
			{
				hex[i/2] |= (0x0f & (unsigned char)num);
			}
		}
		memcpy(buf, hex, 4);
	}
	else
	{
		memset(buf, 0xff, 4);
	}
	
}

void Cstatic_func:: NumCStringToHexByte(char *phone, char *buf)
{
	char phone2[18];
	strcpy(phone2,phone);
	////////////////////////
	int len = strlen(phone2);
	char ch = 0;
	bool bAllNums = true;
	int i;
	for(i = 0; i < len; i++)
	{
		ch = phone2[i];
		if(ch < 48 || ch > 57)
		{
			bAllNums = false;
			break;
		}
	}
	
	if(bAllNums)
	{
		while(len < 18)
		{
			strcat(phone2,"f");
			len = strlen(phone2);
		}
		
		char num = 0;
		char hex[9];
		for(i = 0; i < len; i++)
		{
			ch = phone2[i];
			if(ch == 'f')
			{
				num = (unsigned char)0xff;
			}
			else
			{
				//num = Atoi(ch);
				num = ch - '0';
			}
			
			if(i % 2 == 0)
			{
				hex[i/2] = 0xf0 & (((unsigned char)num) << 4);
			}
			else
			{
				hex[i/2] |= (0x0f & (unsigned char)num);
			}
		}
		memcpy(buf, hex, 9);
	}
	else
	{
		memset(buf, 0xff, 9);
	}
	
}

bool Cstatic_func::exception_len_ip_event(unsigned int len_ip_event,int type,const char *str)
{
	if(type == 0)
	{
		
		if((len_ip_event > MAX_LEN_STD) || (len_ip_event <= 40))
		{
			printf("exception_len_ip_event,len_ip_event=%d,type=%d,str=%s\n",len_ip_event,type,str);
			return true;
			
		}
		
	}
	
	
	return false;
}
void Cstatic_func::get_time(char *buf_out)
{
	
	char timestr[255];
	struct tm *tmutc;
	struct timeb tb;
	ftime(&tb);
	//now=localtime(&tb.time);
	/*sprintf(timestr,"_%02d:%02d:%02d,%02d-%02d-%04d",now->tm_hour,now->tm_min  ,now->tm_sec,now->tm_mon+1,now->tm_mday,
	 now->tm_year+1900);
	 memcpy(buf_out,timestr,20);*/
	
	//memcpy(buf_out,Cstatic_var::buf_ntp,20);
	time_t start_t;
	/*ªÒ»°»’¿˙ ±º‰*/
	time(&start_t);
	tmutc = gmtime(&start_t);
	//tmutc = localtime(&start_t);
	int year,mon,day,hour,min,sec;
	year = tmutc->tm_year+1900;
	mon = tmutc->tm_mon + 1;
	day = tmutc->tm_mday;
	hour = tmutc->tm_hour;
	min = tmutc->tm_min;
	sec = tmutc->tm_sec;
	
	
	/* ‰≥ˆ ±º‰*/
	//printf("%s±Í◊º ±º‰Œ™£∫\t%s %d %d:%d:%d\n", tmutc->tm_zone, asctime(tmutc), tmutc->tm_hour, tmutc->tm_min, tmutc->tm_sec);
	//printf("%d-%d-%d %d %d:%d:%d\n", (tmutc->tm_year+1900), (tmutc->tm_mon+1), tmutc->tm_mday,tmutc->tm_hour, tmutc->tm_min, tmutc->tm_sec);
	//printf("%d-%d-%d %d:%d:%d\n",year,mon,day,hour,min,sec);
	sprintf(timestr,"_%02d:%02d:%02d,%02d-%02d-%04d",hour,min,sec,mon,day,year);
	//printf("%s \n",timestr);
	memcpy(buf_out,timestr,20);
	
}
void Cstatic_func::get_time_log(char *buf_out)
{
	char datestr[255];
	char timestr[255];
	struct tm *now;
	struct timeb tb;
	ftime(&tb);
	now=localtime(&tb.time);
	sprintf(datestr,"%04d-%02d-%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday);
	sprintf(timestr," %02d:%02d:%02d.txt",now->tm_hour,now->tm_min  ,now->tm_sec );
	//sprintf(timestr,"_%02d:%02d:%02d,%02d-%02d-%04d",now->tm_hour,now->tm_min  ,now->tm_sec,now->tm_mon+1,now->tm_mday,
	//now->tm_year+1900);
	strcat(datestr,timestr);
	//char time_temp2[256];
	//strcpy(time_temp2,".txt");
	//strcat(time_temp,time_temp2);
	int len = strlen(datestr);
	memcpy(buf_out,datestr,len);
	//buf_out = timestr;
	//printf("%s\n",timestr);
}



