//
// Created by Administrator on 2020/3/21/021.
//
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

#ifndef TEST_MAP_HUAWEI_CLIENT_H
#define TEST_MAP_HUAWEI_CLIENT_H

#define MAX_USER_NUMBER_APNS 100
#define MAX_USER_NUMBER_HUAWEI 100
//#define MAX_USER_NUMBER_HUAWEI 1
#define MAX_EVENTS 100



struct huawei_server_info
{
    char huawei_str_ip_address[16];
    bool huawei_bHave_server;
    bool huawei_bUsed;
    unsigned int  huawei_epfd_server;
    int  huawei_sockfd_server;
    time_t huawei_time_start_server;
    time_t huawei_time_end_server;

};
#pragma pack ()


#pragma pack (1)

class Chuawei_client {

public:
    Chuawei_client();
    virtual ~Chuawei_client();
    pthread_t   pthreadid_huawei_handle;
    pthread_attr_t attr_huawei_handle;
    pthread_t   pthreadid_huawei_conn;
    pthread_attr_t attr_huawei_conn;


    static struct huawei_server_info huaweiServerInfo[MAX_USER_NUMBER_HUAWEI];
    static int socket_fd_huawei_handle;
    static struct epoll_event events_huawei_handle[MAX_EVENTS];


    static Chuawei_client* p_inst;
    static Chuawei_client *get_instance();
    static void huawei_server_info_init_time(unsigned int conn_number);
    static void huawei_server_info_init(unsigned int conn_number);
    static void huawei_server_info_init2(unsigned int conn_number);

    static void Close(int fd);

    void create_thread_huawei_handle();
    static void * ThreadHandle_huawei_handle(void *args);
    void create_thread_huawei_conn();
    static void * ThreadHandle_huawei_conn(void *args);
    static void send_heart_beat_to_server(unsigned int index);
    static void send_cmd_to_server_huawei(unsigned int index,unsigned char *cmd);
    static void command_handle_huawei(unsigned char *cmd,int sock_recv);
    static void send_server_info_to_huawei_00_03(unsigned int conn_number,char * account_phone,char * account_machine,char * device_tocken,unsigned int language);

};


#endif //TEST_MAP_HUAWEI_CLIENT_H
