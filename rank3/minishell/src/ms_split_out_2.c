/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_out_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:03:26 by davigome          #+#    #+#             */
/*   Updated: 2025/02/10 14:56:29 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	ms_clean(void *n)
{
	t_command	*node;

	node = n;
	ft_free_matrix(node->full_cmd);
	free(node->full_path);
	if (node->in_file != STDIN_FILENO)
		close(node->in_file);
	if (node->out_file != STDOUT_FILENO)
		close(node->out_file);
	free(node);
}

t_list	*ms_break_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, ms_clean);
	ft_free_matrix(temp);
	ft_free_matrix(args);
	return (NULL);
}

char	**ms_extend_array(char	**result, char *output, char *set, int i[3])
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (output && output[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, output[i[0]]))
		{
			while ((!ft_strchr(set, output[i[0]]) || q[0] \
				|| q[1]) && output[i[0]])
			{
				q[0] = (q[0] + (!q[1] && output[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && output[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		result[i[2]++] = ft_substr(output, i[1], i[0] - i[1]);
	}
	return (result);
}

static int	ft_count_words(char *s, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

char	**ms_subsplit(char *output, char *set)
{
	char	**result;
	int		n_strs;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!output)
		return (NULL);
	n_strs = ft_count_words((char *)output, set, 0);
	if (n_strs == -1)
		return (NULL);
	result = malloc((n_strs + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = ms_extend_array(result, (char *)output, set, i);
	result[n_strs] = NULL;
	return (result);
}
