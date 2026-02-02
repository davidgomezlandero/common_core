/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:47:08 by jotrujil          #+#    #+#             */
/*   Updated: 2025/02/13 13:00:59 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

/* Searches for a command in env_path and returns the full path if found.*/
static char	*find_cmd(char **env_path, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		tmp = ft_strjoin(env_path[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
	}
	free(full_path);
	return (NULL);
}

/* Finds the command in the PATH environment variable */
static char	*find_cmd_in_path(t_prompt *p, t_command *current_cmd)
{
	char	*path;
	char	*full_path;
	char	**split_path;

	path = ms_get_env("PATH", p->envp, 4);
	split_path = ft_split(path, ':');
	free(path);
	full_path = find_cmd(split_path, current_cmd->full_cmd[0]);
	if (!full_path || !current_cmd->full_cmd[0] || !current_cmd->full_cmd[0][0])
	{
		ms_handle_error("minishell: command not found: ",
			current_cmd->full_cmd[0], 127);
	}
	ft_free_matrix(split_path);
	return (full_path);
}

/* Checks and prepares the command, handling directories and paths,
and returns a pointer to DIR if the command is a directory. */
static DIR	*check_validate_cmd(t_prompt *p, t_list *cmd)
{
	t_command	*current_cmd;
	DIR			*dir;
	char		**full_cmd;
	char		**split_path;

	dir = NULL;
	current_cmd = cmd->content;
	full_cmd = current_cmd->full_cmd;
	if (full_cmd)
		dir = opendir(*full_cmd);
	if (full_cmd && ft_strchr(*full_cmd, '/') && !dir)
	{
		split_path = ft_split(*full_cmd, '/');
		current_cmd->full_path = ft_strdup(*full_cmd);
		free(full_cmd[0]);
		full_cmd[0] = ft_strdup(split_path[ft_size_matrix(split_path) - 1]);
		ft_free_matrix(split_path);
	}
	else if (!is_builtin(current_cmd) && full_cmd && !dir)
		current_cmd->full_path = find_cmd_in_path(p, current_cmd);
	return (dir);
}

/*  Validates and prepares a command for execution,
handling directories and checking for errors. */
static void	prepare_command(t_prompt *prompt, t_list *cmd)
{
	t_command	*current_cmd;
	DIR			*dir;
	char		*full_path;
	char		**full_cmd;

	current_cmd = cmd->content;
	dir = check_validate_cmd(prompt, cmd);
	full_path = current_cmd->full_path;
	full_cmd = current_cmd->full_cmd;
	if (!is_builtin(current_cmd) && full_cmd && dir)
		ms_handle_error("minishell: Is a directory: ", full_cmd[0], 126);
	else if (!is_builtin(current_cmd) && full_path && access(full_path, F_OK)
		== -1)
		ms_handle_error("minishell: No such file or directory: ", full_path,
			127);
	else if (!is_builtin(current_cmd) && full_path && access(full_path, X_OK)
		== -1)
		ms_handle_error("minishell: Permission denied: ", full_path, 126);
	if (dir)
		closedir(dir);
}

void	*exec_cmd(t_prompt *prompt, t_list *cmd)
{
	t_command	*current_cmd;
	t_command	*next_cmd;
	int			fd[2];

	current_cmd = (t_command *)cmd->content;
	if (cmd->next)
		next_cmd = (t_command *)cmd->next->content;
	else
		next_cmd = NULL;
	prepare_command(prompt, cmd);
	if (pipe(fd) == -1)
		ms_handle_error("minishell: error creating pipe\n", NULL, 1);
	if (!ms_fork_check(prompt, cmd, fd))
		return (NULL);
	close(fd[PIPE_WRITE_END]);
	if (next_cmd && !next_cmd->in_file)
		next_cmd->in_file = fd[PIPE_READ_END];
	else
		close(fd[PIPE_READ_END]);
	if (current_cmd->in_file > 2)
		close(current_cmd->in_file);
	if (current_cmd->out_file > 2)
		close(current_cmd->out_file);
	return (NULL);
}
