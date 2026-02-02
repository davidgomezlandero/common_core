#include <unistd.h>

int ft_atoi(char *n)
{
	int i = -1;
	int num = 0;
	while (n[++i] != '\0')
	       num = n[i] - '0' + num * 10;
	return num;	
}

void ft_putnbr(int n)
{
	char c;
	if(n > 9)
		ft_putnbr(n/10);
	c = n%10 + '0';
	write(1, &c,1);
}

int main(int argc, char **argv)
{	int num_1;
	int num_2;
	int i = 1;
	int max;
	if (argc == 3)
	{
		num_1 = ft_atoi(argv[1]);
		num_2 = ft_atoi(argv[2]);
		while (i <= num_1 && i < num_2)
		{
			if (num_1%i == 0 && num_2%i == 0)
				max = i;
			i++;
		}
		ft_putnbr(max);
	}
	write(1, "\n", 1);
}
