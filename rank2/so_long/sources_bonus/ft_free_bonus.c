/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:15:29 by davigome          #+#    #+#             */
/*   Updated: 2024/11/28 16:26:58 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_free_map(t_map	*game)
{
	int		i;

	i = 0;
	if (game->grid[i])
	{
		while (i < game->size.height)
		{
			free(game->grid[i]);
			i++;
		}
		free(game->grid);
	}
	free(game);
}
