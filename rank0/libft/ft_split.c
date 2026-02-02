/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:04:18 by davigome          #+#    #+#             */
/*   Updated: 2024/06/25 11:10:21 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*next_word(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

static char	*end_of_word(char const *s, char c)
{
	while (*s && *s != c)
		s++;
	return ((char *)s);
}

static char	**ft_chains(int word_count, char const *s, char c, char **result)
{
	char	*end;
	int		i;

	i = 0;
	while (i < word_count)
	{
		s = next_word(s, c);
		end = end_of_word(s, c);
		result[i] = ft_substr(s, 0, end - s);
		if (!result[i])
		{
			while (i >= 0)
				free(result[i--]);
			free(result);
			return (NULL);
		}
		s = end;
		i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	ft_chains(word_count, s, c, result);
	result[word_count] = NULL;
	return (result);
}
