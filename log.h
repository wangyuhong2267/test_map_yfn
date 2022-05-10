// log.h: interface for the Clog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__3FAFFDFB_EC83_4E94_A1F2_76D25188FA90__INCLUDED_)
#define AFX_LOG_H__3FAFFDFB_EC83_4E94_A1F2_76D25188FA90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "head.h"
//////////////////////////////////////////////
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
#include    <sys/shm.h>     //share memory
#include    <sys/sem.h>     //semaphore
#include    <semaphore.h>
#include    <sys/ipc.h>     //ipc communication
#include    <stdbool.h>
#include <sys/epoll.h>
#include <sys/mman.h>  
#include <linux/reboot.h> 
//#include <pthread.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/timeb.h>
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <getopt.h>
//////////////////////////////////////////////

#define  CRITICAL_SECTION   pthread_mutex_t
#define  _vsnprintf         vsnprintf

//Log{
#define MAXLOGSIZE 20000000
#define ARRSIZE(x) (sizeof(x)/sizeof(x[0]))
#include <time.h>
#include <sys/timeb.h>
#include <stdarg.h>


class Clog  
{
public:
	Clog();
	virtual ~Clog();
public:
	//static void Lock(CRITICAL_SECTION *l);
	//static void Unlock(CRITICAL_SECTION *l) ;
	static void LogV(const char *pszFmt,va_list argp);
	static void Log(const char *pszFmt,...);
	/////////////////////////////////////////
	static const char *logfilename1;
	static const char *logfilename2;
	static char logstr[16000];
	static char datestr[16];
	static char timestr[16];
	static char mss[4];
	//static CRITICAL_SECTION cs_log;
	static FILE *flog;
	static char logstr2[16000];

};

#endif // !defined(AFX_LOG_H__3FAFFDFB_EC83_4E94_A1F2_76D25188FA90__INCLUDED_)
