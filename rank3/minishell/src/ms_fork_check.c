/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:27:34 by davigome          #+#    #+#             */
/*   Updated: 2025/02/11 20:15:21 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

/* Redirect the output command to the next command (if pipe) or STDOUT */
void	*ms_child_redir(t_list *cmd, int fd[2])
{
	t_command	*current_cmd;

	current_cmd = cmd->content;
	if (current_cmd->in_file != STDIN_FILENO)
	{
		if (dup2(current_cmd->in_file, STDIN_FILENO) == -1)
			return (ms_handle_error("minishell: dup2 failed\n", NULL, 1));
		close(current_cmd->in_file);
	}
	if (current_cmd->out_file != STDOUT_FILENO)
	{
		if (dup2(current_cmd->out_file, STDOUT_FILENO) == -1)
			return (ms_handle_error("minishell: dup2 failed\n", NULL, 1));
		close(current_cmd->out_file);
	}
	else if (cmd->next && dup2(fd[PIPE_WRITE_END], STDOUT_FILENO) == -1)
		return (ms_handle_error("minishell: dup2 failed\n", NULL, 1));
	close(fd[1]);
	return ("");
}

/* Do the command itself */
void	*ms_child(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_command	*current_cmd;
	int			lenght;

	current_cmd = cmd->content;
	lenght = 0;
	if (current_cmd->full_cmd)
		lenght = ft_strlen(*current_cmd->full_cmd);
	ms_child_redir(cmd, fd);
	close(fd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ms_child_builtin(prompt, current_cmd, lenght, cmd);
	ft_lstclear(&prompt->cmds, ms_clean);
	exit(g_status);
}

/* Do a fork to execute the command in a child */
void	ms_exec(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close (fd[0]);
		close (fd[1]);
		ms_handle_error("minishell: fork failed\n", NULL, 1);
	}
	else if (pid == 0)
		ms_child(prompt, cmd, fd);
}

void	*ms_fork_check(t_prompt	*prompt, t_list *cmd, int fd[2])
{
	t_command	*current_cmd;
	DIR			*dir;

	current_cmd = cmd->content;
	dir = NULL;
	if (current_cmd->full_cmd)
		dir = opendir(*current_cmd->full_cmd);
	if (current_cmd->in_file == -1 || current_cmd->out_file == -1)
		return (NULL);
	if ((current_cmd->full_path && access(current_cmd->full_path, X_OK) == 0)
		|| is_builtin(current_cmd))
		ms_exec(prompt, cmd, fd);
	else if (!is_builtin(current_cmd) && ((current_cmd && \
		!access(current_cmd->full_path, F_OK)) || dir))
		g_status = 126;
	else if (!is_builtin(current_cmd) && current_cmd->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
