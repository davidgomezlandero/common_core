/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:38:40 by davigome          #+#    #+#             */
/*   Updated: 2025/06/09 19:38:50 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*game;

	game = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W)
		game->input.w = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_S)
		game->input.s = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_A)
		game->input.a = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_D)
		game->input.d = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_LEFT)
		game->input.left = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_RIGHT)
		game->input.right = (keydata.action != MLX_RELEASE);
}
