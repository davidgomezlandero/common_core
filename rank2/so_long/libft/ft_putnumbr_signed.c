/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumbr_signed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:52:37 by davigome          #+#    #+#             */
/*   Updated: 2024/11/17 08:51:44 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_digit(int n, int fd)
{
	char	c;

	c = '0' + n;
	write(fd, &c, 1);
}

static void	ftputnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		if (n > 9)
			ftputnbr_fd(n / 10, fd);
		write_digit(n % 10, fd);
	}
}

int	ft_putnumbr_signed(int n)
{
	int	i;

	i = 0;
	ftputnbr_fd(n, 1);
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
