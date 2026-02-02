/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_child_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:52:51 by davigome          #+#    #+#             */
/*   Updated: 2025/02/11 20:17:09 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

/* Writes str in fd and return the nbr of characters */
int	ms_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen(s)));
	return (0);
}

/* Write a matrix in fd and retunr nbr of characters */
int	ft_putmatrix_fd(char **m, int nl, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (m && m[i])
	{
		if (nl)
			count += ms_putendl_fd(m[i], fd);
		else
			count += ms_putstr_fd(m[i], fd);
		i++;
	}
	return (count);
}

void	ms_child_builtin(t_prompt *prompt, t_command *node, int lenght,
		t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (node->full_cmd && !ft_strncmp(*node->full_cmd, "pwd", lenght)
		&& lenght == 3)
		g_status = ms_pwd();
	else if (node->full_cmd && !ft_strncmp(*node->full_cmd, "echo", lenght)
		&& lenght == 4)
		g_status = ms_echo(cmd);
	else if (node->full_cmd && !ft_strncmp(*node->full_cmd, "env", lenght)
		&& lenght == 3)
	{
		ft_putmatrix_fd(prompt->envp, 1, 1);
		g_status = 0;
	}
	else if (node->full_cmd)
	{
		if (execve(node->full_path, node->full_cmd, prompt->envp) == -1)
		{
			perror("minishell");
			g_status = 127;
			exit(g_status);
		}
	}
}
