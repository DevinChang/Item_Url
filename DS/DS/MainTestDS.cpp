#include <iostream>
#include "demo1_GrayCode.h"
#include "demo2_HappyNumber.h"


int main(int argc, char ** argv)
{

	//<<n �൱��������2^n����
	/*unsigned int tmp = 3 << 3;
	std::cout << tmp << std::endl;*/

	bool is_happynum = CHappyNum::IsHappyNum(37);
	is_happynum = CHappyNum::IsHappyNumHash(32);
	system("pause");
	return 0;
}