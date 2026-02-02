/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_nodes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:08:03 by davigome          #+#    #+#             */
/*   Updated: 2025/02/10 14:57:33 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

t_command	*ms_command_init(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->full_cmd = NULL;
	command->full_path = NULL;
	command->in_file = STDIN_FILENO;
	command->out_file = STDOUT_FILENO;
	return (command);
}

char	**ms_clean_output(char **output)
{
	int		i;
	char	**temp;

	i = -1;
	temp = malloc(sizeof(char *) * (ft_size_matrix(output) + 1));
	temp[ft_size_matrix(output)] = NULL;
	while (output && output[++i])
	{
		if ((output[i][0] == '\'' && \
			output[i][ft_strlen(output[i]) - 1] == '\'')
			|| (output[i][0] == '\"' && \
			output[i][ft_strlen(output[i]) - 1] == '\"'))
			temp[i] = ft_substr(output[i], 1, ft_strlen(output[i]) - 2);
		else
			temp[i] = ft_strdup(output[i]);
	}
	return (temp);
}

t_list	*ms_nodes(char **args, int i)
{
	t_list	*cmds[2];
	char	**aux[2];

	cmds[0] = NULL;
	aux[1] = ms_clean_output(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			if (args[i][0] == '|')
				++i;
			ft_lstadd_back(&cmds[0], ft_lstnew(ms_command_init()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		aux[0] = args;
		cmds[1]->content = ms_params(cmds[1]->content, aux, &i);
		if (i < 0)
			return (ms_break_fill(cmds[0], args, aux[1]));
		if (!args[i])
			break ;
	}
	ft_free_matrix(args);
	ft_free_matrix(aux[1]);
	return (cmds[0]);
}
