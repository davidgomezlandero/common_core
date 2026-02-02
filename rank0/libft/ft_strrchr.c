/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:48:57 by davigome          #+#    #+#             */
/*   Updated: 2024/04/21 12:01:55 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*aux;
	int			len;

	c = (char)c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == c)
		{
			aux = &s[len];
			return ((char *)aux);
		}
		len--;
	}
	return (NULL);
}
