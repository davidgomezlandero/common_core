/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:22:34 by davigome          #+#    #+#             */
/*   Updated: 2025/02/01 18:45:05 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* update with the output from command */
static void	ms_update_output(char ***matrix, int fd)
{
	char	**new;
	char	*temp;
	char	*read;

	new = NULL;
	read = NULL;
	while (1)
	{
		read = get_next_line(fd);
		if (!read)
			break ;
		temp = strtrim(read, "\n");
		free(read);
		new = ms_add_end_env(new, temp);
		free(temp);
	}
	ft_free_matrix(*matrix);
	*matrix = new;
}

void	ms_get_exec(char ***out, char *full, char *args, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**matrix;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		matrix = ft_split(args, ' ');
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (access(full, F_OK) == 0)
			execve(full, matrix, envp);
		exit(1);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	ms_update_output(out, fd[0]);
	close(fd[0]);
}
