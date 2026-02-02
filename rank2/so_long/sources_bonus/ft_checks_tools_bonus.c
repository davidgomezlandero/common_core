/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks_tools_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:15:03 by davigome          #+#    #+#             */
/*   Updated: 2024/11/30 16:15:41 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	ft_checks(char *map, t_map *game)
{
	int	i;

	i = 0;
	if (ft_check_ber(map) == FAILURE)
		i++;
	if (ft_jump(game) == FAILURE)
		ft_write_check(map, game);
	if (ft_check_no(game, 'E') == FAILURE
		|| ft_check_no(game, 'C') == FAILURE
		|| ft_check_no(game, 'P') == FAILURE)
		i++;
	if (ft_more(game, 'E') == FAILURE
		|| ft_more(game, 'P') == FAILURE
		|| ft_invalid_char(game) == FAILURE)
		i++;
	if (ft_no_rec(game) == FAILURE
		|| ft_no_surrounded(game) == FAILURE)
	{
		ft_printf(E_NO_BLOCK);
		exit(FAILURE);
	}
	if (ft_valid_path(game) == FAILURE)
		i++;
	return (i);
}

void	ft_write_check(char *map, t_map *game)
{
	if (ft_jump(game) == FAILURE)
	{
		ft_printf(E_EMPTYLINE);
		exit(FAILURE);
	}
	if (ft_check_ber(map) == FAILURE)
		ft_printf(E_FILENAME);
	if (ft_check_no(game, 'E') == FAILURE)
		ft_printf(E_NO_EXIT);
	if (ft_check_no(game, 'C') == FAILURE)
		ft_printf(E_NO_OBJ);
	if (ft_check_no(game, 'P') == FAILURE)
		ft_printf(E_NO_INIT);
	if (ft_more(game, 'E') == FAILURE)
		ft_printf(E_MORE_EXIT);
	if (ft_more(game, 'P') == FAILURE)
		ft_printf(E_MORE_INIT);
	if (ft_invalid_char(game) == FAILURE)
		ft_printf(E_CHAR);
	if (ft_valid_path(game) == FAILURE)
		ft_printf(E_NO_PATH);
}

int	ft_check_ber(char *map)
{
	size_t	len;

	len = ft_strlen(map);
	if (map[len - 1] != 'r' || map[len - 2] != 'e'
		|| map[len - 3] != 'b' || map[len - 4] != '.')
		return (FAILURE);
	return (SUCCESS);
}

int	ft_check_no(t_map *game, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (game->grid[i])
	{
		if (ft_strchr(game->grid[i], c))
		{
			if (c == 'P')
			{
				while (game->grid[i][j] != 'P')
					j++;
				game->start.x = j;
				game->start.y = i;
				game->player.position.x = j;
				game->player.position.y = i;
			}
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

int	ft_more(t_map *game, char c)
{
	int	i;
	int	cont;
	int	j;

	cont = 0;
	i = 0;
	while (game->grid[i])
	{
		j = 0;
		while (game->grid[i][j] != '\0')
		{
			if (game->grid[i][j] == c)
				cont++;
			if (c == 'E')
			{
				game->exit.x = j;
				game->exit.y = i;
			}
			j++;
			if (cont > 1)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
