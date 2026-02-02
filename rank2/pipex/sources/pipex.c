/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:34:35 by davigome          #+#    #+#             */
/*   Updated: 2024/12/28 11:41:50 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_init(char **argv, int argc, t_pipex *pipex)
{
	ft_allocate_pipes(argc, pipex);
	ft_file(argv, pipex, argc);
}

void	ft_allocate_pipes(int argc, t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->num_pipes = argc - 3;
	pipex->pipes = malloc(pipex->num_pipes * sizeof(int *));
	if (!pipex->pipes)
	{
		ft_printf("Error: Could not allocate the neccessary pipes");
		exit(1);
	}
	while (++i < pipex->num_pipes)
		pipex->pipes[i] = malloc(2 * sizeof(int));
}

void	ft_file(char **argv, t_pipex *pipex, int argc)
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	char	**command;

	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	pipe(pipex->pipes[0]);
	pid = fork();
	if (pid == 0)
	{
		ft_child_proccess(pipex, fd_in, argv);
	}
	else
	{
		wait(NULL);
		command = ft_split(argv[3], ' ');
		dup2(fd_out, STDOUT_FILENO);
		dup2(pipex->pipes[0][0], STDIN_FILENO);
		close(pipex->pipes[0][0]);
		close(pipex->pipes[0][1]);
		execvp(command[0], command);
	}
}

void	ft_child_proccess(t_pipex *pipex, int fd_in, char **argv)
{
	char	**command;

	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(pipex->pipes[0][1], STDOUT_FILENO);
	command = ft_split(argv[2], ' ');
	close(pipex->pipes[0][0]);
	close(pipex->pipes[0][1]);
	execvp(command[0], command);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
	{
		perror("Error allocating memory for pipex");
		return (1);
	}
	ft_init_pipex(pipex);
	ft_check(argv, argc, pipex, envp);
	ft_init(argv, argc, pipex);
	return (0);
}
