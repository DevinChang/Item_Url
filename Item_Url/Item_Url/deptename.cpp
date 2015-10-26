#include <fstream>
#include <Windows.h>
#include <string.h>
#include "deptename.h"
#include "util.h"
#include "boost/algorithm/string.hpp"



CDepartmentName::CDepartmentName()
{
	std::string ini_file_path = "./bin/value.ini";
	std::vector<std::string> seciton_name;
	seciton_name.swap(CUtil::LoadSectionNames(ini_file_path));
	std::vector<std::string>::iterator it = seciton_name.begin();
	for (; it != seciton_name.end(); it++)
	{
		if ((*it).size())
			dept_map_.insert(std::map<std::string, std::pair<std::string, int>>::value_type(*it, 
				make_pair(CUtil::LoadSectionKeyValue(*it, "mainkey", "./bin/value.ini"), 0)));
	}
}

//查找部门各关键字的个数
int CDepartmentName::FindDeptNameCount(const std::string &dept_name)
{
	int pos = 0;
	int dept_count = 0;
	while(pos != std::string::npos)
	{
		pos = html_.find(dept_name, pos + dept_name.size());
		if (pos != std::string::npos)
			dept_count++;
	
	}
	return dept_count;
} 

//查找部门关键字的总数
int CDepartmentName::SearchValue(const std::string &keyword_buf)
{
	std::vector<std::string> vec_split;
	boost::algorithm::split(vec_split, keyword_buf, boost::algorithm::is_any_of(" "));
	int count = 0;
	int max_count = 0;
	std::vector<std::string>::iterator it = vec_split.begin();
	for (; it != vec_split.end(); it++)
	{
		count = FindDeptNameCount(*it);
		max_count += count;
	}
	return max_count;
}

std::string CDepartmentName::GetGateGory(const std::string &url)
{	
	if (!CUtil::UTF8ToMB(url, html_))
		return "error";
	std::map<std::string, std::pair<std::string, int>>::iterator it = dept_map_.begin();
	int max_count = (*it).second.second;
	std::string depart_name;
	for (; it != dept_map_.end(); ++it)
	{	
		(*it).second.second = SearchValue((*it).second.first);
		if ((*it).second.second > max_count)
		{	
			max_count = (*it).second.second;
			depart_name = (*it).first;
		}
	}
	return depart_name;
}