#include<stdio.h>
#include <stdlib.h>

void add(int *p)
{
	(*p)++;
	printf("%d",*p);
	if (*p>5)
	{
		return;
	}
	add(p);
}
int main1()
{
	int i=0;
	//add(&i);
	char str[] = "helloworld";
	printf("%d\n", sizeof(str));

	char *p, *q;
	//p = (char*) malloc(sizeof(char) * 20);
	//q = p;
	//scanf("%s %s", p, q);


	int a = 500 * 400;
	int b = 300 * 200;
	printf("%d\n", a * b);
	//printf("%s %s/n", p, q);
	system("pause");
	return 0;
}