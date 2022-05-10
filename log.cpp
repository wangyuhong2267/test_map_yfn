// log.cpp: implementation of the Clog class.
//
//////////////////////////////////////////////////////////////////////

#include "log.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char *Clog::logfilename1="mylog1.log";
const char *Clog::logfilename2="mylog2.log";
char Clog::logstr[16000];
char Clog::datestr[16];
char Clog::timestr[16];
char Clog::mss[4];
//CRITICAL_SECTION Clog::cs_log;
FILE *Clog::flog =NULL;
char Clog::logstr2[16000];
/////////////////////////////////////
Clog::Clog()
{


}

Clog::~Clog()
{

}

/*void Clog::Lock(CRITICAL_SECTION *l) 
{
    //pthread_mutex_lock(l);
}
void Clog::Unlock(CRITICAL_SECTION *l) 
{
    //pthread_mutex_unlock(l);
}*/

void Clog::LogV(const char *pszFmt,va_list argp) 
{
	
    struct tm *now;
    struct timeb tb;
 
    if (NULL==pszFmt||0==pszFmt[0]) return;
    if (-1==_vsnprintf(logstr,ARRSIZE(logstr),pszFmt,argp)) logstr[ARRSIZE(logstr)-1]=0;
    ftime(&tb);
    now=localtime(&tb.time);
    sprintf(datestr,"%04d-%02d-%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday);
    sprintf(timestr,"%02d:%02d:%02d",now->tm_hour     ,now->tm_min  ,now->tm_sec );
    sprintf(mss,"%03d",tb.millitm);
    printf("%s %s.%s %s\n",datestr,timestr,mss,logstr);
    //flog=fopen(logfilename1,"a");
	//flog=fopen(logfilename1,"wb+");
	//printf("Clog::flog=%d\n",Clog::flog);
    if (NULL!=Clog::flog) 
	{
        fprintf(Clog::flog,"%s %s.%s %s \n",datestr,timestr,mss,logstr);
		fflush(Clog::flog);


		
		/*sprintf(logstr2,"%s %s.%s %s\n",datestr,timestr,mss,logstr);
		size_t strlen_write = strlen(logstr2);
		//printf("strlen_write=%d,%s\n",strlen_write,logstr2);
		size_t len = fwrite(logstr2,strlen_write,1,Clog::flog);*/
		
		//printf("len=%d\n",len);
        /*if (ftell(flog)>MAXLOGSIZE) 
		{
            fclose(flog);
            if (rename(logfilename1,logfilename2)) 
			{
                remove(logfilename2);
                rename(logfilename1,logfilename2);
            }
        } 
		else 
		{
            fclose(flog);
        }*/
    }
}
void Clog::Log(const char *pszFmt,...) 
{
	
    va_list argp;
 
    //Lock(&cs_log);
    va_start(argp,pszFmt);
    LogV(pszFmt,argp);
    va_end(argp);
    //Unlock(&cs_log);
}

