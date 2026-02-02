#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	int i;
	int number;
	if(argc == 2)
	{
		number = atoi(argv[1]);
		i = 2;
		if (number == 1)
			printf("1");
		while(number >= i)
		{
			if(number % i == 0)
			{
				printf("%d",i);
				if (number == i)
					break;
				printf("*");
				number /= i;
				i = 1;
			}
			i++;
		}
	}
	printf("\n");
}