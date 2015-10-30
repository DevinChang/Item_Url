/*
ʵ��atoi���������ַ���ת��Ϊ����
����ѧϰ���������ַ���ת����������������ASCII������ʽ���ת������Ȼת��ûʲô�Ѷȣ�����Ҫ���ǵ�����ڶ�
���磺�ַ�����ͷ�Ŀո�Ҫȥ����
	����+�Ż�-���Һ������������ȡ�����򷵻�0��
	�����ֵĹ����������������ַ������жϷ��ص�ǰ��ȡ�����֣���"123+=23" "123 123" �����"123"
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
	//ֻ�е�str[i]Ϊ0ʱ�Ž���ѭ���������"  123 4"��str[2] = 1ʱ�͵���ѭ��,�ʿɽ��ַ�����ǰ��ո�ȥ��
	//while(str[i] == ' ' && str[i] != 0)
		//++i;
	//
	i = str.find(' ');
	//���Ѽ��+ - ��д��ѭ������Ͳ���ÿ��ѭ������⣬ֻ���ڿ�ͷ������������Ǹ�����ִ��һ�μ��ɣ���д��ѭ��
	//�������������������Ŷ��һ����ַ������м�⣬�߼�����
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
