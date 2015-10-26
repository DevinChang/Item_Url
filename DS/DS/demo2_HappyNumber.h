#include <set>

class CHappyNum
{
public:
	static bool IsHappyNum(int n)
	{
		//use the fact of between arr[0, 6) is not happy number,and all not happy numbers end on a cycle that hits this interval; 
		while(n > 6)
		{
			int next = 0;
			while(n > 0)
			{
				next += (n % 10) * (n % 10);
				n /= 10;
			}
			n = next;
		}
		return n == 1;
	}

	//use hash to solve this problem
	/*
	solution: 1.����һ�����������������digits��ƽ���͡�
			  2.�жϺ��Ƿ����1�����൱�򷵻�true���������������
			  3.����������һ���ص��ǣ����յĺ��ظ����֡����ԣ��ڴ��к͵������в��ң����ҵ���ͬ��Ԫ�أ��򷵻�false��
	*/
	static bool IsHappyNumHash(int n)
	{
		int sum = 0;
		std::set<int> happy_set;
		std::set<int>::iterator it;
		happy_set.insert(n);

		while (sum != 1)
		{
			do 
			{
				sum += (n % 10) * (n % 10);
				n /= 10;
			} while (n > 0);
			
			if (sum == 1)
			{
				break;
			}
			else
			{
				it = happy_set.find(sum);
				if (it != happy_set.end())
				{
					return false;
				}
				happy_set.insert(sum);
				n = sum;
				sum = 0;
			}
		}

		return true;
	}
};