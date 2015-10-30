#include "StdAfx.h"
#include "WinInfo.h"



CWmiInfo::CWmiInfo(void)  
{  
	m_pWbemSvc=NULL;  
	m_pWbemLoc=NULL;  
	m_pEnumClsObj = NULL;
	InitWmi();
}  

CWmiInfo::~CWmiInfo(void)  
{
	ReleaseWmi();
	m_pWbemSvc=NULL;  
	m_pWbemLoc=NULL;  
	m_pEnumClsObj = NULL;  
}  

HRESULT CWmiInfo::InitWmi()  
{  
	HRESULT hr;  

	//һ����ʼ��COM���  
	//��ʼ��COM  
	hr=::CoInitializeEx(0,COINIT_MULTITHREADED);  
	if (SUCCEEDED(hr) || RPC_E_CHANGED_MODE == hr)  
	{  
		//���ý��̵İ�ȫ���𣬣�����COM���ʱ�ڳ�ʼ��COM֮��Ҫ����CoInitializeSecurity���ý��̰�ȫ���𣬷���ᱻϵͳʶ��Ϊ������  
		hr=CoInitializeSecurity(NULL,  
			-1,  
			NULL,                     
			NULL,  
			RPC_C_AUTHN_LEVEL_DEFAULT,  
			RPC_C_IMP_LEVEL_IMPERSONATE,  
			NULL,  
			EOAC_NONE,  
			NULL);  
		//VERIFY(SUCCEEDED(hr));  

		//��������һ��WMI�����ռ�����  
		//����һ��CLSID_WbemLocator����  
		hr=CoCreateInstance(CLSID_WbemLocator,  
			0,  
			CLSCTX_INPROC_SERVER,  
			IID_IWbemLocator,  
			(LPVOID*)&m_pWbemLoc);  
		VERIFY(SUCCEEDED(hr));  

		//ʹ��m_pWbemLoc���ӵ�"root\cimv2"������m_pWbemSvc��ָ��  
		hr=m_pWbemLoc->ConnectServer(CComBSTR(L"ROOT\\CIMV2"),  
			NULL,  
			NULL,  
			0,  
			NULL,  
			0,  
			0,  
			&m_pWbemSvc);  
		VERIFY(SUCCEEDED(hr));  

		//��������WMI���ӵİ�ȫ��  
		hr=CoSetProxyBlanket(m_pWbemSvc,  
			RPC_C_AUTHN_WINNT,  
			RPC_C_AUTHZ_NONE,  
			NULL,  
			RPC_C_AUTHN_LEVEL_CALL,  
			RPC_C_IMP_LEVEL_IMPERSONATE,  
			NULL,  
			EOAC_NONE);  
		VERIFY(SUCCEEDED(hr));  

	}  
	return(hr);  
}  

HRESULT CWmiInfo::ReleaseWmi()  
{  
	HRESULT hr;  

	if (NULL != m_pWbemSvc)  
	{  
		hr=m_pWbemSvc->Release();  
	}  
	if (NULL != m_pWbemLoc)  
	{  
		hr=m_pWbemLoc->Release();  
	}  
	if (NULL != m_pEnumClsObj)  
	{  
		hr=m_pEnumClsObj->Release();  
	}  

	::CoUninitialize();  

	return(hr);  
}  

BOOL CWmiInfo::GetSingleItemInfo(std::string ClassName,std::string ClassMember,std::vector<std::string> &chRetValue)  
{  
	USES_CONVERSION;  

	CComBSTR query("SELECT * FROM ");  
	VARIANT vtProp;  
	ULONG uReturn;  
	HRESULT hr;
	BOOL bRet = FALSE;  

	if (NULL != m_pWbemSvc)  
	{  
		//��ѯ��ClassName�е������ֶ�,���浽m_pEnumClsObj��  
		query+=CComBSTR(ClassName.c_str());  
		hr=m_pWbemSvc->ExecQuery(CComBSTR("WQL"),query,WBEM_FLAG_FORWARD_ONLY|WBEM_FLAG_RETURN_IMMEDIATELY,
			0,&m_pEnumClsObj);
		if (SUCCEEDED(hr))  
		{  
			//��ʼ��vtPropֵ  
			VariantInit(&vtProp);  
			uReturn=0;  

			//���شӵ�ǰλ����ĵ�һ������m_pWbemClsObj��  
			do
			{
				hr=m_pEnumClsObj->Next(WBEM_INFINITE,1,&m_pWbemClsObj,&uReturn);

				if (SUCCEEDED(hr) && uReturn>0)
				{
					//��m_pWbemClsObj���ҳ�ClassMember��ʶ�ĳ�Ա����ֵ,�����浽vtProp������
					CString str;
					hr=m_pWbemClsObj->Get(CComBSTR(ClassMember.c_str()),0,&vtProp,0,0);  
					if (SUCCEEDED(hr))
					{  
						VariantToString(&vtProp,str); 
						chRetValue.push_back((LPCTSTR)str);
						VariantClear(&vtProp);//���vtProp  
						bRet = TRUE;
					}  
					if(NULL != m_pWbemClsObj)   
					{  
						hr=m_pWbemClsObj->Release();  
						m_pWbemClsObj = NULL;  
					}  
				}
			} while(SUCCEEDED(hr) && uReturn>0); 
		}  
	}  
	if(NULL != m_pEnumClsObj)   
	{  
		hr=m_pEnumClsObj->Release();  
		m_pEnumClsObj = NULL;  
	} 
	return bRet;  
}  


void CWmiInfo::VariantToString(const LPVARIANT pVar,CString &chRetValue) const  
{  
	USES_CONVERSION;  

	CComBSTR HUGEP* pBstr;  
	BYTE HUGEP* pBuf;  
	LONG low,high,i;  
	HRESULT hr;  

	switch(pVar->vt)  
	{  
	case VT_BSTR:  
		{  
			chRetValue=W2T(pVar->bstrVal);  
		}  
		break;  
	case VT_BOOL:  
		{  
			if(VARIANT_TRUE==pVar->boolVal)   
				chRetValue="��";  
			else  
				chRetValue="��";  
		}  
		break;  
	case VT_I4:  
		{  
			chRetValue.Format(_T("%d"),pVar->lVal);  
		}  
		break;  
	case VT_UI1:  
		{  
			chRetValue.Format(_T("%d"),pVar->bVal);  
		}  
		break;  
	case VT_UI4:  
		{  
			chRetValue.Format(_T("%d"),pVar->ulVal);  
		}  
		break;  

	case VT_BSTR|VT_ARRAY:  
		{  
			hr=SafeArrayAccessData(pVar->parray,(void HUGEP**)&pBstr);  
			hr=SafeArrayUnaccessData(pVar->parray);  
			chRetValue=W2T(pBstr->m_str);  
		}  
		break;  

	case VT_I4|VT_ARRAY:  
		{  
			SafeArrayGetLBound(pVar->parray,1,&low);   
			SafeArrayGetUBound(pVar->parray,1,&high);  

			hr=SafeArrayAccessData(pVar->parray,(void HUGEP**)&pBuf);  
			hr=SafeArrayUnaccessData(pVar->parray);  
			CString strTmp;  
			high=min(high,MAX_PATH*2-1);  
			for(i=low;i<=high;++i)  
			{  
				strTmp.Format(_T("%02X"),pBuf[i]);  
				chRetValue+=strTmp;  
			}  
		}  
		break;  
	default:  
		break;  
	}  
}  