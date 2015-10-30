#include <iostream>
#include <vector>

//时间复杂度O(n) 空间复杂度O(n)
int StiarsStep(int n)
{
	if (n <= 2)
		return n;
	else
	{
		std::vector<int> steps;
		steps.push_back(1);
		steps.push_back(2);
		for (int i = 2; i < n; ++i)
		{
			steps.push_back(steps[i - 1] + steps[i - 2]);
		}
		return steps[n - 1];
	}
}

//时间复杂度O(n) 空间复杂度O(1)
int StiarsStep2(int n)
{
	int a = 1, b = 1;
	for (int i = 1;i < n;i++) {
		b += a;
		a = b - a;
	}
	return b;
}

int main8(int argc, char **argv)
{
	std::cout << StiarsStep(6) <<std::endl;
	system("pause");
	return 0;
}