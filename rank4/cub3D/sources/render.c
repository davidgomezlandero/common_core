/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:16:51 by jotrujil          #+#    #+#             */
/*   Updated: 2025/06/09 12:14:11 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_background(t_map *game)
{
	uint32_t	c_color;
	uint32_t	f_color;
	int			x;
	int			y;

	c_color = (game->ceiling_r << 24) | (game->ceiling_g << 16)
		| (game->ceiling_b << 8) | 255;
	f_color = (game->floor_r << 24) | (game->floor_g << 16)
		| (game->floor_b << 8) | 255;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, c_color);
			else
				mlx_put_pixel(game->img, x, y, f_color);
			x++;
		}
		y++;
	}
}

void	draw_vertical_line(mlx_image_t *img, t_line line)
{
	int	y;

	if (!img)
		return ;
	y = line.y_start;
	while (y <= line.y_end)
	{
		if (y >= 0 && y < (int)img->height && line.x >= 0
			&& line.x < (int)img->width)
			mlx_put_pixel(img, line.x, y, line.color);
		y++;
	}
}

void	draw_column(t_map *game, int x, int start, int end)
{
	t_line	line;

	line.x = x;
	line.y_start = start;
	line.y_end = end;
	line.color = 0xFFFFFFFF;
	draw_vertical_line(game->img, line);
}

void	update_game(void *param)
{
	t_map	*game;

	game = (t_map *)param;
	handle_input(game);
	draw_background(game);
	raycast_all_columns(game);
}
