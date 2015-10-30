#include <iostream>
#include <string>
#include <vector>
#include <map>

class CWordPttern
{
public:
	static bool IsWordPattern(std::string pattern, std::string str);
};

std::vector<std::string> split(std::string str)
{
	std::string tmpstr;
	std::vector<std::string> stroe;
	int j = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] != ' ')
		{	
			tmpstr.append(1, str[i]);
			continue;
		}
		stroe.push_back(tmpstr);
		tmpstr.clear();
	}
	stroe.push_back(tmpstr);
	return stroe;
}

bool CWordPttern::IsWordPattern(std::string pattern, std::string str)
{
	std::map<std::string, std::string> pat;
	std::make_pair("a", "dog");
	pat.insert(std::make_pair("a", "dog"));
	pat.insert(std::make_pair("b", "cat"));
	pat.insert(std::make_pair("c", "fish"));
	pat.insert(std::make_pair("d", "bird"));
	
	std::vector<std::string> tmp = split(str);

	return false;
}
