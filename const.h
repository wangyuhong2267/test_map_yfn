//
//  const.h
//  test_map
//
//  Created by wangyuhong2267 on 17/2/26.
//  Copyright © 2017年 wangyuhong2267. All rights reserved.
//

#ifndef const_h
#define const_h
#include	<sys/types.h>	//basic system data types
#include	<sys/socket.h>	//basic socket definitions
#include	<sys/time.h>	//timeval{} for select()
#include	<time.h>		//timespec{} for pselect()
#include	<netinet/in.h>	//sockaddr_in{} and other Internet defns
#include	<arpa/inet.h>	//inet(3) functions
#include	<errno.h>
#include	<fcntl.h>		//for nonblocking
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	//for S_xxx file mode constants
#include	<sys/uio.h>		//for iovec{} and readv/writev
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		//for Unix domain sockets

#include    <pthread.h>     //thread
#include    <sys/shm.h>     //share memory
#include    <sys/sem.h>     //semaphore
#include    <semaphore.h>
#include    <sys/ipc.h>     //ipc communication
#include    <stdbool.h>
#include <sys/epoll.h>
#include <sys/mman.h>

#include <linux/reboot.h>
#include <pthread.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/timeb.h>
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <getopt.h>


#include <list>
#include <map>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <mutex>

#include "log.h"
using namespace std;
////////////////////////////////////////////////////////////////////////////



#define MAX_FDS    10


#define DEBUG

#ifdef DEBUG
#define printf(format,args...) Clog::Log(format,##args)
#else
#define dbg(format,...)
#endif

//#define PRINT_FUNC_NAME
///////////////////////////////////////////////////
#define SEVER_PORT 7890
#define SEVER_PORT_MACHINE 7891
#define SEVER_PORT_ALARM_CENTER 7892
#define SEVER_PORT_WE_CHAT 7893


#define QIANGONG
#define SERVER_TEST




/*#ifdef QIANGONG
 #define MAX_USER_NUMBER 32
 #define MAX_USER_NUMBER_MACHINE 8
 #define MAX_USER_NUMBER_ALARM_CENTER 4
 
 #else
 #define MAX_USER_NUMBER 120000
 #define MAX_USER_NUMBER_MACHINE 30000
 #define MAX_USER_NUMBER_ALARM_CENTER 1000
 
 #endif*/
#define MAX_USER_NUMBER_APNS 100
#ifdef QIANGONG
#define MAX_USER_NUMBER 100
#define MAX_USER_NUMBER_MACHINE 100000
#define MAX_USER_NUMBER_ALARM_CENTER 5000

#else
#define MAX_USER_NUMBER 100
#define MAX_USER_NUMBER_MACHINE 100000
#define MAX_USER_NUMBER_ALARM_CENTER 5000


#endif
//#ifdef QIANGONG
//#define MAX_USER_NUMBER 4000
//#define MAX_USER_NUMBER_MACHINE 1000
//#define MAX_USER_NUMBER_ALARM_CENTER 5000

//#else
//#define MAX_USER_NUMBER 400000
//#define MAX_USER_NUMBER_MACHINE 100000
//#define MAX_USER_NUMBER_ALARM_CENTER 5000


//#endif

#define CONN_START_MACHINE 0
#define CONN_START_PHONE 0
#define CONN_START_CENTER 1





//#define MAX_EVENTS 30000

#define MAX_EVENTS 100
////////////////////////////////////////////////////
#define MAX_LISTEN_BUF MAX_USER_NUMBER*10
#define IDLEIDLE 0x0000ffff
#define IDLEIDLEIDLE 0x00ffffff

#define PRINTF_LINE_BYTES 20
#define PRINTF_LINE_BYTES_ASC 45

#define IDLE_MAX 0xffffffff
#define PUBLIC_SIZE 31
#define ACCT_ID_NO_QUOTE "HENG-BO"
#define ACCT_ID_ACK_NO_QUOTE  "ACK"
#define ACCT_ID_NAK_NO_QUOTE  "NAK"
#define ACCT_ID_NULL_NO_QUOTE  "NULL"

#define ACCT_ID "\"HENG-BO\""
#define ACCT_ID_ACK  "\"ACK\""
#define ACCT_ID_NAK  "\"NAK\""
#define ACCT_ID_NULL  "\"NULL\""




