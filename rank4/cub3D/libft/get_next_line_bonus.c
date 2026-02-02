/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:34:23 by davigome          #+#    #+#             */
/*   Updated: 2025/01/22 15:06:11 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	lean = (char *)malloc(sizeof(char) * (ft_strlen_g(str) - i + 1));
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
	while (!(ft_strchr_g(str, '\n')) && len > 0)
	{
		len = read(fd, buff, BUFFER_SIZE);
		if (len == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[len] = '\0';
		str = ft_strjoin_g(str, buff);
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
	static char	*str[4096];
	char		*out;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	str[fd] = ft_join(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	out = ft_out(str[fd]);
	str[fd] = ft_clean(str[fd]);
	return (out);
}

/* int main(int ac, char **av)
{
    int fd1;
	int fd2;
	int fd3;
    char *line1;
	char *line2;
	char *line3;
	int	i;

	i = 1;
	fd1 = open(av[1], O_RDONLY); 
	fd2 = open(av[2], O_RDONLY);
	fd3 = open(av[3], O_RDONLY);
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	while (line1 || line2 || line3)
	{
//	        fd = open(av[i], O_RDONLY);
	        if (line1)
			{
	            printf("%s", line1);
				line1 = get_next_line(fd1);
	        }
	        if (line2)
			{
	            printf("%s", line2);
				line2 = get_next_line(fd2);
	        }
	    	if (line3)
			{
	            printf("%s", line3);
				line3 = get_next_line(fd3);
	        }
	}
	close (fd1);
	close (fd3);
	close (fd2);
    return 0;
} */

/* int main(int ac, char **av)
{
    int fd;
    char *line;
	int	i;

	i = 1;
	
	while (av[i])
	{
	    if (av[i])
		{
	        fd = open(av[i], O_RDONLY);
	        if (fd == -1)
			{
	            printf("%s\n", av[i]);
	            return 0;
	        }
				else
			{
	            line = get_next_line(fd);
	            while (line)
				{
	                printf("%s\n", line);
	                free(line);
	                line = get_next_line(fd);
	            }
	            close(fd);
	        }
	    }
		if (fd == 0)
		{
	        line = get_next_line(0);
	        while (line) 
			{
	            printf("%s", line);
            	free(line);
        	    line = get_next_line(0);
    	    }
	    }
		i++;
	}
    return 0;
} */