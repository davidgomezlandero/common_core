/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:52:45 by davigome          #+#    #+#             */
/*   Updated: 2025/06/09 20:35:38 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_check_elements_3(t_map *game)
{
	int		i;
	int		j;

	i = -1;
	while (game->grid[++i])
	{
		if (game->grid[i][0] != 'N' && game->grid[i][0] != 'S'
			&& game->grid[i][0] != 'W' && game->grid[i][0] != 'E'
			&& game->grid[i][0] != 'F' && game->grid[i][0] != 'C'
			&& game->grid[i][0] != '\n')
			break ;
		j = 1;
		if (game->grid[i][0] == 'N')
			ft_check_n(game, i, j);
		if (game->grid[i][0] == 'S')
			ft_check_s(game, i, j);
		if (game->grid[i][0] == 'W')
			ft_check_w(game, i, j);
		if (game->grid[i][0] == 'E')
			ft_check_e(game, i, j);
		if (game->grid[i][0] == 'F')
			ft_check_f(game, i, j);
		if (game->grid[i][0] == 'C')
			ft_check_c(game, i, j);
	}
}

void	ft_check_elements(t_map *game)
{
	t_elem	*elem;
	int		i;

	i = -1;
	elem = malloc(sizeof(t_elem));
	ft_init_elem(elem);
	while (game->grid[++i])
	{
		if (game->grid[i][0] != 'N' && game->grid[i][0] != 'S'
			&& game->grid[i][0] != 'W' && game->grid[i][0] != 'E'
			&& game->grid[i][0] != 'F' && game->grid[i][0] != 'C'
			&& game->grid[i][0] != '\n')
			break ;
		ft_check_elements_rep(game, i, elem);
	}
	ft_check_elements_2(game, elem);
	free(elem);
	ft_check_elements_3(game);
}

void	ft_invalid_char(t_map *game, int i)
{
	int	j;

	while (game->grid[i])
	{
		j = -1;
		while (game->grid[i][++j])
		{
			if (game->grid[i][j] != '0' && game->grid[i][j] != '1'
				&& game->grid[i][j] != 'N' && game->grid[i][j] != 'S'
				&& game->grid[i][j] != 'E' && game->grid[i][j] != 'W'
				&& game->grid[i][j] > 32)
			{
				fprintf(stderr, "Error\nOnly valid characters in the map.\n");
				ft_bad_close(game);
			}
		}
		++i;
	}
}

void	ft_init_start(t_start *start)
{
	start->e = 0;
	start->n = 0;
	start->s = 0;
	start->w = 0;
}

void	ft_check_start_2(t_map *game, int i, int j, t_start *start)
{
	if (game->grid[i][j] == 'N')
		++start->n;
	if (game->grid[i][j] == 'S')
		++start->s;
	if (game->grid[i][j] == 'E')
		++start->e;
	if (game->grid[i][j] == 'W')
		++start->w;
}
