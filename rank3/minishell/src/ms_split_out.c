/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:48:47 by davigome          #+#    #+#             */
/*   Updated: 2025/02/02 08:18:26 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

char	*ms_paths(char *str, int i, int j[2], char *var)
{
	char	*path;
	char	*aux;

	j[0] = 0;
	j[1] = 0;
	while (str && str[++i])
	{
		j[0] = (j[0] + (!j[1] && str[i] == '\'')) % 2;
		j[1] = (j[1] + (!j[0] && str[i] == '\"')) % 2;
		if (!j[0] && !j[1] && str[i] == '~' && (i == 0 || \
			str[i - 1] != '$'))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (ms_paths(str, i + ft_strlen(var) - 1, j, var));
		}
	}
	free(var);
	return (str);
}

char	*ms_get_sub_var(char *str, int i, t_prompt *prompt)
{
	char	*beggin;
	char	*var;
	char	*result;
	int		pos;

	pos = ms_strchars_pos(&str[i], "|\"\'$?>< ") + \
		(ft_strchr("$?", str[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(str) - 1;
	beggin = ft_substr(str, 0, i - 1);
	var = ms_get_env(&str[i], prompt->envp, \
		ms_strchars_pos(&str[i], "\"\'$|>< "));
	if (!var && str[i] == '$')
		var = ft_itoa(prompt->pid);
	if (!var && str[i] == '?')
		var = ft_itoa(g_status);
	result = ft_strjoin(beggin, var);
	free(var);
	var = ft_strjoin(result, &str[i + pos]);
	free(result);
	free(beggin);
	free(str);
	return (var);
}

char	*ms_vars(char *str, int i, int j[2], t_prompt *prompt)
{
	j[0] = 0;
	j[1] = 0;
	while (str && str[++i])
	{
		if (str [i] == '\'' && j[1] == 0)
		{
			++j[0];
			j[0] = j[0] % 2;
		}
		if (str [i] == '\"' && j[0] == 0)
		{
			++j[1];
			j[1] = j[1] % 2;
		}
		if (str[i] == '$' && str[i + 1] && ms_strchr_pos("\'\" ", \
			str[i + 1]) == -1)
			return (ms_vars(ms_get_sub_var(str, ++i, prompt), -1, j, prompt));
	}
	return (str);
}

char	**ms_split_output(char **output, t_prompt *prompt)
{
	char	**split_out;
	int		i;
	int		j[2];

	i = -1;
	while (output && output[++i])
	{
		output[i] = ms_vars(output[i], -1, j, prompt);
		output[i] = ms_paths(output[i], -1, j, \
			ms_get_env("HOME", prompt->envp, 4));
		split_out = ms_subsplit(output[i], "<>|");
		ft_matrix_replace_in(&output, split_out, i);
		i += ft_size_matrix(split_out) - 1;
		ft_free_matrix(split_out);
	}
	return (output);
}
