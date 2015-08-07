#ifndef __AHOCORASICK_H__
#define __AHOCORASICK_H__
/*
AC多模匹配算法，用于匹配多个关键字，在本项目中，经测试，时间复杂度也为O（n），达不到优化的目的。
*/
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>
#include <cstdio>
using namespace std;

#define AC_FAIL_STATE   -1
#define AC_UNDEF_FAIL   -1
#define AC_CONT_SIZE    256

enum FSAType
{
	FSA_NULL = 0,
	FSA_NFA,
	FSA_DFA
};


class AhoCorasick
{
public:
	
	int  ac_goto(int _state, char _cont);
	int  ac_creat_goto_table(const vector<string>& _ptns);
	int  ac_creat_fail_table();
	int  ac_convert_to_DFA();
	int  ac_search(const string& _txt);
	void  OutputMatch(int _state, size_t _pos, int a[]);
};

#endif