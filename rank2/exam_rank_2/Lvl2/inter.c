#include <unistd.h>

int main(int argc, char **argv)
{
	char aux[5000];
	int j= 0;
	int k = 0;
	int i = 0;
	int flag = 0;
	if (argc == 3)
	{
		while(argv[1][i] != '\0')
		{
			while(argv[1][i] != argv[2][j] && argv[2][j] != '\0')
				j++;
			if(argv[1][i] == argv[2][j])
			{
				while(aux[k] != '\0')
				{
					if (argv[1][i] == aux[k])
					{
						flag = 1;
						break;
					}
					k++;
				}
				if(flag == 0)
				{
					write(1, &argv[1][i],1);
					aux[k] = argv[1][i];
				}
			}
			flag = 0;
			j = 0;
			k = 0;
			i++;
		}
	}
	write(1, "\n",1);
}
