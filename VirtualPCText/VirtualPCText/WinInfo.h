#pragma once
#include <afxpriv.h>  
#include <atlbase.h>  

#include <WbemIdl.h> 
#include <string>
#include <vector>

#pragma comment(lib,"WbemUuid.lib")  

class CWmiInfo  
{  
public:  
	CWmiInfo(void);  
	~CWmiInfo(void);  

public:  
	HRESULT InitWmi();    //��ʼ��WMI  
	HRESULT ReleaseWmi(); //�ͷ�
	/*
	 *�����������������������еĳ�Ա ������ص����� �ɲο���http://msdn.microsoft.com/en-us/library/aa394388(v=vs.85).aspx
	 *���磺 ����Win32_Process  �����Ա Description ���ᴫ�����еĽ��̵�������Ϣ
	 */
	BOOL GetSingleItemInfo(std::string ClassName,std::string ClassMember,std::vector<std::string> &chRetValue);
	

private:  
	void VariantToString(const LPVARIANT,CString &) const;//��Variant���͵ı���ת��ΪCString  
private:  
	IEnumWbemClassObject* m_pEnumClsObj;  
	IWbemClassObject* m_pWbemClsObj;  
	IWbemServices* m_pWbemSvc;  
	IWbemLocator* m_pWbemLoc;  
};  