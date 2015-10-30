#include "VirualCheck.h"
#include "..\..\..\VS2008\VC\include\tchar.h"
#include "setupapi.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment(lib, "Setupapi.lib")

#define IOCTL_STORAGE_QUERY_PROPERTY CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)  
#define BUF_SIZE 512

bool CVirualCheck::IsSandboxed()
{
	HANDLE hPhysicalDriveIOCTL = 0;  
	int j = 0,k = 0;  
	char szModel[128],szBuffer[128];  

	char *szDrives[] = {  
		"qemu",  
		"virtual",  
		"vmware", 
		"vbox",
		NULL  
	};  

	hPhysicalDriveIOCTL = CreateFile ("\\\\.\\PhysicalDrive0", 0,FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, 0, NULL);
	if (hPhysicalDriveIOCTL != INVALID_HANDLE_VALUE)  
	{  
		STORAGE_PROPERTY_QUERY query;
		DWORD cbBytesReturned = 0;
		memset ((void *) & query, 0, sizeof (query));  
		query.PropertyId = StorageDeviceProperty;  
		memset (szBuffer, 0, sizeof (szBuffer));  
		memset (szModel, 0, sizeof (szModel));  

		if (DeviceIoControl(hPhysicalDriveIOCTL, IOCTL_STORAGE_QUERY_PROPERTY,& query,sizeof (query),& szBuffer,sizeof (szBuffer),& cbBytesReturned, NULL))
		{   
			STORAGE_DEVICE_DESCRIPTOR *descrip = (STORAGE_DEVICE_DESCRIPTOR*)&szBuffer;  
			int pos = descrip->ProductIdOffset;  
			int m = 0;  
			for(int g = pos;szBuffer[g] != '\0';g++)
			{  
				szModel[m++] = szBuffer[g];  
			}  

			CharLowerBuff(szModel,strlen(szModel));  

			for (int i = 0; i < (sizeof(szDrives)/sizeof(LPSTR)) - 1; i++ ) 
			{  
				if (szDrives[i][0] != 0) 
				{  
					if(strstr(szModel,szDrives[i]))  
						return TRUE;  
				}  
			}  
		}  
		CloseHandle (hPhysicalDriveIOCTL);  
	}  
	return FALSE;  
}

bool CVirualCheck::IsInsideVMWare()
{
	bool rc = true;

	__try
	{
		__asm
		{
			push   edx
				push   ecx
				push   ebx
				mov    eax, 'VMXh'
				mov    ebx, 0  // 将ebx设置为非幻数’VMXH’的其它值
				mov    ecx, 10 // 指定功能号，用于获取VMWare版本，当它为0x14时用于获取VMware内存大小
				mov    edx, 'VX' // 端口号
				in     eax, dx // 从端口dx读取VMware版本到eax
				//若上面指定功能号为0x14时，可通过判断eax中的值是否大于0，若是则说明处于虚拟机中
				cmp    ebx, 'VMXh' // 判断ebx中是否包含VMware版本’VMXh’，若是则在虚拟机中
				setz   [rc] // 设置返回值
				pop    ebx
				pop    ecx
				pop    edx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)  //如果未处于VMware中，则触发此异常
	{
		rc = false;
	}

	return rc;
}

char* CVirualCheck::GetHostIP()
{
	int ret;
	char cHost[256];

	ret = gethostname(cHost,256);
	if (ret != 0)
	{
		ret = GetLastError();
		return NULL;
	}

	hostent *pHost = gethostbyname(cHost);
	in_addr addr;

	char *p = pHost->h_addr_list[0];
	memcpy(&addr.S_un.S_addr,p,pHost->h_length);

	return inet_ntoa(addr);
}

void CVirualCheck::GetGraphicInfo(DWORD *grathic_count, std::string &grathic_name)
{
	HKEY key_serv;
	HKEY key_enum;
	HKEY key;
	HKEY key2;
	LONG result;
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &key_serv);
	if (result != ERROR_SUCCESS)
		return;
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum"), 0, KEY_READ, &key_enum);
	if (result != ERROR_SUCCESS)
		return;

	int i = 0, count = 0;
	DWORD size = 0, type = 0;
	while (++i)
	{
		Sleep(5);
		size = BUF_SIZE;
		TCHAR name[BUF_SIZE] = {0};
		result = RegEnumKeyEx(key_serv, i , name, &size, NULL, NULL, NULL, NULL);
		if (result != ERROR_SUCCESS)
			return;
		RegOpenKeyEx(key_serv, name, 0, KEY_READ, &key);
		if (result != ERROR_SUCCESS)
		{
			RegCloseKey(key_serv);
			return;
		}

		size = BUF_SIZE;
		result = RegQueryValueEx(key, TEXT("Group"), 0, &type, (LPBYTE)name, &size);
		if (result == ERROR_FILE_NOT_FOUND)
		{
			RegCloseKey(key);
			continue;
		}

		if (_tcscmp(TEXT("Video"), name) != 0)
		{
			RegCloseKey(key);
			continue;
		}

		result = RegOpenKeyEx(key, TEXT("Enum"), 0, KEY_READ, &key2);
		if (result != ERROR_SUCCESS)
			return;
		RegCloseKey(key);
		key = key2;
		size = sizeof(count);
		result = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);
		*grathic_count = count;
		for (int j = 0; j < count; ++j)
		{
			TCHAR sz[BUF_SIZE] = {0};
			TCHAR tmpname[64] = {0};
			wsprintf(tmpname, TEXT("%d"), j);
			size = sizeof(sz);
			result = RegQueryValueEx(key, tmpname, 0, &type, (LPBYTE)sz, &size);

			result = RegOpenKeyEx(key_enum, sz, 0, KEY_READ, &key2);
			if (result != ERROR_SUCCESS)
			{
				RegCloseKey(key_enum);
				return;
			}

			size = sizeof(sz);
			result = RegQueryValueEx(key, TEXT("FriendlyName"), 0, &type, (LPBYTE)sz, &size);
			if (result == ERROR_FILE_NOT_FOUND)
			{
				size = sizeof(sz);
				RegQueryValueEx(key2, TEXT("DeviceDesc"), 0, &type, (LPBYTE)sz, &size);
				grathic_name.append(sz);
			}
			RegCloseKey(key2);
			key2 = NULL;
		}
		RegCloseKey(key);
		key = NULL;
		break;
	}
}

