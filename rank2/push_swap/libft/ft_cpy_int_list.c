/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_int_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:36:48 by davigome          #+#    #+#             */
/*   Updated: 2025/01/02 01:19:14 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cpy_int_list(int *src, int *dst, size_t	lenght)
{
	size_t	i;

	i = -1;
	while (++i < lenght)
		dst[i] = src[i];
}
