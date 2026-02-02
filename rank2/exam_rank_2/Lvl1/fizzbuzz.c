#include <unistd.h>

void printnum (int i)
{
	char c;
	if (i > 9)
		printnum(i / 10);
	c = i % 10 + '0';
	write(1,&c,1);
}

int main ()
{
	int i = 1;
	char c;
	while (i <= 100)
	{
		if(i % 5 == 0 && i % 3 != 0)
			write(1, "buzz\n",5);
		else if (i%3 == 0 && i %5 != 0)
			write(1, "fizz\n", 5);
		else if(i%15 == 0)
			write(1, "fizzbuzz\n",9);
		else
		{
			printnum(i);
			write(1, "\n",1);
		}
		i++;
	}
	return 0;
}
