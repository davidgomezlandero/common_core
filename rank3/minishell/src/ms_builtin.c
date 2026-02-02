/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:51:08 by jotrujil          #+#    #+#             */
/*   Updated: 2025/02/11 20:12:22 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	is_builtin(t_command *cmd)
{
	const char	*builtins[] = {"cd", "export", "unset", "pwd",
		"echo", "env", "exit", NULL};
	int			i;
	int			len;

	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
		return (0);
	if (ft_strchr(cmd->full_cmd[0], '/')
		|| (cmd->full_path && ft_strchr(cmd->full_path, '/')))
		return (0);
	len = ft_strlen(cmd->full_cmd[0]);
	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(cmd->full_cmd[0], builtins[i], len)
			&& len == (int)ft_strlen(builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

// Initialize all the custom builtins and assign their functions
static void	init_builtins(t_builtin *builtins)
{
	builtins[0] = (t_builtin){"cd", ms_cd};
	builtins[1] = (t_builtin){"export", ms_export};
	builtins[2] = (t_builtin){"unset", ms_unset};
	builtins[3] = (t_builtin){NULL, NULL};
}

// Execute the builtins or exit the minishell if the exit builtin is executed
static int	exec_builtin(t_prompt *prompt, t_list *cmd, int *terminate)
{
	char		**full_cmd;
	t_builtin	builtins[4];
	int			i;

	full_cmd = ((t_command *)cmd->content)->full_cmd;
	i = 0;
	init_builtins(builtins);
	if (full_cmd && !ft_strncmp(*full_cmd, "exit", ft_strlen(*full_cmd))
		&& ft_strlen(*full_cmd) == 4)
	{
		g_status = ms_exit(cmd, terminate);
		return (1);
	}
	while (builtins[i].name)
	{
		if (full_cmd && !ft_strncmp(*full_cmd, builtins[i].name,
				ft_strlen(builtins[i].name)))
		{
			g_status = builtins[i].func(prompt);
			return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_or_cmd(t_prompt *prompt, t_list *cmd, int	*terminate)
{
	int	status;

	while (cmd)
	{
		if (!exec_builtin(prompt, cmd, terminate))
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_status = 128 + WTERMSIG(status);
	}
	return (g_status);
}
