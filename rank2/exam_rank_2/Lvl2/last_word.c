#include <unistd.h>

int main (int argc, char **argv)
{
	int len = 0;
	int aux = 0;
	if (argc == 2)
	{
		while(argv[1][len] != '\0')
			len++;
		len--;
		while(argv[1][len] == 32 || argv[1][len] == 9)
			len--;
		aux = len;
		while (argv[1][aux] != 32 && argv[1][aux] != 9)
			aux--;
		aux++;
		while (aux <= len)
		{
			write(1, &argv[1][aux],1);
			aux++;
		}
	}
	write (1, "\n",1);
}
