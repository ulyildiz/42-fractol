#include <stdio.h>

int main()
{
	long long x = 0;

	long long *a = &x;
	long long *y = a + 1;
	printf("%lld\n", *y);

	int color;
	unsigned char red = 17;
	unsigned char blue = 33;
	color = red << 16 | blue << 8;
	//0000 0000 0001 0001 0000 0000 0000 0000 -> kırmızı gelince
	//0000 0000 0000 0000 0000 0000 0001 0001
	printf("%d\n", color);
	char *c;
	c = (void *)0;

	printf("%s\n", c);
	return *y;
}