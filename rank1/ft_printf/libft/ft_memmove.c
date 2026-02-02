/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:58:38 by davigome          #+#    #+#             */
/*   Updated: 2024/04/19 12:57:58 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*destiny;
	unsigned const char	*origin;

	destiny = (unsigned char *) dst;
	origin = (unsigned const char *) src;
	if (dst == (void *)0 && src == (void *)0)
		return (0);
	if (destiny < origin)
		ft_memcpy(dst, src, len);
	if (destiny > origin)
		while (0 < len--)
			destiny[len] = origin[len];
	return (dst);
}
