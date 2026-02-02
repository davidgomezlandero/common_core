/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 08:34:51 by davigome          #+#    #+#             */
/*   Updated: 2024/04/27 12:38:52 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cont_l(char const *set, char const *s1)
{
	int		i;
	int		j;
	size_t	cont;

	i = -1;
	j = -1;
	cont = 0;
	while (s1[++i])
	{
		j = -1;
		while (set[++j])
		{
			if (s1[i] == set[j])
			{
				cont++;
				break ;
			}
		}
		if (s1[i] != set[j])
			break ;
	}
	return (cont);
}

static size_t	cont_r(char const *set, char const *s1)
{
	int		i;
	int		j;
	size_t	cont;

	cont = 0;
	i = ft_strlen(s1);
	while (s1[--i])
	{
		j = -1;
		while (set[++j])
		{
			if (set[j] == s1[i])
			{
				cont++;
				break ;
			}
		}
		if (s1[i] != set[j])
			break ;
	}
	return (cont);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	cont_left;
	size_t	cont_right;

	if (!s1 || !set)
		return (NULL);
	cont_left = cont_l(set, s1);
	cont_right = cont_r(set, s1);
	return (ft_substr(s1, cont_left, ft_strlen(s1) - cont_right - cont_left));
}
