#include <unistd.h>

int main (int argc, char **argv)
{
	int len_1 = 0;
	int i_1 = 0;
	int j_2 = 0;
	int coinc = 0;

	if (argc == 3)
	{
		while (argv[1][len_1] != '\0')
			len_1++;
		while(argv[1][i_1] != '\0' )
		{
			while (argv[2][j_2] != '\0')
			{
				if (argv[1][i_1] == argv[2][j_2])
				{
					coinc++;
					break;
				}
				j_2++;
			}
			i_1++;
		}
		if (len_1 == coinc || argv[1] == "")
			write(1, "1",1);
		else 
			write (1, "0",1);

	}
	write(1, "\n",1);
}
