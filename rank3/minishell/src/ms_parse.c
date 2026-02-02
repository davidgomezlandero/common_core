/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:16:44 by davigome          #+#    #+#             */
/*   Updated: 2025/02/13 11:49:27 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

char	**ms_trim(char const *s, char *set)
{
	char	**temp;
	int		strings;
	int		i[3];
	int		count[2];

	count[0] = 0;
	count[1] = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	strings = ms_count_strs(s, set, count);
	if (strings == -1)
		return (NULL);
	temp = malloc((strings + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	temp = ms_separate_matrix(temp, s, set, i);
	temp[strings] = NULL;
	return (temp);
}

char	**ft_matrix_replace_in(char ***big, char **small, int n)
{
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_size_matrix(*big))
		return (NULL);
	aux = ft_calloc(ft_size_matrix(*big) + \
		ft_size_matrix(small), sizeof(char *));
	while (aux && big[0][++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup(big[0][i[0]]);
		else
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	ft_free_matrix(*big);
	*big = aux;
	return (*big);
}

t_command	*ms_params(t_command *node, char **temp[2], int *i)
{
	if (temp[0][*i])
	{
		if (temp[0][*i][0] == '>' && temp[0][*i + 1] && \
			temp[0][*i + 1][0] == '>')
			node = ms_out_2(node, temp[1], i);
		else if (temp[0][*i][0] == '>')
			node = ms_out_1(node, temp[1], i);
		else if (temp[0][*i][0] == '<' && temp[0][*i + 1] && \
			temp[0][*i + 1][0] == '<')
			node = ms_in_2(node, temp[1], i);
		else if (temp[0][*i][0] == '>')
			node = ms_in_1(node, temp[1], i);
		else if (temp[0][*i][0] != '|')
			node->full_cmd = ms_add_end_env(node->full_cmd, temp[1][*i]);
		else
		{
			ms_handle_error("Minishell: syntax error near `|'\n", NULL, 1);
			*i = -2;
		}
		return (node);
	}
	ms_handle_error("Minishell: syntax error near `|'\n", NULL, 1);
	*i = -2;
	return (node);
}

void	*ms_parse_and_exec(char **output, t_prompt *prompt)
{
	int	terminate;
	int	i;

	terminate = 0;
	output = ms_split_output(output, prompt);
	prompt->cmds = ms_nodes(output, -1);
	if (!prompt->cmds)
		return (prompt);
	i = ft_lstsize(prompt->cmds);
	g_status = builtin_or_cmd(prompt, prompt->cmds, &terminate);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!terminate && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (output && terminate)
	{
		ft_lstclear(&prompt->cmds, ms_clean);
		return (NULL);
	}
	return (prompt);
}

void	*ms_parse(char *output, t_prompt *p)
{
	char		**aux;
	t_command	*t;

	if (!output)
	{
		printf("exit\n");
		return (NULL);
	}
	if (output[0] != '\0')
		add_history(output);
	aux = ms_trim(output, " ");
	free(output);
	if (!aux)
		ms_handle_error("Minishell could not trim the output\n", NULL, 1);
	if (!aux)
		return ("");
	p = ms_parse_and_exec(aux, p);
	if (p && p->cmds)
		t = p->cmds->content;
	if (p && p->cmds && t && t->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = ms_add_env("_", t->full_cmd[ft_size_matrix(t->full_cmd) - 1], \
			p->envp);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, ms_clean);
	return (p);
}
