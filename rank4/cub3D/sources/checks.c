/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:49:36 by davigome          #+#    #+#             */
/*   Updated: 2025/06/03 21:21:59 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_check_start(t_map *game, int i)
{
	t_start	*start;
	int		j;

	start = malloc(sizeof(t_start));
	ft_init_start(start);
	while (game->grid[i])
	{
		j = -1;
		while (game->grid[i][++j])
		{
			ft_check_start_2(game, i, j, start);
		}
		++i;
	}
	if ((start->e == 0 && start->n == 0 && start->s == 0 && start->w == 1)
		|| (start->e == 0 && start->n == 0 && start->s == 1 && start->w == 0)
		|| (start->e == 0 && start->n == 1 && start->s == 0 && start->w == 0)
		|| (start->e == 1 && start->n == 0 && start->s == 0 && start->w == 0))
	{
		free(start);
		return ;
	}
	fprintf(stderr, "Error\nOnly one start point.\n");
	free(start);
	ft_bad_close(game);
}

void	ft_flood_fill(char **cpy, int i, int j, t_map *game)
{
	if (cpy[i][j] == '1' || cpy[i][j] == 'V')
		return ;
	if (!cpy[i + 1])
	{
		fprintf(stderr, "Error\nYour map have not the correct structure.\n");
		ft_free_matrix(cpy);
		ft_bad_close(game);
	}
	cpy[i][j] = 'V';
	ft_aux_flood(cpy, i, j, game);
	ft_flood_fill(cpy, i + 1, j, game);
	ft_flood_fill(cpy, i, j + 1, game);
	ft_flood_fill(cpy, i - 1, j, game);
	ft_flood_fill(cpy, i, j - 1, game);
}

void	ft_check_path(t_map *game, int i)
{
	int		j;
	char	**cpy;

	j = 0;
	while (game->grid[i])
	{
		j = -1;
		while (game->grid[i][++j])
		{
			if (game->grid[i][j] == '0' || game->grid[i][j] == 'N'
				|| game->grid[i][j] == 'S' || game->grid[i][j] == 'W'
				|| game->grid[i][j] == 'E')
			{
				cpy = ft_cpy_matrix(game->grid);
				ft_flood_fill(cpy, i, j, game);
				ft_free_matrix(cpy);
			}
		}
		++i;
	}
}

void	ft_check_map(t_map *game)
{
	int		i;

	i = -1;
	while (game->grid[++i])
	{
		if (game->grid[i][0] != 'N' && game->grid[i][0] != 'S'
			&& game->grid[i][0] != 'W' && game->grid[i][0] != 'E'
			&& game->grid[i][0] != 'F' && game->grid[i][0] != 'C'
			&& game->grid[i][0] != '\n')
			break ;
	}
	ft_invalid_char(game, i);
	ft_check_start(game, i);
	ft_check_path(game, i);
}

void	ft_checks(t_map *game, char **argv)
{
	ft_check_name(argv);
	ft_init_map(game);
	ft_read_map(game, argv);
	ft_check_elements(game);
	ft_check_map(game);
}
