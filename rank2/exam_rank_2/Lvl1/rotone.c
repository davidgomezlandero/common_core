#include <unistd.h>

int main (int argc, char **argv)
{
	int i;

	i = 0;
	if (argc != 2)
	{
		write(1, "\n",1);
		return 0;
	}
	while (argv[1][i])
	{
		if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
		{
			if(argv[1][i] == 'z')
				argv[1][i] = 'a';
			else
				argv[1][i] += 1;	
		}
		if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
                {
                        if(argv[1][i] == 'Z')
                                argv[1][i] = 'A';
                        else
                                argv[1][i] += 1;
                }
		i++;
	}
	i = -1;
	while(argv[1][++i])
		write(1, &argv[1][i], 1);
	write(1, "\n",1);
	return 0;
}
