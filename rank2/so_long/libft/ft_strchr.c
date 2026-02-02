/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 09:57:06 by davigome          #+#    #+#             */
/*   Updated: 2024/04/21 13:03:24 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			cont;
	const char	*aux;

	cont = 0;
	c = (char)c;
	if (c == '\0')
	{
		aux = &s[ft_strlen(s)];
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
