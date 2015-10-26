#pragma once

#include <iostream>
#include <string>
#include <vector>

class CIniFile
{
public:
	void SetIniFilePath(const std::string &);
	//ָ��section��key��ȡvalue
	std::string GetValueKey(const std::string &, const std::string &);
	//��ȡ����section
	std::vector<std::string> GetSectionNames();
	//��ȡsection����������
	std::string GetSectionData(const std::string &);
private:
	std::string ini_file_path_;
};

