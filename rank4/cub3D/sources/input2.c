/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:33:32 by jotrujil          #+#    #+#             */
/*   Updated: 2025/06/09 20:34:12 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	rotate_player(t_player *p, double dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	angle = dir * p->rot_speed;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

int	is_wall(t_map *game, double x, double y)
{
	return (
		game->grid[(int)(y)][(int)(x)] == '1' ||
		game->grid[(int)(y + COLLISION_MARGIN)][(int)(x)] == '1' ||
		game->grid[(int)(y - COLLISION_MARGIN)][(int)(x)] == '1' ||
		game->grid[(int)(y)][(int)(x + COLLISION_MARGIN)] == '1' ||
		game->grid[(int)(y)][(int)(x - COLLISION_MARGIN)] == '1' ||
		game->grid[(int)(y + COLLISION_MARGIN)]
			[(int)(x + COLLISION_MARGIN)] == '1' ||
		game->grid[(int)(y - COLLISION_MARGIN)]
			[(int)(x - COLLISION_MARGIN)] == '1'
	);
}
