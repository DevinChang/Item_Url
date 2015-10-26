#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "boost/smart_ptr.hpp"

class CDepartmentName
{
public:
	static CDepartmentName *GetInstance()
	{
		static CDepartmentName *ms_pInstance;
		if (ms_pInstance == NULL)
			ms_pInstance = new CDepartmentName;
		return ms_pInstance;
	}
	std::string GetGateGory(const std::string &);
private:
	CDepartmentName();
	int SearchValue(const std::string &);
	int FindDeptNameCount(const std::string &deptname);
private:
	std::map<std::string, std::pair<std::string, int>> dept_map_;
	std::string html_;
};

