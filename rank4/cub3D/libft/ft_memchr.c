/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:27:04 by davigome          #+#    #+#             */
/*   Updated: 2024/04/21 15:18:53 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			cont;

	cont = 0;
	str = (unsigned char *)s;
	while (cont < n)
	{
		if (str[cont] == (unsigned char)c)
			return ((void *)&str[cont]);
		cont++;
	}
	return (NULL);
}
