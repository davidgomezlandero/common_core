/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:36:24 by davigome          #+#    #+#             */
/*   Updated: 2025/06/10 16:49:28 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_init_mlx(t_map	*game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!game->mlx)
	{
		fprintf(stderr, "Error:\nCould not init MLX42");
		ft_bad_close(game);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		fprintf(stderr, "Error:\nCould not create image");
		ft_bad_close(game);
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	init_player_3(t_map *game, int x, int y)
{
	if (game->grid[y][x] == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->grid[y][x] == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	init_player_2(t_map *game, int x, int y)
{
	game->player.x = (double)x + 0.5;
	game->player.y = (double)y + 0.5;
	if (game->grid[y][x] == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->grid[y][x] == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	init_player_3(game, x, y);
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.17;
}

void	init_player_position(t_map *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->grid[y] && (game->grid[y][0] == 'N' || game->grid[y][0] == 'S'
		|| game->grid[y][0] == 'E' || game->grid[y][0] == 'W'
		|| game->grid[y][0] == 'F' || game->grid[y][0] == 'C'
		|| game->grid[y][0] == '\n'))
		y++;
	while (game->grid[y])
	{
		x = 0;
		while (game->grid[y][x])
		{
			if (game->grid[y][x] == 'N' || game->grid[y][x] == 'S'
				|| game->grid[y][x] == 'E' || game->grid[y][x] == 'W')
			{
				init_player_2(game, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	ft_run(t_map *game)
{
	ft_init_mlx(game);
	ft_load_textures(game);
	init_player_position(game);
	mlx_loop_hook(game->mlx, &update_game, game);
	mlx_key_hook(game->mlx, &key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
