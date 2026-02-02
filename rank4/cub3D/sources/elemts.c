/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elemts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:18:48 by davigome          #+#    #+#             */
/*   Updated: 2025/06/02 20:19:09 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_init_map(t_map *game)
{
	if (!game)
	{
		fprintf(stderr, "Error\nCould not allocate the map");
		exit(EXIT_FAILURE);
	}
	game->grid = NULL;
	game->height = 0;
}

void	ft_init_elem(t_elem *elem)
{
	elem->c = 0;
	elem->f = 0;
	elem->e = 0;
	elem->n = 0;
	elem->s = 0;
	elem->w = 0;
}

void	ft_check_elements_2(t_map *game, t_elem *elem)
{
	if (elem->c > 1 || elem->e > 1 || elem->f > 1
		|| elem->n > 1 || elem->s > 1 || elem->w > 1)
	{
		fprintf(stderr, "Error\nYou must specify each texture one time.\n");
		ft_bad_close(game);
	}
	if (elem->c < 1 || elem->e < 1 || elem->f < 1
		|| elem->n < 1 || elem->s < 1 || elem->w < 1)
	{
		fprintf(stderr, "Error\nYou must specify each texture one time.\n");
		ft_bad_close(game);
	}
}

void	ft_check_elements_rep(t_map *game, int i, t_elem *elem)
{
	if (game->grid[i][0] == 'N')
		++elem->n;
	if (game->grid[i][0] == 'S')
		++elem->s;
	if (game->grid[i][0] == 'W')
		++elem->w;
	if (game->grid[i][0] == 'E')
		++elem->e;
	if (game->grid[i][0] == 'F')
		++elem->f;
	if (game->grid[i][0] == 'C')
		++elem->c;
}
