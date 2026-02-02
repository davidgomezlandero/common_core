/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:46:29 by davigome          #+#    #+#             */
/*   Updated: 2024/06/30 14:32:25 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	space(const char *str, int cont)
{
	if ((str[cont] >= 9 && str[cont] <= 13) || str[cont] == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	cont;
	int		number;
	int		neg;

	cont = 0;
	number = 0;
	neg = 1;
	while (space(str, cont))
		cont++;
	if (str[cont] == '-' || str[cont] == '+')
	{
		if (str[cont] == '-')
			neg = -1;
		cont++;
	}
	while (ft_isdigit(str[cont]))
	{
		number = number * 10 + (str[cont] - 48);
		cont++;
	}
	number = neg * number;
	return (number);
}
/*int main()
{
	char e= 'e';
	printf("%d",ft_atoi((e + "1").c_str());
	printf("%d",atoi((e + "1").c_str());
	return 0;
}*/