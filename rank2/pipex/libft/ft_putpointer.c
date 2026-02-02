/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:04:02 by davigome          #+#    #+#             */
/*   Updated: 2024/11/17 08:51:54 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putrest(unsigned long p)
{
	if (p >= 16)
	{
		ft_putrest(p / 16);
		ft_putrest(p % 16);
	}
	else
	{
		if (p <= 9)
			ft_putchar(p + '0');
		else
			ft_putchar(p - 10 + 'a');
	}
}

static int	ft_count(unsigned long p)
{
	int	len;

	len = 0;
	while (p)
	{
		p = p / 16;
		len++;
	}
	return (len);
}

int	ft_putpointer(unsigned long p)
{
	int	len;

	len = 0;
	if (p == 0)
	{
		write(1, "(nil)", 5);
		len = 5;
	}
	else
	{
		ft_putstring("0x");
		ft_putrest(p);
		len = 2 + ft_count(p);
	}
	return (len);
}
