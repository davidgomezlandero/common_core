#include <unistd.h>

int main (int argc, char **argv)
{
	int len = 0;
	int i = 0;

	if (argc == 2)
	{
		while (argv[1][i] == 32 || argv[1][i] == 9)
			i++;
		while (argv[1][len] != '\0')
			len++;
		len--;
		while (argv[1][len] == 32 || argv[1][len] == 9)
			len--;
		while (i <= len)
		{
			if (argv[1][i] == 32 || argv[1][i] == 9)
			{
				while (argv[1][i] == 32 || argv[1][i] == 9)
                        		i++;
				write(1, "   ",3);
			}
			write (1, &argv[1][i], 1);
			i++;
		}
	}
	write (1, "\n",1);
	return 0;
}
