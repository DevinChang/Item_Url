#include <windows.h>
#include <wincon.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Nb30.h>

#pragma comment(lib,"netapi32.lib")  

int GetMac(char * mac)     
{     
	NCB ncb;
	typedef struct _ASTAT_
	{
		ADAPTER_STATUS   adapt;
		NAME_BUFFER   NameBuff   [30];
	}ASTAT,*PASTAT;

	ASTAT Adapter;   

	typedef struct _LANA_ENUM
	{
		UCHAR   length;
		UCHAR   lana[MAX_LANA];
	}LANA_ENUM;

	LANA_ENUM lana_enum;    
	UCHAR uRetCode;
	memset(&ncb, 0, sizeof(ncb));
	memset(&lana_enum, 0, sizeof(lana_enum));    
	ncb.ncb_command = NCBENUM;
	ncb.ncb_buffer = (unsigned char *)&lana_enum;
	ncb.ncb_length = sizeof(LANA_ENUM);
	uRetCode = Netbios(&ncb);

	if(uRetCode != NRC_GOODRET)     
		return uRetCode;     

	for(int lana=0; lana<lana_enum.length; lana++)     
	{
		ncb.ncb_command = NCBRESET;
		ncb.ncb_lana_num = lana_enum.lana[lana];
		uRetCode = Netbios(&ncb); 
		if(uRetCode == NRC_GOODRET)
			break; 
	}

	if(uRetCode != NRC_GOODRET)
		return uRetCode;     

	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBASTAT;
	ncb.ncb_lana_num = lana_enum.lana[0];
	strcpy((char*)ncb.ncb_callname, "*");
	ncb.ncb_buffer = (unsigned char *)&Adapter;
	ncb.ncb_length = sizeof(Adapter);
	uRetCode = Netbios(&ncb);

	if(uRetCode != NRC_GOODRET)
		return uRetCode;

	sprintf(mac,"%02X-%02X-%02X-%02X-%02X-%02X",
		Adapter.adapt.adapter_address[0],
		Adapter.adapt.adapter_address[1],
		Adapter.adapt.adapter_address[2],
		Adapter.adapt.adapter_address[3],
		Adapter.adapt.adapter_address[4],
		Adapter.adapt.adapter_address[5]);

	return 0;   
} 


int main2(int argc, char* argv[])
{
	char   mac[200]; 
	GetMac(mac);   
	printf("The Mac Address is : %s   \n",mac);        

	system("pause");
	return 0;
}