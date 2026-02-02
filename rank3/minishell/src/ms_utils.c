/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:57:49 by davigome          #+#    #+#             */
/*   Updated: 2025/02/11 19:38:40 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (matrix[++i])
			free(matrix[i]);
		free(matrix);
	}
}

int	ft_size_matrix(char **matrix)
{
	int	size;

	size = 0;
	while (matrix && matrix[size])
		size++;
	return (size);
}

char	**ft_dup_matrix(char **envp)
{
	int		size;
	char	**cpy;
	int		i;

	i = -1;
	size = ft_size_matrix(envp);
	cpy = malloc(sizeof(char *) * (size + 1));
	if (!cpy)
		return (NULL);
	while (envp[++i])
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
		{
			ft_free_matrix(cpy);
			return (NULL);
		}
	}
	cpy[i] = NULL;
	return (cpy);
}

void	*ms_handle_error(char *error, char *param, int g_status_error)
{
	g_status = g_status_error;
	ft_putstr_fd(error, 2);
	ms_putendl_fd(param, 2);
	return (NULL);
}

int	ms_strchr_pos(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}
