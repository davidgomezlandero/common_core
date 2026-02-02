/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:13:27 by davigome          #+#    #+#             */
/*   Updated: 2024/11/17 08:52:12 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_printnumber(unsigned int n)
{
	char	c;

	if (n > 9)
		ft_printnumber(n / 10);
	n = n % 10;
	c = n + '0';
	write (1, &c, 1);
}

int	ft_putunsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		ft_printnumber(n);
		len = ft_count(n);
	}
	return (len);
}
