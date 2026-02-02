/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:33:02 by davigome          #+#    #+#             */
/*   Updated: 2025/02/13 11:42:31 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_g(char *s)
{
	size_t	contador;

	contador = 0;
	while (s[contador] != '\0')
		contador++;
	return (contador);
}

static char	*allocate_and_concat(char *s1, char *s2, size_t len1, size_t len2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	dst = malloc(len1 + len2 + 1);
	if (!dst)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	j = -1;
	while (s1[++i])
		dst[i] = s1[i];
	while (s2[++j])
		dst[i + j] = s2[j];
	dst[i + j] = 0;
	return (dst);
}

char	*ft_strjoin_g(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*dst;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	len1 = ft_strlen_g(s1);
	len2 = ft_strlen_g(s2);
	dst = allocate_and_concat(s1, s2, len1, len2);
	free(s1);
	return (dst);
}

char	*ft_strchr_g(char *s, int c)
{
	int			cont;
	const char	*aux;

	cont = 0;
	if (!s)
		return (0);
	c = (char)c;
	if (c == '\0')
	{
		aux = &s[ft_strlen_g(s)];
		return ((char *)aux);
	}
	while (s[cont] != '\0')
	{
		if (s[cont] == c)
		{
			aux = &s[cont];
			return ((char *)aux);
		}
		cont++;
	}
	return (NULL);
}
