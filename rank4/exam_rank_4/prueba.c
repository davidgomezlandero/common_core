#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int error(char *msg)
{
	while(*msg)
		write(2, msg++, 1);
	return (1);
}
int cd(int ac, char **av)
{
	if (ac != 2)
		return (error("error: cd: bad arguments\n"));
	else if (chdir(av[1]) == -1)
		return (error("error: cd: cannot change directory to "), error(av[1]), error("\n"));
	return (0);
}
int execute(int ac, char **av, char **envp, int pipeFlag)
{
	int fd[2];
	int status;
	int pid;

	if (strcmp("cd", av[0]) == 0)
		return (cd(ac, av));
	if (pipeFlag != 0 && pipe(fd) == -1)
		return (error("error: fatal\n"));
	pid = fork();
	if (pid == 0)
	{
		if (pipeFlag != 0 && (dup2(fd[1], STDOUT_FILENO) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return (error("error: fatal\n"), exit(1), 1);
		av[ac] = NULL;
		return (execve(av[0], av, envp), error("error: cannot execute "), error(av[0]), error("\n"), exit(1), 1);
	}
	waitpid(pid, &status, 0);
	if (pipeFlag != 0 && (dup2(fd[0], STDIN_FILENO) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		return (error("error: fatal\n"), exit(1), 1);
	return (status);
}

int main(int ac, char **av, char **envp)
{
	int status = 0;
	int j;

	if (ac < 2 || !av[1])
		return (1);
	for(int i = 1; i < ac; i++)
	{
		j = i;
		while(i < ac && av[i] && strcmp("|", av[i]) != 0 && strcmp(";", av[i]) != 0)
		i++;
		if (i != j)
			status = execute(i - j, &av[j], envp, (i < ac && av[i] && strcmp("|", av[i]) == 0));
	}
	return (WIFEXITED(status) && WEXITSTATUS(status));
}
