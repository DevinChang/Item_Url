#include <Windows.h>
#include "ini.h"
#include "boost/smart_ptr.hpp"
#include "boost/algorithm/string.hpp"


void CIniFile::SetIniFilePath(const std::string &path)
{
	//设置ini文件的路径
	ini_file_path_ = path;
}

std::string CIniFile::GetValueKey(const std::string &section, const std::string &key)
{
	char value[MAX_PATH] = {0};
	int count = GetPrivateProfileString(section.c_str(), key.c_str(), "", value, sizeof(value), ini_file_path_.c_str());
	std::string	key_value(value);
	return key_value;
}

std::vector<std::string> CIniFile::GetSectionNames()
{
	char section[MAX_PATH] = {0};
	int count = GetPrivateProfileSectionNames(section, sizeof(section), ini_file_path_.c_str());
	std::string section_string(section, count);
	for (unsigned int i = 0; i < section_string.size(); i++)
	{	
		if (section_string[i] == '\0')
			section_string[i] = '#';
	}
	std::vector<std::string> vct_result;
	boost::split(vct_result, section_string, boost::is_any_of("#"));
	return vct_result;
}

std::string CIniFile::GetSectionData(const std::string &section)
{
	char value_buf[MAX_PATH] = {0};
	std::string key_word;
	int value_length = GetPrivateProfileSection(section.c_str(), value_buf, sizeof(value_buf), ini_file_path_.c_str());
	std::vector<std::string> vec_split;
	boost::algorithm::split(vec_split, value_buf, boost::algorithm::is_any_of("="));
	key_word = vec_split[1];
	return key_word;
}

