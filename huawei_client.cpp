//
// Created by Administrator on 2020/3/21/021.
//

#include "huawei_client.h"
#include "static_var.hpp"
#include "tcp_socket.hpp"
#include "static_func.hpp"


struct huawei_server_info Chuawei_client::huaweiServerInfo[MAX_USER_NUMBER_HUAWEI];
struct epoll_event Chuawei_client::events_huawei_handle[MAX_EVENTS];
int Chuawei_client::socket_fd_huawei_handle = -1;

Chuawei_client* Chuawei_client::p_inst = NULL;
Chuawei_client::Chuawei_client()
{

}

Chuawei_client::~Chuawei_client()
{

}

Chuawei_client* Chuawei_client::get_instance()
{
    if(p_inst == NULL)
    {
        p_inst = new Chuawei_client();
    }
    return p_inst;
}

void Chuawei_client::huawei_server_info_init_time(unsigned int conn_number)
{
    Chuawei_client::huaweiServerInfo[conn_number].huawei_time_start_server = time((time_t *)NULL);
    Chuawei_client::huaweiServerInfo[conn_number].huawei_time_end_server = time((time_t *)NULL);
}


void Chuawei_client::huawei_server_info_init(unsigned int conn_number)
{

    memset(Chuawei_client::huaweiServerInfo[conn_number].huawei_str_ip_address,0,sizeof(Chuawei_client::huaweiServerInfo[conn_number].huawei_str_ip_address));
    Chuawei_client::huaweiServerInfo[conn_number].huawei_bHave_server = false;
    Chuawei_client::huaweiServerInfo[conn_number].huawei_bUsed = false;
    Chuawei_client::huaweiServerInfo[conn_number].huawei_epfd_server = -1;
    Chuawei_client::huaweiServerInfo[conn_number].huawei_sockfd_server = - 1;
    huawei_server_info_init_time(conn_number);

}
void Chuawei_client::huawei_server_info_init2(unsigned int conn_number)
{
    if(Chuawei_client::huaweiServerInfo[conn_number].huawei_sockfd_server != -1)
    {
        Chuawei_client::Close(Chuawei_client::huaweiServerInfo[conn_number].huawei_sockfd_server);
        Chuawei_client::huaweiServerInfo[conn_number].huawei_sockfd_server = -1;
    }


    if(Chuawei_client::huaweiServerInfo[conn_number].huawei_epfd_server != -1)
    {
        Chuawei_client::Close(Chuawei_client::huaweiServerInfo[conn_number].huawei_epfd_server);
        Chuawei_client::huaweiServerInfo[conn_number].huawei_epfd_server = -1;
    }
    //memset(Chuawei_client::huaweiServerInfo[conn_number].str_ip_address,0,sizeof(Chuawei_client::huaweiServerInfo[conn_number].str_ip_address));
    //Chuawei_client::huaweiServerInfo[conn_number].bHave_server = false;
    Chuawei_client::huaweiServerInfo[conn_number].huawei_bUsed = false;
    Chuawei_client::huaweiServerInfo[conn_number].huawei_epfd_server = -1;
    Chuawei_client::huaweiServerInfo[conn_number].huawei_sockfd_server = - 1;
    huawei_server_info_init_time(conn_number);

}

void Chuawei_client::Close(int fd)
{
    ///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
    printf("......function_name:%s\n",__func__);
#else
#endif
    ///////////////////////////////////////////////
    if (close(fd) == -1)
    {
        perror("close error");
    }
    else
    {
        //printf("socket release success!\n");
    }
}


