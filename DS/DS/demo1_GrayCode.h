/*
Project: CrayCode(格雷码）
Describe: The gray code is a binary numeral system where two successive values differ in only one bit.
Analysise: 规律分析在文档。重点说下如何用代码实现文档的所说的镜像生成并在(n+1)位GrayCode的后2n位前缀加一。
		   这里利用的是位运算技巧。
*/

#include <vector>



class CGrayCode
{
public:

	static void GrayCode(int n, std::vector<int> &tmp);

	//Nim Game
	static bool CanWin(int n)
	{
		return (n % 4) > 0;
	}
};


void CGrayCode::GrayCode(int n, std::vector<int> &tmp)
{
	unsigned int highest = 1 << (n - 1);
	if (n == 0)
	{
		tmp.push_back(0);
		return;
	}
	if (n == 1)
	{
		tmp.push_back(0);
		tmp.push_back(1);
		return;
	}
	GrayCode(n - 1, tmp);
	std::vector<int> r_tmp(tmp);
	reverse(r_tmp.begin(), r_tmp.end());
	for (int i = 0; i < r_tmp.size(); ++i)
	{
		tmp.push_back(highest | r_tmp[i]);
	}
}

