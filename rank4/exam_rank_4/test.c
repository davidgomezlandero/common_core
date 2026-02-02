#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int	error(char *str)
{
	while(*str)
		write(2,str++,1);
	return 1;
}

int	cd(int i, char **argv)
{
	if (i != 2)
		return error("error: cd: bad arguments\n");
	else if (chdir(argv[1]) == -1)
	{
		return error("error: cd: cannot change directory to "), error(argv[1]), error("\n");
	}
	return 0;
}