void Chuawei_client::create_thread_huawei_handle()
{

    ///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
    printf("......function_name:%s\n",__func__);
#else
#endif
    /////////////////////////////////////////////////
    printf("tttttttttttttttttttttttt \n");
    pthread_attr_init(&attr_huawei_handle);
    pthread_attr_setdetachstate(&attr_huawei_handle,PTHREAD_CREATE_DETACHED);
    if (pthread_create(&pthreadid_huawei_handle, &attr_huawei_handle, ThreadHandle_huawei_handle,NULL) == 0)
    {
        printf("pthreadid_huawei_handle %lu\n",pthreadid_huawei_handle);

    }
    pthread_attr_destroy(&attr_huawei_handle);
}
void Chuawei_client::create_thread_huawei_conn()
{

    ///////////////////////////////////////////
#ifdef PRINT_FUNC_NAME
    printf("......function_name:%s\n",__func__);
#else
#endif
    /////////////////////////////////////////////////
    printf("tttttttttttttttttttttttt \n");
    pthread_attr_init(&attr_huawei_conn);
    pthread_attr_setdetachstate(&attr_huawei_conn,PTHREAD_CREATE_DETACHED);
    if (pthread_create(&pthreadid_huawei_conn, &attr_huawei_conn, ThreadHandle_huawei_conn,NULL) == 0)
    {
        printf("pthreadid_huawei_conn %lu\n",pthreadid_huawei_conn);

    }
    pthread_attr_destroy(&attr_huawei_conn);
}

