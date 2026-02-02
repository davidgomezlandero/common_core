/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 01:49:34 by davigome          #+#    #+#             */
/*   Updated: 2024/04/24 02:17:52 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*s: La string desde la que crear la substring.
start: El índice del caracter en ’s’ desde el que
empezar la substring.
len: La longitud máxima de la substring.
Reserva (con malloc(3)) y devuelve una substring de
la string ’s’.
La substring empieza desde el índice ’start’ y
tiene una longitud máxima ’len’.
La substring resultante.
NULL si falla la reserva de memoria.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	cont;

	cont = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (0);
	while (len > cont)
	{
		dst[cont] = s[start + cont];
		cont++;
	}
	dst[cont] = 0;
	return (dst);
}

/*int main()
{
    char *str = "i just want this part #############";
    size_t size = 10;
	str = ft_substr(str,5,size);
	printf("%s", str);
	return 0;
}*/