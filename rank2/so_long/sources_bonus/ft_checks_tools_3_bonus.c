/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks_tools_3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:11:51 by davigome          #+#    #+#             */
/*   Updated: 2024/11/28 18:18:21 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_check_path(char **cpy, t_map *game, t_coord now)
{
	if (now.x < 0 || now.y < 0
		|| now.y >= game->size.height || now.x >= game->size.width)
		return ;
	if (cpy[now.y][now.x] == '1' || cpy[now.y][now.x] == 'V'
		|| cpy[now.y][now.x] == 'X')
		return ;
	if (cpy[now.y][now.x] == 'C')
		game->collectibles--;
	if (cpy[now.y][now.x] == 'E')
	{
		game->exit_reach = 0;
		cpy[now.y][now.x] = 'V';
		return ;
	}
	cpy[now.y][now.x] = 'V';
	ft_check_path(cpy, game, (t_coord){now.x + 1, now.y});
	ft_check_path(cpy, game, (t_coord){now.x - 1, now.y});
	ft_check_path(cpy, game, (t_coord){now.x, now.y + 1});
	ft_check_path(cpy, game, (t_coord){now.x, now.y - 1});
}

int	ft_jump(t_map *game)
{
	int	i;

	i = -1;
	while (game->grid[++i])
	{
		if (game->grid[i][0] == '\n')
			return (FAILURE);
	}
	return (SUCCESS);
}