std::vector<std::string> CVirualCheck::GetGraphicsType()
{
	std::vector<std::string> vct_graphics;
	DWORD dwType = 0;
	DWORD dwBuflen = 0;
	PUCHAR pBuf = NULL;

	GUID guidScsiRaid = {0x4d36e968,0xe325,0x11CE, {0xBF,   0xC1,   0x08,   0x00,   0x2B,   0xE1,   0x03,   0x18}};

	HDEVINFO hScsi = SetupDiGetClassDevs(&guidScsiRaid, NULL, NULL, DIGCF_PRESENT);

	SP_DEVINFO_DATA adapterData;
	adapterData.cbSize = sizeof(SP_DEVINFO_DATA);

	for(DWORD dwIndex = 0; SetupDiEnumDeviceInfo(hScsi, dwIndex, &adapterData); dwIndex++)
	{
		SetupDiGetDeviceRegistryProperty(
			hScsi, 
			&adapterData, 
			SPDRP_DEVICEDESC,
			&dwType,
			NULL,
			0,
			&dwBuflen
			);

		if(ERROR_INSUFFICIENT_BUFFER == GetLastError())
		{
			pBuf = (PUCHAR)malloc(dwBuflen);
			if(SetupDiGetDeviceRegistryProperty(
				hScsi, 
				&adapterData, 
				SPDRP_DEVICEDESC,
				&dwType,
				pBuf,
				dwBuflen,
				NULL
				))
			{
				vct_graphics.push_back((char *)pBuf);
			}

			free(pBuf);
			pBuf = NULL;
		}
	}

	SetupDiDestroyDeviceInfoList(hScsi);
	return vct_graphics;
}

bool CVirualCheck::IsVirtualGraphicCard()
{
	std::vector<std::string> vct_graphics;
	DWORD dwType = 0;
	DWORD dwBuflen = 0;
	PUCHAR pBuf = NULL;

	char* judge[] = {"VMware",
		"VBox"};

	GUID guidScsiRaid = {0x4d36e968,0xe325,0x11CE, {0xBF,   0xC1,   0x08,   0x00,   0x2B,   0xE1,   0x03,   0x18}};

	HDEVINFO hScsi = SetupDiGetClassDevs(&guidScsiRaid, NULL, NULL, DIGCF_PRESENT);

	SP_DEVINFO_DATA adapterData;
	adapterData.cbSize = sizeof(SP_DEVINFO_DATA);

	for(DWORD dwIndex = 0; SetupDiEnumDeviceInfo(hScsi, dwIndex, &adapterData); dwIndex++)
	{
		SetupDiGetDeviceRegistryProperty(
			hScsi, 
			&adapterData, 
			SPDRP_DEVICEDESC,
			&dwType,
			NULL,
			0,
			&dwBuflen
			);

		if(ERROR_INSUFFICIENT_BUFFER == GetLastError())
		{
			pBuf = (PUCHAR)malloc(dwBuflen);
			if(SetupDiGetDeviceRegistryProperty(
				hScsi, 
				&adapterData, 
				SPDRP_DEVICEDESC,
				&dwType,
				pBuf,
				dwBuflen,
				NULL
				))
			{
				vct_graphics.push_back((char *)pBuf);
				for (int i = 0; i < sizeof(judge) / sizeof(LPSTR) - 1; ++i)
				{
					if (strstr((char *)pBuf, judge[i]))
					{
						free(pBuf);
						pBuf = NULL;
						return true;
					}
				}
			}

			free(pBuf);
			pBuf = NULL;
		}
	}

	SetupDiDestroyDeviceInfoList(hScsi);
	
	return false;
}

bool CVirualCheck::IsVirtualPC()
{
	return (CVirualCheck::IsInsideVMWare() || CVirualCheck::IsSandboxed() || CVirualCheck::IsVirtualGraphicCard());
}

