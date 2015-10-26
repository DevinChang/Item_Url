/*
Project: CrayCode(�����룩
Describe: The gray code is a binary numeral system where two successive values differ in only one bit.
Analysise: ���ɷ������ĵ����ص�˵������ô���ʵ���ĵ�����˵�ľ������ɲ���(n+1)λGrayCode�ĺ�2nλǰ׺��һ��
		   �������õ���λ���㼼�ɡ�
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

