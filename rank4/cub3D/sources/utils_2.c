/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:06:27 by davigome          #+#    #+#             */
/*   Updated: 2025/06/03 15:00:36 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_count_lines(char *map, t_map *game)
{
	char	*line;
	int		len;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Error\nCould not open the file to count lines.\n");
		ft_bad_close(game);
	}
	line = get_next_line(fd);
	len = 0;
	while (line)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->height = len;
	return (len);
}

void	ft_free_map(t_map *game)
{
	int	i;

	i = -1;
	if (!game)
		return ;
	if (game->grid)
	{
		while (++i < game->height && game->grid[i])
			free(game->grid[i]);
		free(game->grid);
	}
	free(game);
}

void	ft_read_2(int fd, char *line, t_map *game)
{
	int	i;

	i = 0;
	while (line)
	{
		if (line[0] == '\n')
			game->grid[i] = ft_strdup("\n");
		else if (line[ft_strlen(line) - 1] == '\n' )
			game->grid[i] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			game->grid[i] = ft_strdup(line);
		if (!game->grid[i])
		{
			fprintf(stderr, "Error\nCould not duplicate line.\n");
			free(line);
			ft_bad_close(game);
		}
		free(line);
		i++;
		line = get_next_line(fd);
	}
	game->grid[i] = NULL;
}

void	ft_read_map(t_map *game, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Error\nCould not open the file properly.\n");
		exit(EXIT_FAILURE);
	}
	game->grid = malloc(sizeof(char *) * (ft_count_lines(argv[1], game) + 1));
	if (!game->grid)
	{
		fprintf(stderr, "Error\nCould not allocate memory for the grid.\n");
		ft_bad_close(game);
	}
	line = get_next_line(fd);
	if (!line)
	{
		fprintf(stderr, "Error\nThe map is empty\n");
		ft_bad_close(game);
	}
	ft_read_2(fd, line, game);
	close(fd);
}

void	ft_check_name(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (argv[1][len - 1] != 'b' || argv[1][len - 2] != 'u'
		|| argv[1][len - 3] != 'c' || argv[1][len - 4] != '.')
	{
		fprintf(stderr, "Error\nThe map must end with .cub.\n");
		exit(EXIT_FAILURE);
	}
}
