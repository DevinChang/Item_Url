#ifndef __SPIDER_H__
#define __SPIDER_H__

#include <iostream>

#define MSG_DEPTNAME 101


class Config
{
public:
	void Init();
	std::string GetDepteName(std::string &);
	bool Judgeurl(std::string &);
	
private:
	
};


#endif