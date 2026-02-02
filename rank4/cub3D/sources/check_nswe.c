/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nswe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:24:59 by davigome          #+#    #+#             */
/*   Updated: 2025/06/03 21:02:42 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_check_n(t_map *game, int i, int j)
{
	if (game->grid[i][1] != 'O')
	{
		fprintf(stderr, "Error\nThe texture north must be NO.\n");
		ft_bad_close(game);
	}
	if (game->grid[i][j + 1] != 32)
	{
		fprintf(stderr, "Error\nBetween NO and the texture must be a space.\n");
		ft_bad_close(game);
	}
	while (game->grid[i][++j] <= 32)
		;
	if (!game->grid[i][j])
	{
		fprintf(stderr, "Error\nThere is no a path for NO texture.\n");
		ft_bad_close(game);
	}
	while (game->grid[i][++j] > 32 && game->grid[i][j] < 127)
		;
	if (game->grid[i][j] != 10 && game->grid[i][j] != '\0')
	{
		fprintf(stderr, "Error\nOnly the name of the texture ");
		fprintf(stderr, "space and the path.\n");
		ft_bad_close(game);
	}
}

void	ft_check_s(t_map *game, int i, int j)
{
	if (game->grid[i][1] != 'O')
	{
		fprintf(stderr, "Error\nThe texture south must be SO.\n");
		ft_bad_close(game);
	}
	if (game->grid[i][j + 1] != ' ')
	{
		fprintf(stderr, "Error\nBetween SO and the texture must be a space.\n");
		ft_bad_close(game);
	}
	while (game->grid[i][++j] <= 32)
		;
	if (!game->grid[i][j])
	{
		fprintf(stderr, "Error\nThere is no a path for SO texture.\n");
		ft_bad_close(game);
	}
	while (game->grid[i][++j] > 32 && game->grid[i][j] < 127)
		;
	if (game->grid[i][j] != 10 && game->grid[i][j] != '\0')
	{
		fprintf(stderr, "Error\nOnly the name of the texture ");
		fprintf(stderr, "space and the path.\n");
		ft_bad_close(game);
	}
}

void	ft_check_w(t_map *game, int i, int j)
{
	if (game->grid[i][1] != 'E')
	{
		fprintf(stderr, "Error\nThe texture west must be WE.\n");
		ft_bad_close(game);
	}
	if (game->grid[i][j + 1] != ' ')
	{
		fprintf(stderr, "Error\nBetween WE and the texture must be a space.\n");
		ft_bad_close(game);
	}
	while (game->grid[i][++j] <= 32)
		;
	if (!game->grid[i][j])
	{
		fprintf(stderr, "Error\nThere is no a path for WE texture.\n");
		ft_bad_close(game);
	}
	while (game->grid[i][++j] > 32 && game->grid[i][j] < 127)
		;
	if (game->grid[i][j] != 10 && game->grid[i][j] != '\0')
	{
		fprintf(stderr, "Error\nOnly the name of the texture ");
		fprintf(stderr, "space and the path.\n");
		ft_bad_close(game);
	}
}

void	ft_check_e(t_map *game, int i, int j)
{
	if (game->grid[i][1] != 'A')
	{
		fprintf(stderr, "Error\nThe texture west must be EA.\n");
		ft_bad_close(game);
	}
	if (game->grid[i][j + 1] != ' ')
	{
		fprintf(stderr, "Error\nBetween EA and the texture must be a space.\n");
		ft_bad_close(game);
	}
	while (game->grid[i][++j] <= 32)
		;
	if (!game->grid[i][j])
	{
		fprintf(stderr, "Error\nThere is no a path for EA texture.\n");
		ft_bad_close(game);
	}
	while (game->grid[i][++j] > 32 && game->grid[i][j] < 127)
		;
	if (game->grid[i][j] != 10 && game->grid[i][j] != '\0')
	{
		fprintf(stderr, "Error\nOnly the name of the texture ");
		fprintf(stderr, "space and the path.\n");
		ft_bad_close(game);
	}
}