void* Chuawei_client::ThreadHandle_huawei_handle(void *args)
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
        //printf("ThreadHandle_huawei_handle,aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
        signal(SIGPIPE, SIG_IGN);
        Ctcp_socket *p_tcp_sock = Ctcp_socket::get_instance();
        while(1)
        {
            for(j = 0;j < MAX_USER_NUMBER_HUAWEI;j++)
            {
                int nfds=epoll_wait(Chuawei_client::huaweiServerInfo[j].huawei_epfd_server,Chuawei_client::events_huawei_handle,MAX_EVENTS,0);
                if(nfds > 0)
                {
                    //printf("ThreadHandle_jiaxing,nfds=%d\n",nfds);
                }
                int i;
                for(i=0;i<nfds;++i)
                {
                    if(Chuawei_client::events_huawei_handle[i].data.fd == Chuawei_client::huaweiServerInfo[j].huawei_sockfd_server)
                    {


                        if(Chuawei_client::events_huawei_handle[i].events & EPOLLIN)
                        {
                            while(b_find_thread)
                            {

                                int i_t1 = i_13 %10;

                                len_recv = recv(Chuawei_client::huaweiServerInfo[j].huawei_sockfd_server,&buf_small[i_t1],1,MSG_WAITALL);
                                if((len_recv == -1))
                                {
                                    break;
                                }
                                if((len_recv == 0))
                                {
                                    printf("ThreadHandle_jiaxing,socket release,Chuawei_client::huaweiServerInfo[j].huawei_sockfd_server=%d\n", Chuawei_client::huaweiServerInfo[j].huawei_sockfd_server);
                                    Chuawei_client::huawei_server_info_init2(j);
                                    break;
                                }
                                if(len_recv > 0)
                                {
                                    i_13++;
                                    if(buf_small[i_t1] == '"')
                                    {
                                        len_recv = recv(Chuawei_client::huaweiServerInfo[j].huawei_sockfd_server,buf_id,3,MSG_WAITALL);
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
                                            len_recv = recv(Chuawei_client::huaweiServerInfo[j].huawei_sockfd_server,pos + 13,len_standard - 1,MSG_WAITALL);
                                            if((len_recv <= 0) || (len_recv == -1))
                                            {
                                                //printf("len_recv=%d\n",len_recv);
                                                break;
                                            }
                                            if(len_recv == (len_standard - 1))
                                            {
                                                len_pri = buf[len_standard + 10] * 256 + buf[len_standard + 10 + 1];
                                                int len_total = len_standard + len_pri + 10 + 2 + 4;

                                                if(Cstatic_var::p_static_func->exception_handle_cmd_format("phone len_pri",3,len_pri,MAX_LEN_PRI))
                                                {
                                                    break;
                                                }
                                                len_recv = recv(Chuawei_client::huaweiServerInfo[j].huawei_sockfd_server,pos + len_standard + 10 + 2,len_pri + 4,MSG_WAITALL);
                                                if((len_recv <= 0) || (len_recv == -1))
                                                {
                                                    break;
                                                }
                                                if(len_recv == (len_pri + 4))
                                                {
                                                    //printf("ThreadHandle_jiaxing,len_total=%d\n",len_total);
                                                    //Chuawei_client::p_static_func->printf_cmd_client_hex((unsigned char*)buf,len_total);
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
                                                    command_handle_huawei((unsigned char *)buf,Chuawei_client::huaweiServerInfo[j].huawei_sockfd_server);
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
            usleep(1000);
        }
    }
}

void* Chuawei_client::ThreadHandle_huawei_conn(void *args)
{
    signal(SIGPIPE, SIG_IGN);

    Ctcp_socket *p_tcp_sock = Ctcp_socket::get_instance();
    while(1)
    {
//        printf("ThreadHandle_huawei_conn,aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
        int i;
//        for(i=0;i<MAX_USER_NUMBER_APNS;i++)
        for(i=0;i<1;i++)
        {
            if ((Chuawei_client::huaweiServerInfo[i].huawei_bHave_server) && (!Chuawei_client::huaweiServerInfo[i].huawei_bUsed)) {
                Chuawei_client::huawei_server_info_init2(i);
                int ret_conn = p_tcp_sock->tcp_connect_timeout (&(Chuawei_client::huaweiServerInfo[i].huawei_sockfd_server), 3 ,Chuawei_client::huaweiServerInfo[i].huawei_str_ip_address,9501);
                printf("ThreadHandle_huawei_conn,i=%d,ret_conn=%d\n",i,ret_conn);
                printf("ThreadHandle_huawei_conn,Chuawei_client::huaweiServerInfo[%d].huawei_str_ip_address=%s\n",i,Chuawei_client::huaweiServerInfo[i].huawei_str_ip_address);
                if (ret_conn > 0) {
                    Chuawei_client::huaweiServerInfo[i].huawei_bUsed = true;

                    Chuawei_client::huaweiServerInfo[i].huawei_epfd_server = Cstatic_var::p_static_func->EpollConfig(Chuawei_client::huaweiServerInfo[i].huawei_sockfd_server,false);;
                    Chuawei_client::huawei_server_info_init_time(i);

//                    Chuawei_client::send_server_info_to_huawei_00_03(0,"15934928273","860399450179481","0868551036300526300002881100CN01",1);
                }
            }
        }





//        if (Cstatic_var::time_calculate_three_second >= 123) {
//        if (Cstatic_var::time_calculate_three_second >= 61) {
        if (Cstatic_var::time_calculate_three_second >= 9) {

            for (int i = 0; i < MAX_USER_NUMBER_HUAWEI; i++) {
//                if(Chuawei_client::huaweiServerInfo[i].huawei_bUsed){
                if((Chuawei_client::huaweiServerInfo[i].huawei_bHave_server) && (!Chuawei_client::huaweiServerInfo[i].huawei_bUsed)){
//                    printf("ThreadHandle_huawei_conn,bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n");
                    send_heart_beat_to_server(i);

                }
            }
            Cstatic_var::time_calculate_three_second = 0;
        }
        Cstatic_var::time_calculate_three_second++;
//        printf("Cstatic_var::time_calculate_three_second=%d\n",Cstatic_var::time_calculate_three_second);

        usleep(1000000);
    }
}


void Chuawei_client::send_heart_beat_to_server(unsigned int index)
{
    unsigned char buf[1460];
    char buf_len[5];
    int i;
    memset(buf,0,sizeof(buf));
    int len_ip_event = Cstatic_var::p_static_func->create_ip_standard_event(buf,ACCT_ID,ACCT_SEQ,ACCT_RRCVR,
                                                               ACCT_LPREF,ACCT_MACHINE);
    //printf("len_ip_event=%d\n",len_ip_event);
    if(Cstatic_var::p_static_func->exception_len_ip_event(len_ip_event,0,"send_connnumber_tophone"))
    {
        return;
    }
    /////////////////////////////////////////////////////////////////////////////////////
    //private public cmd
    int length_private = 29 + 5;
    int len_toacct = len_ip_event;
    Cstatic_var::p_static_func->create_pricmd_public_29(buf,len_toacct,length_private,
                                           "FFFFFFFFFFF","123456","FFFFFFFFFFF",2);
    //printf("length_private=%d\n",length_private);
    int len_tolevel = len_toacct + 9 + 9 - 1 + 4 + 2;
    buf[len_tolevel + 8] = 0x33;
    buf[len_tolevel + 9] = 0x00;
    buf[len_tolevel + 10] = (index >> 16) & 0xff;
    buf[len_tolevel + 11] = (index >> 8) & 0xff;
    buf[len_tolevel + 12] = index & 0xff;
    //crc_private
    unsigned int crc_value_private = Cstatic_var::p_static_func->calcCRC_buf(&buf[len_toacct + 2],length_private);
    Cstatic_var::p_static_func->NumToHex_4(crc_value_private,buf_len);
    for(i = 0;i < 4;i++)
    {
        buf[len_tolevel + 13 + i] = buf_len[i];
    }
    send_cmd_to_server_huawei(index,buf);



}

void Chuawei_client::send_cmd_to_server_huawei(unsigned int index,unsigned char *cmd)
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
    unsigned int len_standard = len_std_a * 16 + len_std_b;
    unsigned int len_pri = cmd[len_standard + 10] * 256 + cmd[len_standard + 10 + 1];
    unsigned int len_total = len_standard + len_pri + 10 + 2 + 4;

    //printf("len_standard=%d,len_pri=%d,len_total=%d\n",len_standard,len_pri,len_total);
    int len_temp = len_standard + PUBLIC_SIZE + 10;
    //////////////////////////////////////////////////////////////////////////////////

    unsigned int big_class = cmd[len_temp];
    unsigned int small_class = cmd[len_temp + 1];


    //crc_private
    char buf_len[5];
    unsigned int crc_value_private = Cstatic_var::p_static_func->calcCRC_buf(&cmd[len_standard + 10 + 2],len_pri);
    Cstatic_var::p_static_func->NumToHex_4(crc_value_private,buf_len);
    for(int i = 0;i < 4;i++)
    {
        cmd[len_total -(4 - i)] = buf_len[i];
    }


    /////////////////////////////////////////////////////////////
//    Cstatic_var::p_static_func->printf_cmd_client((unsigned char*)cmd,len_total);

    int ret2 = send(Chuawei_client::huaweiServerInfo[index].huawei_sockfd_server,(char *)cmd,len_total,0);
//	printf("send_cmd_towe_chat,big_class=%02x, small_class=%02x,send to phone,ret2=%d\n",
//		   big_class, small_class,ret2);

}

void Chuawei_client::command_handle_huawei(unsigned char *cmd,int sock_recv)
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
    if(!((big_class == 0x44) || ((big_class == 0x0e) && (small_class == 0x03)) || ((big_class == 0x00) && (small_class == 0x02))))
    {
        if(conn_number >= MAX_USER_NUMBER_APNS)
        {
            printf("big_class=%02x, small_class=%02x\n",big_class, small_class);
            printf("huawei conn_number=%d is out of max conn_number\n",conn_number);
            return;
        }
    }


    //printf("command_handle_apns,big_class=%02x, small_class=%02x,conn_number=%d\n",big_class, small_class,conn_number);

//    Cstatic_var::p_static_func->printf_cmd_client((unsigned char*)cmd,len_total);

    switch(big_class)
    {
        case 0x44:
        {
            if (small_class == 00) {//
                try{

                    printf("big_class=%02x, small_class=%02x\n",big_class, small_class);
                }
                catch(...){

                }

            }
            if (small_class == 01) {//
                try{

                    printf("delete machine,big_class=%02x, small_class=%02x\n",big_class, small_class);
                    if(Cstatic_var::ServerInfo[0].bUsed){
                        Cstatic_var::send_cmd_to_server(0,cmd);
                    }
                    if(Cstatic_var::ServerInfo[1].bUsed){
                        Cstatic_var::send_cmd_to_server(1,cmd);
                    }
                    if(Cstatic_var::ServerInfo[2].bUsed){
                        Cstatic_var::send_cmd_to_server(2,cmd);
                    }
                    if(Cstatic_var::ServerInfo[3].bUsed){
                        Cstatic_var::send_cmd_to_server(3,cmd);
                    }

                }
                catch(...){

                }

            }
            if (small_class == 04) {//
                try{

                    printf("history_record,big_class=%02x, small_class=%02x\n",big_class, small_class);
                    if(Cstatic_var::ServerInfo[0].bUsed){
                        Cstatic_var::send_cmd_to_server(0,cmd);
                    }
                    if(Cstatic_var::ServerInfo[1].bUsed){
                        Cstatic_var::send_cmd_to_server(1,cmd);
                    }
                    if(Cstatic_var::ServerInfo[2].bUsed){
                        Cstatic_var::send_cmd_to_server(2,cmd);
                    }
                    if(Cstatic_var::ServerInfo[3].bUsed){
                        Cstatic_var::send_cmd_to_server(3,cmd);
                    }

                }
                catch(...){

                }

            }
        }

            break;
        case 0x0e://phone send to netserver
        {

            if(small_class == 0x00)//apple app online and china or english
            {
            }


        }
            break;
        case 0x05:
        {
            try{
                if (small_class == 0x00) {//handle alarm event




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

void Chuawei_client::send_server_info_to_huawei_00_03(unsigned int conn_number,char * account_phone,char * account_machine,char * device_tocken,unsigned int language)
{
    unsigned char buf[1460];
    char buf_len[5];
    int i;
    memset(buf,0,sizeof(buf));
    int len_ip_event = Cstatic_var::p_static_func->create_ip_standard_event(buf,ACCT_ID,ACCT_SEQ,ACCT_RRCVR,
                                                             ACCT_LPREF,ACCT_MACHINE);
    //printf("len_ip_event=%d\n",len_ip_event);
    if(Cstatic_var::p_static_func->exception_len_ip_event(len_ip_event,0,"send_connnumber_tophone"))
    {
        return;
    }
    /////////////////////////////////////////////////////////////////////////////////////
    //private public cmd
    int length_private = 29 + 105;
    int len_toacct = len_ip_event;
    Cstatic_var::p_static_func->create_pricmd_public_29(buf,len_toacct,length_private,
                                         "864501039979481","123456","15934928273",2);
    //printf("length_private=%d\n",length_private);
    int len_tolevel = len_toacct + 9 + 9 - 1 + 4 + 2;
    buf[len_tolevel + 6] = language & 0xff;
    buf[len_tolevel + 7] = 0;
    buf[len_tolevel + 8] = 0x00;
    buf[len_tolevel + 9] = 0x03;
    buf[len_tolevel + 10] = (conn_number >> 16) & 0xff;
    buf[len_tolevel + 11] = (conn_number >> 8) & 0xff;
    buf[len_tolevel + 12] = conn_number & 0xff;
    memcpy(&buf[len_tolevel + 13],account_phone,18);
    memcpy(&buf[len_tolevel + 13 + 18],account_machine,18);
    memcpy(&buf[len_tolevel + 13 + 18 + 18],device_tocken,64);


    //crc_private
    unsigned int crc_value_private = Cstatic_var::p_static_func->calcCRC_buf(&buf[len_toacct + 2],length_private);
    Cstatic_var::p_static_func->NumToHex_4(crc_value_private,buf_len);
    for(i = 0;i < 4;i++)
    {
        buf[len_tolevel + 13 + 18 + 18 + 64 + i] = buf_len[i];
    }


    send_cmd_to_server_huawei(0,buf);



}
