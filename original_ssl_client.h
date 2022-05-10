

#ifndef original_ssl_client_h
#define original_ssl_client_h

#pragma once
#include "const.h"
#include <iostream>
#include <stdio.h>  

#include <sys/socket.h>

#include <openssl/ssl.h>  
#include <openssl/rand.h>  
#include <openssl/bio.h>  
#include <openssl/err.h>  
#include <openssl/x509.h> 

//using namespace std;


class original_ssl_client
{
public:
    original_ssl_client()   
    {
        m_pctx          = NULL;
        m_sockfd        = -1;
        m_phost_info    = NULL;
        m_pssl          = NULL;
        memset(m_recv_buffer,0,MAX_BUFFER_RECEIVE);

    }
    ~original_ssl_client() 
    {

    }

private:
    //SSL_METHOD*       m_pmeth;
    SSL_CTX *       m_pctx;
    int          m_sockfd;
    sockaddr_in     m_server_addr;
    struct hostent* m_phost_info;
    SSL*            m_pssl;
    enum
    {
        MAX_BUFFER_RECEIVE = 1024,
    };

    char            m_recv_buffer[MAX_BUFFER_RECEIVE];

public:
	void Hex2Str( const char *sSrc,  char *sDest, int nSrcLen )
	{
		int  i;
		char szTmp[3];
  
		for( i = 0; i < nSrcLen; i++ )
		{
			sprintf( szTmp, "%02x", (unsigned char) sSrc[i] );
			memcpy( &sDest[i * 2], szTmp, 2 );
		}
		return ;
	}
    int ssl_read_data(char *chstr_dest2){
        char buf [293];
        memset(buf,0,sizeof(buf));
        int err = SSL_read (m_pssl, buf, sizeof(buf));
        printf("ssl_read_data,err=%d\n",err);
        
        for (int st=0;st<err;st++)
        {
            printf("%x, ",buf[st]);
        }
		char chstr_dest[65];
		memset(chstr_dest, 0, sizeof(chstr_dest));
		Hex2Str(&buf[6],chstr_dest,  32);
		printf("ssl_read_data,chstr_dest=%s\n",chstr_dest);
		memcpy(chstr_dest2,chstr_dest,64);
		//chstr_dest2 = chstr_dest;
		return err;
    }
    //
    void close2()
    {
        // �ر�SSL�׽���
        SSL_shutdown(m_pssl);

        // �ͷ�SSL�׽���
        SSL_free(m_pssl);

        // �ͷ�SSL�Ự����
        SSL_CTX_free(m_pctx);

        // �ر�tcp �׽���
        close(m_sockfd);

    }

    // ��ʼ��ssl�⣬Windows�³�ʼ��WinSock
    void init_openssl() 
    { 

//    #ifdef _WIN32 WSADATA wsaData;
//        WSADATA wsaData;
//        WSAStartup(MAKEWORD(2, 2), &wsaData);
//    #endif

        SSL_library_init(); 
        ERR_load_BIO_strings(); 
        SSL_load_error_strings(); 
        OpenSSL_add_all_algorithms();
    }

