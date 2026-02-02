/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:15:02 by davigome          #+#    #+#             */
/*   Updated: 2024/08/08 22:59:44 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	length(int n)
{
	size_t	size;

	size = 0;
	if (n < 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static char	*special(int n)
{
	char	*result;

	if (n == 0)
	{
		result = malloc(2);
		result[0] = '0';
		result[1] = '\0';
	}
	else
	{
		result = malloc(12);
		result[0] = '-';
		result[1] = '2';
		result[2] = '1';
		result[3] = '4';
		result[4] = '7';
		result[5] = '4';
		result[6] = '8';
		result[7] = '3';
		result[8] = '6';
		result[9] = '4';
		result[10] = '8';
		result[11] = '\0';
	}
	return (result);
}

static char	*tochar(char *result, int div, int aux, int n)
{
	size_t	size;
	int		i;

	i = aux;
	size = length(n);
	while (aux++ < (int)size - 1)
		div = div * 10;
	if (n < 0)
		n = -n;
	while (div > 0)
	{
		result[i++] = '0' + n / div;
		aux = n / div;
		n = n - aux * div;
		div = div / 10;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	size;
	int		i;
	int		div;
	int		aux;

	div = 1;
	i = 0;
	size = length(n);
	if (!n && n != 0)
		return (NULL);
	if (n == 0 || n == -2147483648)
		return (special(n));
	result = malloc (size + 1);
	if (!result)
		return (NULL);
	if (n < 0)
		result[i++] = '-';
	aux = i;
	return (tochar(result, div, aux, n));
}

/* int main (void)
{
	int j = -2147483648;
	printf("%s", ft_itoa(j));
	return 0;
} */