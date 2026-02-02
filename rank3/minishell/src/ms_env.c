/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:57:37 by davigome          #+#    #+#             */
/*   Updated: 2025/02/13 10:59:40 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ms_add_end_env(char	**matrix, char *new)
{
	char	**new_matrix;
	int		len;
	int		i;

	i = -1;
	new_matrix = NULL;
	if (!new || !*new)
		return (matrix);
	len = ft_size_matrix(matrix);
	new_matrix = malloc(sizeof(char *) * (len + 2));
	new_matrix[len + 1] = NULL;
	if (!new_matrix)
		return (matrix);
	while (++i < len)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		if (!new_matrix[i])
		{
			ft_free_matrix(new_matrix);
			ft_free_matrix(matrix);
		}
	}
	new_matrix[i] = ft_strdup(new);
	ft_free_matrix(matrix);
	return (new_matrix);
}

char	**ms_add_env(char *var, char *value, char **envp)
{
	int		count[2];
	char	*temp[2];

	count[0] = -1;
	temp[0] = ft_strjoin(var, "=");
	if (!temp[0])
		return (envp);
	temp[1] = ft_strjoin(temp[0], value);
	free(temp[0]);
	if (!temp[1])
		return (envp);
	while (!ft_strchr(var, '=') && envp && envp[++count[0]])
	{
		count[1] = ms_strchr_pos(envp[count[0]], '=');
		if (!ft_strncmp(envp[count[0]], var, count[1]))
		{
			free(envp[count[0]]);
			envp[count[0]] = temp[1];
			return (envp);
		}
	}
	envp = ms_add_end_env(envp, temp[1]);
	free(temp[1]);
	return (envp);
}

char	*ms_get_env(char *var, char **envp, int n)
{
	int	i;
	int	aux;

	i = -1;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[++i])
	{
		aux = n;
		if (aux < ms_strchr_pos(envp[i], '='))
			aux = ms_strchr_pos(envp[i], '=');
		if (!ft_strncmp(envp[i], var, aux))
			return (ft_substr(envp[i], aux + 1, ft_strlen(envp[i])));
	}
	return (NULL);
}

int	ms_var_in_envp(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ms_strchr_pos(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}
