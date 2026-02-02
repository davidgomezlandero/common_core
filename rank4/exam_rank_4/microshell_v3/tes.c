#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int	error(char *str)
{
	while(*str)
		write(2, str++, 1);
	return 1;
}

int	cd(int i, char **argv)
{
	if (i != 2)
		return error("error: cd: bad arguments\n");
	if (chdir(argv[1]) == -1)
		return error("error: cd: cannot change directory to "), error(argv[1]), error("\n");
	return 0;
}

int execute(int argc, char **argv, char **envp, int pipeFlag)
{
	int fd[2], status, pid;

	if (strcmp("cd", argv[0]) == 0)
		return cd(argc, argv);
	if (pipeFlag != 0 && pipe(fd) == -1)
		return error("error: fatal\n");
	pid = fork();
	if (pid == 0)
	{
		if (pipeFlag != 0 && (dup2(fd[1], STDOUT_FILENO) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
			return error("error: fatal\n"), exit, 1;
		argv[argc] = NULL;
		return (execve(argv[0], argv, envp), error("error: cannot execute "), error(argv[0]), error("\n"), exit(1), 1);
	}
	waitpid(pid, &status, 0);
	if (pipeFlag != 0 && (dup2(fd[0], STDIN_FILENO) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		return error("error: fatal\n"), exit(1), 1;
	return status;
}

int main(int argc, char **argv, char **envp)
{
	int status = 0;

	int j;
	if (argc < 2 || !argv[1])
		return 1;
	for (int i = 1; i < argc; i++)
	{
		j = i;
		while (i < argc && argv[i] && strcmp("|", argv[i]) != 0 && strcmp(";", argv[i]) != 0)
			i++;
		if (i != j)
			status = execute(i - j, &argv[j], envp, (i < argc && argv[i] && strcmp("|", argv[i]) == 0));
	}
	return WIFEXITED(status) && WEXITSTATUS(status);
}
