/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:12:15 by davigome          #+#    #+#             */
/*   Updated: 2025/02/03 19:30:18 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		j;
	int		len_1;
	int		len_2;

	i = -1;
	j = -1;
	if (!s1)
		len_1 = 0;
	else
		len_1 = ft_strlen(s1);
	if (!s2)
		len_2 = 0;
	else
		len_2 = ft_strlen(s2);
	dst = malloc(len_1 + len_2 + 1);
	if (!dst)
		return (0);
	while (s1 && s1[++i])
		dst[i] = s1[i];
	while (s2 && s2[++j])
		dst[i + j] = s2[j];
	dst [i + j] = 0;
	return (dst);
}
