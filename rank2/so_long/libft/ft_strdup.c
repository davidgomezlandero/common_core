/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:33:43 by davigome          #+#    #+#             */
/*   Updated: 2024/04/23 23:47:57 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	cont;

	cont = 0;
	dst = malloc(ft_strlen(s1) +1);
	if (!dst)
		return (0);
	while (s1[cont])
	{
		dst[cont] = s1[cont];
		cont++;
	}
	dst[cont] = 0;
	return (dst);
}
