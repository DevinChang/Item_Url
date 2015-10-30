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
	HRESULT InitWmi();    //初始化WMI  
	HRESULT ReleaseWmi(); //释放
	/*
	 *函数描述：传入类名及类中的成员 传出相关的内容 可参考：http://msdn.microsoft.com/en-us/library/aa394388(v=vs.85).aspx
	 *例如： 传入Win32_Process  及其成员 Description 将会传出所有的进程的描述信息
	 */
	BOOL GetSingleItemInfo(std::string ClassName,std::string ClassMember,std::vector<std::string> &chRetValue);
	

private:  
	void VariantToString(const LPVARIANT,CString &) const;//将Variant类型的变量转换为CString  
private:  
	IEnumWbemClassObject* m_pEnumClsObj;  
	IWbemClassObject* m_pWbemClsObj;  
	IWbemServices* m_pWbemSvc;  
	IWbemLocator* m_pWbemLoc;  
};  