/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:28:21 by jotrujil          #+#    #+#             */
/*   Updated: 2025/02/11 19:43:04 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	if_sigint(int sig)
{
	struct termios	term;

	if (sig == SIGINT)
	{
		g_status = 130;
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOE;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

char	*strtrim(char const *s1, char const *set)
{
	int	len;
	int	i;
	int	j;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	i = 0;
	j = len -1;
	while (i <= len / 2 && ft_strchr(set, s1[i]) != NULL)
		i++;
	while (j >= len / 2 && ft_strchr(set, s1[j]) != NULL)
		j--;
	if (i > j)
		return (ft_strdup(""));
	len = j - i;
	return (ft_substr(s1, i, len + 1));
}

int	ms_count_strs(const char *s, char *c, int i[2])
{
	int	j[2];

	j[0] = 0;
	j[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (ft_strchr(c, s[i[0]]) == 0)
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || j[0]) && s[i[0]] != '\0')
			{
				if (!j[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					j[1] = s[i[0]];
				j[0] = (j[0] + (s[i[0]] == j[1])) % 2;
				j[1] *= j[0] != 0;
				i[0]++;
			}
			if (j[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

char	**ms_matrix_replace_n(char ***src, char **add, int n)
{
	char	**tmp;
	int		ijk[3];

	ijk[0] = 0;
	ijk[1] = 0;
	ijk[2] = 0;
	if (!src || !*src || n < 0 || n >= ft_size_matrix(*src))
		return (NULL);
	tmp = ft_calloc(ft_size_matrix(*src) + ft_size_matrix(add), sizeof(char *));
	while (ijk[0] < ft_size_matrix(*src))
	{
		if (ijk[0] == n)
		{
			while (add && add[ijk[1]])
				tmp[ijk[2]++] = ft_strdup(add[ijk[1]++]);
		}
		else
			tmp[ijk[2]++] = ft_strdup(src[0][ijk[0]]);
		ijk[0]++;
	}
	ft_free_matrix(*src);
	*src = tmp;
	return (*src);
}

int	ms_strchars_pos(const char *s, char *search)
{
	int	i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i] != '\0')
	{
		if (ft_strchr(search, s[i]))
			return (i);
	}
	return (-1);
}
