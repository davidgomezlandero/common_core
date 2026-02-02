/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:04:00 by davigome          #+#    #+#             */
/*   Updated: 2024/11/30 14:47:35 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_invalid_char(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->grid[i])
	{
		j = 0;
		while (game->grid[i][j] != '\0' && game->grid[i][j] != '\n')
		{
			if (game->grid[i][j] != 'P' && game->grid[i][j] != '0'
				&& game->grid[i][j] != '1' && game->grid[i][j] != 'E'
				&& game->grid[i][j] != 'C')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_no_rec(t_map *game)
{
	int	i;

	i = 0;
	if (!game || !game->grid || !game->grid[0])
		return (FAILURE);
	game->size.width = ft_strlen(game->grid[i]);
	while (game->grid[i])
	{
		if (game->size.width != (int)ft_strlen(game->grid[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_no_surrounded(t_map *game)
{
	int	i;
	int	height;
	int	j;

	j = 0;
	i = 0;
	while (game->grid[i])
		i++;
	height = i;
	game->size.height = height;
	i = 0;
	while (game->grid[0][j] != '\0' && game->grid[0][j] != '\n')
		if (game->grid[0][j++] != '1')
			return (FAILURE);
	j = 0;
	while (game->grid[height - 1][j] != '\0'
		&& game->grid[height - 1][j] != '\n')
		if (game->grid[height - 1][j++] != '1')
			return (FAILURE);
	j = 0;
	while (++j < height)
		if (game->grid[j][0] != '1' ||
		game->grid[j][ft_strlen(game->grid[j]) - 1] != '1')
			return (FAILURE);
	return (SUCCESS);
}

void	ft_cont_collectables(t_map *game)
{
	int	i;
	int	j;
	int	cont;

	i = 0;
	j = 0;
	cont = 0;
	while (game->grid[i])
	{
		j = 0;
		while (game->grid[i][j])
		{
			if (game->grid[i][j] == 'C')
				cont++;
			j++;
		}
		i++;
	}
	game->collectibles = cont;
}

int	ft_valid_path(t_map *game)
{
	char	**cpy;
	int		i;

	i = -1;
	cpy = NULL;
	cpy = ft_cpy_matrix(game->grid);
	ft_cont_collectables(game);
	ft_check_path(cpy, game, game->start);
	while (cpy[++i])
		free(cpy[i]);
	free(cpy);
	if (game->collectibles == 0 && game->exit_reach == 0)
		return (SUCCESS);
	return (FAILURE);
}
