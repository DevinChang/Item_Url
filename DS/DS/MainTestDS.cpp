#include <iostream>
#include "demo1_GrayCode.h"
#include "demo2_HappyNumber.h"
#include "demo3_ReverseInteger.h"
#include "demo4_StringToInteger.h"
#include "demo5_DynamicPrograming.h"
#include "demo6_WordPattern.h"

int main(int argc, char ** argv)
{

	//<<n 相当于扩大了2^n倍？
	/*unsigned int tmp = 3 << 3;
	std::cout << tmp << std::endl;*/
	
	/*
	//Happy Number
	bool is_happynum = CHappyNum::IsHappyNum(37);
	is_happynum = CHappyNum::IsHappyNumHash(32);
	*/

	/*
	//Reverse Integer
	int reverse_int = 0;
	std::cout << "Please Input ReverseNumber: " << std::endl;
	std::cin >> reverse_int;
	std::cout << CReverseInt::Reverse(reverse_int) << std::endl;
	*/

	//String To Integer
	//std::cout << CAtoi::MyAtoi("2147483648") << std::endl;
	//std::cout << CAtoi::MyItoi(-123) << std::endl;
	
	int sub[] = {5, 3, 4, 8, 6, 7};
	std::string str = "dog cat cat dog";
	std::cout << CDP::LongestIncreasingSub(sub, sizeof(sub) / sizeof(int)) << std::endl;
	std::cout << CDP::ImproveLongestIncreasingSub(sub, sizeof(sub) / sizeof(int)) << std::endl;

	CWordPttern::IsWordPattern("abba", "dog cat cat dog");

	system("pause");
	return 0;
}