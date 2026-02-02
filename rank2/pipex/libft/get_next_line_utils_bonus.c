/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:33:02 by davigome          #+#    #+#             */
/*   Updated: 2024/12/28 11:55:30 by davigome         ###   ########.fr       */
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

char	*ft_strjoin_g(char *s1, char *s2)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	dst = malloc(ft_strlen_g(s1) + ft_strlen_g(s2) + 1);
	if (!dst)
		return (0);
	while (s1[++i])
		dst[i] = s1[i];
	while (s2[++j])
		dst[i + j] = s2[j];
	dst [i + j] = 0;
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
