#pragma once

#include <iostream>
#include <string>
#include <vector>

class CIniFile
{
public:
	void SetIniFilePath(const std::string &);
	//指定section和key获取value
	std::string GetValueKey(const std::string &, const std::string &);
	//获取所有section
	std::vector<std::string> GetSectionNames();
	//获取section下所有数据
	std::string GetSectionData(const std::string &);
private:
	std::string ini_file_path_;
};

