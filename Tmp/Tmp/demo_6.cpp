#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>

#pragma comment (lib, "Ws2_32.lib")

int  main6(int argc, char **argv)
{
	WORD wVersion;
	WSADATA WSAData;
	wVersion=MAKEWORD(2,2);
	WSAStartup(wVersion,&WSAData);
	struct addrinfo hints;
	struct addrinfo *res, *cur;
	int ret;
	struct sockaddr_in *addr;
	char m_ipaddr[16];

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;     /* Allow IPv4 */
	hints.ai_flags = AI_PASSIVE;/* For wildcard IP address */
	hints.ai_protocol = 0;         /* Any protocol */
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo("www.baidu.com", NULL,&hints,&res);

	if (ret == -1) {
		perror("getaddrinfo");
		exit(1);
	}
	
	std::string strip;

	for (cur = res; cur != NULL; cur = cur->ai_next) {
		addr = (struct sockaddr_in *)cur->ai_addr;
		sprintf(m_ipaddr, "%d.%d.%d.%d",
			(*addr).sin_addr.S_un.S_un_b.s_b1,
			(*addr).sin_addr.S_un.S_un_b.s_b2,
			(*addr).sin_addr.S_un.S_un_b.s_b3,
			(*addr).sin_addr.S_un.S_un_b.s_b4);
		strip.append(m_ipaddr);
		
	}
	std::cout << strip << std::endl;
	freeaddrinfo(res);
	system("pause");
	return 0;
}