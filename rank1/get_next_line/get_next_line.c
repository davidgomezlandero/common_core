/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 09:24:20 by davigome          #+#    #+#             */
/*   Updated: 2024/08/31 16:36:08 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>

char	*ft_clean(char *str)
{
	char	*lean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	lean = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!lean)
		return (NULL);
	i++;
	while (str[i])
		lean[j++] = str[i++];
	lean[j] = '\0';
	free(str);
	return (lean);
}

char	*ft_join(int fd, char *str)
{
	ssize_t		len;
	char		*buff;

	len = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!(ft_strchr(str, '\n')) && len > 0)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[len] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_out(char *str)
{
	int			i;
	char		*out;

	i = 0;
	if (str[i] == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	out = (char *)malloc(sizeof(char) * (i + 2));
	if (!out)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		out[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		out[i] = '\n';
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*out;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = ft_join(fd, str);
	if (!str)
		return (NULL);
	out = ft_out(str);
	str = ft_clean(str);
	return (out);
}

/* int main(int ac, char **av) {
    int fd;
    char *line;

    if (ac == 2) 
	{
        fd = open(av[1], O_RDONLY);
        if (fd == -1) 
		{
            printf("%s\n", av[1]);
            return 0;
        } else 
		{
            line = get_next_line(fd);
            while (line) 
			{
                printf("%s", line);
                free(line);
                line = get_next_line(fd);
            }
            close(fd);
        }
    } 
	else 
	{
        line = get_next_line(0);  
        while (line) 
		{
            printf("%s", line);
            free(line);
            line = get_next_line(0);
        }
    }
    return 0;
}
 */