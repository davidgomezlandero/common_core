#include <unistd.h>

int main (int argc, char **argv)
{
	int len = 0;
	if (argc == 2)
	{
		while(argv[1][len] != '\0')
			len++;
		len--;
		while (argv[1][len])
		{
			write(1, &argv[1][len],1);
			len--;
		}
	}
	write (1, "\n",1);
}
