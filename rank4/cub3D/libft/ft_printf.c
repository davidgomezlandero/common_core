/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:35:15 by davigome          #+#    #+#             */
/*   Updated: 2024/11/17 08:50:52 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	option_ftprintf(va_list args, const char format)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstring(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putpointer(va_arg(args, unsigned long)));
	else if (format == 'd' || format == 'i')
		return (ft_putnumbr_signed(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (format == 'x' || format == 'X')
		return (ft_puthexadecimal(va_arg(args, unsigned int), format));
	else if (format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		length;
	va_list	args;

	length = 0;
	i = -1;
	va_start(args, format);
	if (!format)
		return (-1);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			length += option_ftprintf(args, format[i + 1]);
			i++;
		}
		else
		{
			write (1, &format[i], 1);
			length++;
		}
	}
	va_end(args);
	return (length);
}

/* int main()
{
	ft_printf("Hola que tal estas %c o estas %c \n", 'b', 'm');
	
	ft_printf( "%d\n", -2147483647);
	printf( "%d\n", -2147483647);
	return (0);
} */