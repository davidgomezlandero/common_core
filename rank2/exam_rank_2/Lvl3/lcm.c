#include <unistd.h>
#include <stdio.h>
unsigned int	lcm( int a, int b)
{
	unsigned int	num;
	unsigned int	mcm = 1;
	if (a <= 0 || b <= 0)
		return 0;
	if (a > b)
		mcm = a;
	else
		mcm = b;
	num = a * b;
	while (mcm < num)
	{
		if (mcm%a == 0 && mcm%b == 0)
			return mcm;
		mcm++;
	}
}
/*
int main()
{
	printf("%d", lcm(-1,5));
}*/
