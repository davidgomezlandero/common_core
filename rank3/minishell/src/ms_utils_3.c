/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 08:11:51 by davigome          #+#    #+#             */
/*   Updated: 2025/02/11 16:00:22 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

char	**ms_separate_matrix(char **aux, char const *s, char *set, int i[3])
{
	int	len;
	int	j[2];

	len = ft_strlen(s);
	j[0] = 0;
	j[1] = 0;
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || j[0] || j[1]) && s[i[0]])
		{
			j[0] = (j[0] + (!j[1] && s[i[0]] == '\'')) % 2;
			j[1] = (j[1] + (!j[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

int	ms_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
		return ((int)ft_strlen(s) + 1);
	}
	return (0);
}
