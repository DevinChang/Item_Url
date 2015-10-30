#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include "openssl\bn.h"
#include "openssl\bio.h"
#include "openssl\ssl.h"
#include "openssl\err.h"
#include "openssl\rand.h"

#pragma comment (lib, "Ws2_32.lib") // error,没引入静态库，导致链接错误
#pragma comment (lib, "libeay32.lib")
#pragma comment (lib, "ssleay32.lib")

#define CHK_SSL(err, s) if (err == -1) {perror(s);} 
#define DebugMsg printf 

int SSLSocket(std::string domain, int port, const char *targetIP)
{
	
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	SOCKET socketfd = socket(AF_INET, SOCK_STREAM, 0);
	CHK_SSL(socketfd, "Create Socket Error!");
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(targetIP);
	

	int err = connect(socketfd, (struct sockaddr *) (&addr), sizeof(struct sockaddr));
	CHK_SSL(err, "Connect Socket Error!");

	SSL *ssl;
	SSL_CTX *ctx;
	// SSL initialize
	SSL_library_init();
	SSL_load_error_strings();
	ctx = SSL_CTX_new(SSLv23_client_method());
	

	ssl = SSL_new(ctx);
	if (ssl == NULL) 
	{
		DebugMsg("SSL new failed!");
		return -1;
	}

	// link socket & SSL
	int ret = SSL_set_fd(ssl, socketfd);
	if (ret == 0) 
	{
		DebugMsg("SSL link socket failed!");
		return -1;
	}

	RAND_poll();
	while (RAND_status() == 0) 
	{
		unsigned short rand_ret = rand() % 65536;
		RAND_seed(&rand_ret, sizeof(rand_ret));
	}

	// SSL connect
	ret = SSL_connect(ssl);
	if (ret != 1) 
	{
		DebugMsg("SSL connect failed!");
		return -1;
	}

	char get_request[1024] = {0};
	std::string request = "www.baidu.com";
	sprintf(get_request, "GET / HTTP/1.1\r\nAccept: */*\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1) Gecko Firefox\r\nConnection: Close\r\nHost: %s\r\n\r\n", domain);

	int total_send = 0;
	int request_len = strlen(get_request);
	while(request_len > total_send)
	{
		int rev = SSL_write(ssl, get_request + total_send, request_len - total_send);
		if (rev == -1)
		{
			return -1;
		}
		total_send += rev;
	}

	int responseLen = 0;
	int i = 0;
	char buffer[8] = {0};
	char returnBuffer[1024] = {0};
	int p = 0;
	while ((responseLen = SSL_read(ssl, buffer, 1)) == 1 && p<1024) 
	{
		returnBuffer[p] = buffer[0];
		p++;
		if (i < 4) 
		{
			if (buffer[0] == '\r' || buffer[0] == '\n')
				i++;
			else
				i = 0;
		}
	}

	if (SSL_shutdown(ssl) != 1)
	{
		return -1;
	}
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	ERR_free_strings();
	closesocket(socketfd);
	WSACleanup();
}


int main(int argc, char **argv)
{
	//SSLSocket();
	int ret = SSLSocket("www.baidu.com", 443, "119.75.218.70");
	system("pause");
	return 0;
}