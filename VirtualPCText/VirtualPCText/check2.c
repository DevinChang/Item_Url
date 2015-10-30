#include <stdio.h>
#include <stdlib.h>

void LDTDetect(void)
{
	unsigned short ldt_addr = 0;
	unsigned char ldtr[2];

	_asm sldt ldtr
	ldt_addr = *((unsigned short *)&ldtr);
	printf("LDT BaseAddr: 0x%x\n", ldt_addr);

	if(ldt_addr == 0x0000)
	{
		printf("Native OS\n");
	}
	else
		printf("Inside VMware\n");
}

void GDTDetect(void)
{
	unsigned int gdt_addr = 0;
	unsigned char gdtr[4];

	_asm sgdt gdtr
	gdt_addr = *((unsigned int *)&gdtr[2]);
	printf("GDT BaseAddr:0x%x\n", gdt_addr);

	if((gdt_addr >> 24) == 0xff)
	{
		printf("Inside VMware\n");
	}
	else
		printf("Native OS\n");
}

int main2(void)
{
	LDTDetect();
	GDTDetect();
	system("pause");
	return 0;
}