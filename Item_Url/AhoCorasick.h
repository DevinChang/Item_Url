#ifndef __AHOCORASICK_H__
#define __AHOCORASICK_H__
/*
AC��ģƥ���㷨������ƥ�����ؼ��֣��ڱ���Ŀ�У������ԣ�ʱ�临�Ӷ�ҲΪO��n�����ﲻ���Ż���Ŀ�ġ�
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