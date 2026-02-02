/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:15:29 by davigome          #+#    #+#             */
/*   Updated: 2024/11/27 22:56:47 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
