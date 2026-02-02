#include <unistd.h>

int main (int argc, char **argv)
{
	int i = 0;
	int aux;
	int cont = 0;
	if (argc == 2)
	{
		while(argv[1][i] != 0)
		{
			if (argv[1][i] >= 'A' && argv[1][i] <= 'Z'
					|| argv[1][i] >= 'a' && argv[1][i] <= 'z')
			{
				if(argv[1][i] >= 'A' && argv[1][i] <= 'Z')
				{
					int aux = argv[1][i] - 'A';
					while (cont < aux)
					{
						write(1, &argv[1][i], 1);
						cont++;
					}

				}
				else
				{
					int aux = argv[1][i] - 'a';
                                        while (cont < aux)
                                        {
                                                write(1, &argv[1][i], 1);
                                                cont++;                                                                                                             }
				}
				cont = 0;
			}
			write (1, &argv[1][i], 1);
			i++;

		}
	}
	write (1, "\n",1);
}
