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
	solution: 1.定义一个容器用来存放数的digits的平方和。
			  2.判断和是否等于1，若相当则返回true。否则放入容器。
			  3.不快乐数的一个特点是，最终的和重复出现。所以，在存有和的容器中查找，若找到相同的元素，则返回false。
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