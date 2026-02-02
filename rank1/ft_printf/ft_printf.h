/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:58:58 by davigome          #+#    #+#             */
/*   Updated: 2024/08/07 02:05:10 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_putstring(char *string);
int	ft_putnumbr_signed(int n);
int	ft_putpointer(unsigned long p);
int	ft_putunsigned(unsigned int n);
int	ft_puthexadecimal(unsigned int n, const char format);

#endif