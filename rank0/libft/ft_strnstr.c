/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:48:47 by davigome          #+#    #+#             */
/*   Updated: 2024/04/21 18:38:18 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cycle(const char *haystack, const char *needle, size_t len,
		size_t i)
{
	size_t	j;

	j = -1;
	while (haystack[i] == needle[++j] && j < ft_strlen(needle) && i < len)
	{
		i++;
	}
	return (j);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*ub;

	i = -1;
	if (needle[++i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		ub = (char *)&haystack[i];
		if (cycle(haystack, needle, len, i) == ft_strlen(needle))
			return (ub);
		i++;
	}
	return (0);
}
