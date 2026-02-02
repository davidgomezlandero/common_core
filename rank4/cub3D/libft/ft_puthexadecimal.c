/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexadecimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:46:06 by davigome          #+#    #+#             */
/*   Updated: 2024/11/17 08:52:25 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print(unsigned int n, const char format)
{
	if (n >= 16)
	{
		ft_print(n / 16, format);
		ft_print(n % 16, format);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
		{
			if (format == 'x')
				ft_putchar(n - 10 + 'a');
			else
				ft_putchar(n - 10 + 'A');
		}
	}
}

static int	ft_count(unsigned int n)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n = n / 16;
	}
	return (count);
}

int	ft_puthexadecimal(unsigned int n, const char format)
{
	int	len;

	len = 0;
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		ft_print(n, format);
		len = ft_count(n);
	}
	return (len);
}