#define ACCT_SEQ  "FFFF"
#define ACCT_RRCVR  "R123ABC"
#define ACCT_LPREF  "L456DEF"
#define ACCT_MACHINE  "FFFFFFFFFFF"



#define NTP_SERVER  "198.60.22.240"
#define NTP_PORT    37//123
#define JAN_1970    0x83aa7e80	//3600s*24h*(365days*70years+17days)
#define NTPFRAC(x) (4294 * (x) + ((1981 * (x)) >> 11))
#define USEC(x) (((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))
#define MAXDATASIZE 100
#define SERVPORT 1234
#define MAXLINE 1024

#define MAX_NUMS_IP_CENTER 1000
#define MAX_NUMS_IP_MACHINE 10000
#define MAX_NUMS_IP_PHONE 40000


//#define MAX_LIMIT_CONN 1000
#define MAX_LIMIT_CONN 999999999
#define MAX_LIMIT_CONN_CENTER 999999999
#define MAX_LIMIT_CONN_PHONE 999999999


//const int  HEARTBEAT_INTERVAL_APNS_THREE_THIME = 20;
//const int  HEARTBEAT_INTERVAL_APNS_ONE_TIME = 6;
const int  HEARTBEAT_INTERVAL_APNS_THREE_THIME = 241;
const int  HEARTBEAT_INTERVAL_APNS_ONE_TIME = 60;

///////////////////////////////////////////////////////////////////////////
const unsigned int MAX_THREADNUMS=1;

#ifdef QIANGONG
const int  DETECT_INTERVAL_MACHINE = 91;
const int  DETECT_INTERVAL_MACHINE_CENTER = 190;

const int  DETECT_INTERVAL_PHONE = 24;
#else
const int  DETECT_INTERVAL_MACHINE = 91;
const int  DETECT_INTERVAL_MACHINE_CENTER = 190;

const int  DETECT_INTERVAL_PHONE = 24;
#endif
//#ifdef QIANGONG
//const int  DETECT_INTERVAL_MACHINE = 999999999;
//const int  DETECT_INTERVAL_PHONE = 999999999;
//#else
//const int  DETECT_INTERVAL_MACHINE = 999999999;
//const int  DETECT_INTERVAL_PHONE = 999999999;
//#endif




/*#ifdef QIANGONG
 const int  DETECT_INTERVAL_MACHINE = 72000;
 const int  DETECT_INTERVAL_PHONE = 72000;
 #else
 const int  DETECT_INTERVAL_MACHINE = 360;
 const int  DETECT_INTERVAL_PHONE = 60;
 #endif*/




const int  DETECT_INTERVAL_CENTER = 15;




const int MAX_LEN_STD = 115;
const int MAX_LEN_PRI = 1460;
//const unsigned int BUF_SIZE = 1024*1024;



const unsigned int PAK_NUMS = 29999;
const unsigned int PAK_NUMS2 = 59999;
const unsigned int PAK_NUMS3 = 89999;
const unsigned int PAK_NUMS4 = 119999;
const unsigned int PAK_NUMS_CENTER = 99;
const unsigned int MAX_BUF_SOCKFD = 1000;



#pragma pack (1)

struct server_info
{
	char str_ip_address[16];
	bool bHave_server;
	bool bUsed;
	unsigned int  epfd_server;
	int  sockfd_server;
	time_t time_start_server;
	time_t time_end_server;
	
};
#pragma pack ()

#pragma pack (1)
typedef struct phone_info{
	string phone_device_tocken;
	string phone_account;
	//string online_or_offline;
	//string language;
}Cphone_info;
#pragma pack ()

#pragma pack (1)
typedef struct machine_info{
	string machine_account;
	string phone_account;
	string badge_identification;
	
}Cmachine_info;
#pragma pack ()

#pragma pack (1)
typedef struct machine_info_language{
	string machine_account;
	string phone_account;
	string language;
	
}Cmachine_info_language;
#pragma pack ()

#pragma pack (1)
typedef struct alarm_event_cid_info{
	string alarm_cid;
	string date_time_cid;
}Calarm_event_cid_info;
#pragma pack ()

#pragma pack (1)
typedef struct machine_05_00_cid_info{
	string event_cid_05_00;
	time_t time_start_05_00;
	
}Cmachine_05_00_cid_info;
#pragma pack ()

#endif /* const_h */
