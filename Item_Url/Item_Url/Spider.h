#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <boost/regex.hpp>
#include "thread.h"



class CSpider
{
public:
	enum Method{READ_CMD, READ_FILE};
	void Init( const std::string &deal_url);
	void Init();

	void BeginTask(int thead_count = 1);
private:
	bool UrlIsLegal(const std::string &);	
	std::vector<NodeUrl> stroe_vec_;
	std::vector<std::string> url_vec_;
	int method_;
};

