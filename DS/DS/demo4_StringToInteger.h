/*
实现atoi函数，将字符串转换为整数
这题学习了怎样把字符串转换成整数，即利用ASCII码的性质进行转换。虽然转换没什么难度，但需要考虑的情况众多
比如：字符串开头的空格要去掉。
	若是+号或-号且后面是数字则读取，否则返回0。
	读数字的过程中若遇到其他字符，则中断返回当前读取的数字，若"123+=23" "123 123" 都输出"123"
*/
#include <iostream>
#include <string>

class CAtoi
{
public:
	static int MyAtoi(std::string str);
	static std::string MyItoi(int num);
};

int CAtoi::MyAtoi(std::string str)
{
	long long ret = 0;
	int op = 1;
	int i = 0;
	//只有当str[i]为0时才进入循环，如果是"  123 4"则到str[2] = 1时就调出循环,故可将字符串的前面空格去掉
	//while(str[i] == ' ' && str[i] != 0)
		//++i;
	//
	i = str.find(' ');
	//不把检测+ - 号写到循环里面就不用每次循环都检测，只用在开头检测是正数还是负数，执行一次即可，若写到循环
	//里，这样不仅检测是正负号而且会在字符串的中检测，逻辑混乱
	if (str[i] == '+')
		++i;
	else if (str[i] == '-')
	{
		op = -1;
		++i;
	}
	for (; i < str.size(); ++i)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			ret = ret * 10 + op * (str[i] - '0');
		}
		else
			return ret;
		if (ret > INT_MAX || ret < INT_MIN)
			ret = ret > 0 ? INT_MAX : INT_MIN;
	}

	return ret;
}

std::string CAtoi::MyItoi(int num)
{
	std::string str;
	char tmp;
	char op;
	int x = abs(num);
	while (x)
	{
		tmp = x % 10 + '0';
		x /= 10;
		str.append(1, tmp);
	}
	if (num < 0)
	{
		op = '-';
		str.append(1, op);
	}
	reverse(str.begin(), str.end());
	return str;
}
