/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 06:23:22 by davigome          #+#    #+#             */
/*   Updated: 2024/11/17 08:51:35 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ftstrlen(const char *s)
{
	size_t	contador;

	contador = 0;
	while (s[contador] != '\0')
		contador++;
	return (contador);
}

static void	ftputstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (i < (int)ftstrlen(s))
		write(fd, &s[i++], 1);
}

int	ft_putstring(char *string)
{
	if (!string)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ftputstr_fd(string, 1);
	return (ftstrlen(string));
}
