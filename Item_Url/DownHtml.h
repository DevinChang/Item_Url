#ifndef __DOWNHTML_H__
#define __DOWNHTML_H__

#include <string>
#include <vector>

class DownHtml
{
public:
	std::string GetUrlHtml(const char *);
	//void DisplayHttpPage(LPCTSTR pszServerName, LPCTSTR pszFileName);
	

	bool UTF8ToMB(std::string& , const char* , int );

	std::string GetGateGory(const std::string &);

	int Judge(const std::string &);

	int Category(const std::string &);
};


#endif

