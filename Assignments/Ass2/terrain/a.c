#include<stdio.h>
int main()
{
	char arr[] = "acb";
	char *a;
	a = arr;
	a++;
	printf("%c\n",a[-1]);
	return 0;
}
