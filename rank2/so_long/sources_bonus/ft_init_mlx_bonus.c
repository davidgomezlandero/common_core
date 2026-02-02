/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:31:20 by davigome          #+#    #+#             */
/*   Updated: 2024/11/28 16:27:05 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_start(t_map *game)
{
	ft_init_mlx(game);
	ft_load_textures(game);
	ft_render_map(game);
	mlx_key_hook(game->mlx, ft_key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	ft_free_map(game);
}

void	ft_init_mlx(t_map	*game)
{
	game->mlx = mlx_init(game->size.width * TILE_SIZE,
			game->size.height * TILE_SIZE, TITRE, true);
	if (!game->mlx)
	{
		ft_printf("Error:\nCould not init MLX42");
		exit(ERROR);
	}
}
