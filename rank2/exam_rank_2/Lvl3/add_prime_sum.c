/* Assignment name  : add_prime_sum
Expected files   : add_prime_sum.c
Allowed functions: write, exit
--------------------------------------------------------------------------------

Write a program that takes a positive integer as argument and displays the sum
of all prime numbers inferior or equal to it followed by a newline.

If the number of arguments is not 1, or the argument is not a positive number,
just display 0 followed by a newline.

Yes, the examples are right.

Examples:

$>./add_prime_sum 5
10
$>./add_prime_sum 7 | cat -e
17$
$>./add_prime_sum | cat -e
0$
$> */

int ft_atoi(char *str)
{
	int n = 0;
	while(*str)
	{
		n = n *10 + *str - '0';
		str++;
	}
	return n;
}

int isprime (int n)
{
	int i = 2;

	if (n <= 1)
		return (0);
	while(i * i <= n)
	{
		if(n % i == 0)
			return (0);
		i++;
	}
	return 1;
}

void ft_putnbr (int n)
{
	if(n > 9)
		ft_putnbr(n / 10);
	char c = n % 10 + '0';
	write (1, &c, 1);
}
int main (int argc, char **argv)
{
	if (argc == 2)
	{
		int nbr = ft_atoi (argv[1]);
		int sum = 0;
		while (nbr > 0)
		{
			if (isprime(nbr))
				sum+=nbr;
			nbr--;
		}
	}
	if (argc != 2)
		ft_putnbr(0);
	write(1, "\n", 1);
}