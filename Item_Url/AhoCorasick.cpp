/*
AC多模匹配算法，用于匹配多个关键字，在本项目中，经测试，时间复杂度也为O（n），达不到优化的目的。
*/

#include "AhoCorasick.h"



struct  ac_transition
{
	char  condition;
	int   next;
};


struct  ac_state_finder :
	public binary_function<ac_transition, char, bool>
{
	bool  operator() (const ac_transition& t, char c) const
	{
		return  (t.condition == c);
	}
};


vector<vector<ac_transition>>   goto_table;
vector<vector<string>>          output_table;
vector<int>                     fail_table;
FSAType  fsa_type = FSA_NULL;



int  AhoCorasick::ac_goto(int _state, char _cont)
{
	vector<ac_transition>::const_iterator ret = 
		find_if(goto_table[_state].begin(), goto_table[_state].end(),
		bind2nd(ac_state_finder(), _cont));
	if(goto_table[_state].end() == ret)
	{
		if(0 == _state)
			return 0;
		else
			return AC_FAIL_STATE;
	}
	else
		return ret->next;
}


int  AhoCorasick::ac_creat_goto_table(const vector<string>& _ptns)
{
	int state = 0;
	int state_id = 0;

	ac_transition t;
	vector<ac_transition>  ts;
	vector<string>  ss;

	goto_table.push_back(ts);
	output_table.push_back(ss);
	state_id++;

	for(vector<string>::const_iterator i = _ptns.begin(); i != _ptns.end(); ++i)
	{
		state = 0;
		for(string::const_iterator j=i->begin(); j<i->end(); ++j)
		{
			int next_state = ac_goto(state, *j);
			if(0 == next_state || AC_FAIL_STATE == next_state)
			{
				t.condition = *j;
				t.next = state_id++;
				goto_table[state].push_back(t);

				goto_table.push_back(ts);
				output_table.push_back(ss);

				state = t.next;
			}
			else
				state = next_state;
		}
		output_table[state].push_back(*i);
	}

	return 0;
}


int  AhoCorasick::ac_creat_fail_table()
{
	if(goto_table.empty())
		return -1;

	fail_table.resize(goto_table.size());
	for(size_t i=0; i<goto_table.size(); ++i)
		fail_table[i] = AC_UNDEF_FAIL;

	queue<int>  q;
	for(vector<ac_transition>::const_iterator i = goto_table[0].begin();
		i != goto_table[0].end(); ++i)
	{
		fail_table[i->next] = 0;
		q.push(i->next);
	}

	int  state;
	while(!q.empty())
	{
		state = q.front();  q.pop();

		for(vector<ac_transition>::const_iterator i = goto_table[state].begin();
			i != goto_table[state].end(); ++i)
		{
			if(AC_UNDEF_FAIL != fail_table[i->next])
				continue;

			q.push(i->next);

			int  prev_state = state, ret;
			do 
			{
				prev_state = fail_table[prev_state];
				ret = ac_goto(prev_state, i->condition);
			} while (AC_FAIL_STATE == ret);

			fail_table[i->next] = ret;

			for(vector<string>::const_iterator j = output_table[ret].begin();
				j != output_table[ret].end(); ++j)
			{
				vector<string>::const_iterator sret =
					find(output_table[i->next].begin(), output_table[i->next].end(), *j);
				if(output_table[i->next].end() == sret)
					output_table[i->next].push_back(*j);
			}
		}
	}

	fsa_type = FSA_NFA;

	return 0;
}


int  AhoCorasick::ac_convert_to_DFA()
{
	if(fsa_type != FSA_NFA)
		return -1;

	if(goto_table.empty() || fail_table.empty())
		return -1;

	queue<int>  q;
	for(vector<ac_transition>::const_iterator i = goto_table[0].begin();
		i != goto_table[0].end(); ++i)
	{ q.push(i->next); }

	int  state;
	while(!q.empty())
	{
		state = q.front();  q.pop();

		for(size_t c=0; c<AC_CONT_SIZE; ++c)
		{
			int  next_state = ac_goto(state, c);
			if(next_state != AC_FAIL_STATE && next_state != 0)
				q.push(next_state);
			else
			{
				next_state = ac_goto(fail_table[state], c);
				if(next_state != AC_FAIL_STATE && next_state != 0)
				{
					ac_transition t;
					t.condition = c;
					t.next = next_state;
					goto_table[state].push_back(t);
				}
			}
		}
	}

	fail_table.clear();
	fsa_type = FSA_DFA;

	return 0;
}


void  AhoCorasick::OutputMatch(int _state, size_t _pos, int a[])
{
	for(vector<string>::const_iterator i = output_table[_state].begin();
		i != output_table[_state].end(); ++i)
	{
		if ("新闻" == *i)
			a[0]++;
		if ("购物" == *i)
			a[1]++;
		if ("银行" == *i)
			a[2]++;
		if ("集团" == *i)
			a[3]++;
		if ("游戏" == *i)
			a[4]++;
		if ("视频" == *i)
			a[5]++;
		if ("教育" == *i)
			a[6]++;
		if ("政府" == *i)
			a[7]++;
		if ("招聘" == *i)
			a[8]++;
		if ("通信" == *i)
			a[9]++;
		if ("健康" == *i)
			a[10]++;
		if ("旅游" == *i)
			a[11]++;
	}
}

int  AhoCorasick::ac_search(const string& _txt)
{
	if(goto_table.empty() || FSA_NULL == fsa_type)
		return -1;

	int  state = 0;
	string::size_type i;
	int a[12] = {0};
	for(i=0; i<_txt.length(); ++i)
	{
		char c = _txt[i];
		if(output_table[state].size() > 0)
			OutputMatch(state, i, a);

		if(FSA_NFA == fsa_type)
		{
			while(AC_FAIL_STATE == ac_goto(state, c))
				state = fail_table[state];
			state = ac_goto(state, c);
		}
		else if(FSA_DFA == fsa_type)
		{
			state = ac_goto(state, c);
			if(AC_FAIL_STATE == state)
				state = 0;
		}
	}

	if(output_table[state].size() > 0)
		OutputMatch(state, i, a);

	int k = 0;
	int max = a[0];
	for (int i = 0; i < 12; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
			k = i;
		}
	}

	return k;
}