    //
    bool init_tcp_connect(const char* host, int port) 
    { 
        if ( !host )
            return false;

        struct hostent *hp; 
        //struct sockaddr_in m_server_addr; 
        if (!(hp = gethostbyname(host)))        // �������� 
            return false;

        memset(&m_server_addr, 0, sizeof(m_server_addr));
        m_server_addr.sin_addr  = *(struct in_addr*)hp->h_addr_list[0];
        m_server_addr.sin_family = AF_INET;
        m_server_addr.sin_port  = htons(port);
        if ((m_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        {
            cout<<"Could not get Socket"<<endl;
            return false;
        } 

        if (connect(m_sockfd, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)) != 0) 
        { 
            return false;
        } 

        return true;
    }

    // ����SSL Context 
    SSL_CTX* init_ssl_context( const char* clientcert, /* �ͻ��˵�֤�� */ const char* clientkey, /* �ͻ��˵�Key */ const char* keypwd, /* �ͻ���Key������, ����еĻ� */ const char* cacert) /* ������CA֤�� ����еĻ� */ 
    { 
        // set up the ssl context 
        m_pctx = SSL_CTX_new((SSL_METHOD*)TLSv1_client_method()); 
        if (!m_pctx) { return NULL; } 

        // Ҫ��У��Է�֤��
        //SSL_CTX_set_verify(m_pctx,SSL_VERIFY_PEER |SSL_VERIFY_CLIENT_ONCE , myssl_verify_callback);

        // certificate 
        if (clientcert && SSL_CTX_use_certificate_file(m_pctx, clientcert, SSL_FILETYPE_PEM) <= 0) 
            { return NULL; } 

        // key
        if ( clientkey )
        {
            SSL_CTX_set_default_passwd_cb_userdata(m_pctx,(void*)keypwd);

            if (SSL_CTX_use_PrivateKey_file(m_pctx, clientkey, SSL_FILETYPE_PEM) <= 0) 
            { return NULL; } 

            // make sure the key and certificate file match 
            if (SSL_CTX_check_private_key(m_pctx) == 0) 
            { return NULL; } 
        }


        // load ca if exist
        if ( cacert ) 
        { 
            if (!SSL_CTX_load_verify_locations(m_pctx, cacert, NULL)) 
                { return NULL; } 
        } 

        return m_pctx; 
    }

    // ʵ��SSL���֣�����SSL���� 
    SSL* ssl_connect( ) 
    { 
        m_pssl = SSL_new(m_pctx); 
        //BIO *bio = BIO_new_socket(m_sockfd, BIO_NOCLOSE);
        //SSL_set_bio(m_pssl, bio, bio);
        SSL_set_fd(m_pssl,m_sockfd);
        int ret = SSL_connect(m_pssl);
        if ( ret <= 0)
        {
            int nErr = SSL_get_error(m_pssl,ret);   // SSL_ERROR_SSL 1,  SSL_ERROR_SYSCALL 5
			printf("nErr=%d\n", nErr);
            char err_msg[1024];
            ERR_error_string_n(ERR_get_error(), err_msg, sizeof(err_msg));
            printf("%s\n", err_msg);

            ERR_print_errors_fp(stderr);
            std::cout<<ssl_error_string().c_str()<<endl;
            return NULL; 
        }
        else{
            printf("ssl_connect,conncted success!\n");
        }

        return m_pssl; 
    }

    // ��֤������֤��
    // ����Ҫ��֤��������֤����Ч�����Ҫ��֤������֤���CommonName(CN)������ 
    // ʵ��Ҫ���ӵķ���������һ�� 
    bool verify_connection(const char* peername) 
    { 
        // ��ȡУ����
        int result = SSL_get_verify_result(m_pssl);
        if (result != X509_V_OK && result != X509_V_ERR_CERT_UNTRUSTED && result != X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY) 
        { 
            fprintf(stderr, "WARNING! ssl verify failed: %d \n", result);
            std::cout<<ssl_error_string().c_str()<<endl;
            return false;
        } 

//      X509 *peer; 
//      char peer_CN[256] = {0}; 
//      peer = SSL_get_peer_certificate(m_pssl); 
//      X509_NAME_get_text_by_NID(X509_get_subject_name(peer), NID_commonName, peer_CN, 255); 
//      if (strcmp(peer_CN, peername) != 0) 
//      { 
//          fprintf(stderr, "WARNING! Server Name Doesn't match, got: %s, required: %s", peer_CN, peername);
//      } 

        return true;
    }

    std::string ssl_error_string( )
    {
        //SSL_get_error();
        unsigned long ulErr = ERR_get_error();  // ��ȡ�����
        char szErrMsg[1024] = {0};
        char *pTmp = NULL;
        pTmp = ERR_error_string(ulErr,szErrMsg); //
		printf("ssl_error_string,pTmp=%s\n",pTmp);
        return szErrMsg;
    }

    void ssl_send_keyinput_msg( )
    {
        while ( true)
        {
            sleep(3);
            
            if( true )
            {
                char szInput[100] = {"5555555"};
                cout<<"commond: "<<endl;
                cin.getline(szInput,sizeof(szInput),'\n');
                if ( strcmp(szInput,"exit") == 0 )
                    break;
                printf("ssl_send_keyinput_msg,aaaaaaaaa\n");
                //char token[]        = "b810a35c472c28a8a533468a6ca270d6750b31c5d88a063c43c4bf6c47d2b338";
                char token[]        = "b36b5ee2d6a3c786653708c1f124691d450129e45321d5d28733abd016fa7183";
                char format[]       = "{\"aps\":{\"alert\":\"%s\",\"badge\":1}}";
                char payload[256]   = {};
                sprintf(payload,format,szInput);
                printf("ssl_send_keyinput_msg,bbbbbbbb\n");
                int ret = pushMessage(token, payload);
                cout<<"push ret["<<ret<<"]"<<endl;
            }
            
            recv_message();
        }
    }
    void ssl_send_keyinput_msg2( )
    {
        
                char szInput[100] = {"5555555"};
                cout<<"commond: "<<endl;
                cin.getline(szInput,sizeof(szInput),'\n');
                if ( strcmp(szInput,"exit") == 0 )
                    return;
                printf("ssl_send_keyinput_msg,aaaaaaaaa\n");
                //char token[]        = "b810a35c472c28a8a533468a6ca270d6750b31c5d88a063c43c4bf6c47d2b338";
                char token[]        = "b36b5ee2d6a3c786653708c1f124691d450129e45321d5d28733abd016fa7183";
                //char format[]       = "{\"aps\":{\"alert\":\"%s\",\"badge\":1}}";
                char format[]       = "{\"aps\":{\"alert\":\"%s\",\"badge\":1,\"sound\":\"default\",\"content-available\":1}}";
                char payload[256]   = {};
                sprintf(payload,format,szInput);
                printf("ssl_send_keyinput_msg,bbbbbbbb\n");
                int ret = pushMessage(token, payload);
                cout<<"push ret["<<ret<<"]"<<endl;
           // recv_message();
        
    }



    int pushMessage(const char * token, const char * payload)
    {
        char tokenBytes[32];
        char message[293];
        unsigned long msgLength;

        token2bytes( token, tokenBytes );
        unsigned short payloadLength    = strlen( payload );
        char * pointer = message;
        unsigned short networkTokenLength   = htons( (unsigned short)32 );
        unsigned short networkPayloadLength = htons( (unsigned short)payloadLength );
        // command
        //*/
        unsigned char command           = 0;
        memcpy(pointer, &command, sizeof(unsigned char));
        pointer += sizeof(unsigned char);
        /*/
        unsigned char command           = 1;
        memcpy(pointer, &command, sizeof(unsigned char));
        pointer += sizeof(unsigned char);
        // identityfer
        boost::uint32_t identityfer = 1;
        memcpy(pointer, &identityfer, 4);  
        pointer += 4;
        // expiry
        boost::uint32_t tExpiry = time(NULL) + 24*3600;
        memcpy(pointer, &tExpiry, 4);  
        pointer += 4;
        //*/

        // token len
        memcpy(pointer, &networkTokenLength, sizeof(unsigned short));
        pointer += sizeof(unsigned short);
        // token
        memcpy(pointer, tokenBytes, sizeof(tokenBytes));
        pointer += 32;
        // payload len
        memcpy(pointer, &networkPayloadLength, sizeof(unsigned short));
        pointer += sizeof(unsigned short);
        // payload
        memcpy(pointer, payload, payloadLength);
        pointer += payloadLength;
        // clac len
        msgLength = pointer - message;
        return SSL_write( m_pssl, message, (int)msgLength );
    }

    void recv_message( )
    {
        int nRealRead = SSL_read(m_pssl,m_recv_buffer,MAX_BUFFER_RECEIVE);
        if ( nRealRead <= 0 )
        {
            int nErr = SSL_get_error(m_pssl, nRealRead);    // SSL_ERROR_SSL 1,  SSL_ERROR_SYSCALL 5
			printf("recv_message,nErr=%d\n", nErr);
            char err_msg[1024];
            ERR_error_string_n(ERR_get_error(), err_msg, sizeof(err_msg));
            printf("recv_message,%s\n", err_msg);
        }
        else
        {
            std::cout<<m_recv_buffer<<endl;
            memset(m_recv_buffer,0,MAX_BUFFER_RECEIVE);
        }
    }

    void token2bytes(const char *token, char *bytes)
    {
        int val;  
        while (*token) 
        {  
            sscanf(token, "%2x", &val);  
            *(bytes++) = (char)val;  
            token += 2;  
            while (*token == ' ') {  
                ++token;                // skip space
            }  
        }  
    } 

};

#endif





