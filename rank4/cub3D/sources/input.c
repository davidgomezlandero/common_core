/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:40:25 by jotrujil          #+#    #+#             */
/*   Updated: 2025/06/09 17:44:14 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	move_forward(t_map *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * speed;
	new_y = game->player.y + game->player.dir_y * speed;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
}

static void	move_left(t_map *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * speed;
	new_y = game->player.y - game->player.plane_y * speed;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
}

static void	move_backward(t_map *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * speed;
	new_y = game->player.y - game->player.dir_y * speed;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
}

static void	move_right(t_map *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * speed;
	new_y = game->player.y + game->player.plane_y * speed;
	if (!is_wall(game, game->player.x, new_y))
		game->player.y = new_y;
	if (!is_wall(game, new_x, game->player.y))
		game->player.x = new_x;
}

void	handle_input(void *param)
{
	t_map	*game;
	double	speed;

	game = (t_map *)param;
	speed = game->player.move_speed;
	if (game->input.w)
		move_forward(game, speed);
	if (game->input.a)
		move_left(game, speed);
	if (game->input.s)
		move_backward(game, speed);
	if (game->input.d)
		move_right(game, speed);
	if (game->input.right)
		rotate_player(&game->player, +game->player.rot_speed);
	if (game->input.left)
		rotate_player(&game->player, -game->player.rot_speed);
}
