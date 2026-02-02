/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:47:05 by davigome          #+#    #+#             */
/*   Updated: 2024/04/21 15:15:12 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*aux1;
	unsigned char	*aux2;
	size_t			cont;

	cont = 0;
	aux1 = (unsigned char *)s1;
	aux2 = (unsigned char *)s2;
	while (cont < n)
	{
		if (aux1[cont] != aux2[cont])
			return (aux1[cont] - aux2[cont]);
		cont++;
	}
	return (0);
}
