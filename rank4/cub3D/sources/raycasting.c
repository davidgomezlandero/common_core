/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:38:15 by davigome          #+#    #+#             */
/*   Updated: 2025/06/09 19:13:00 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calculate_projection(t_ray	*ray)
{
	int	lineheight;
	int	drawstart;
	int	drawend;

	lineheight = (int)(HEIGHT / ray->perpwalldist);
	drawstart = -lineheight / 2 + HEIGHT / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + HEIGHT / 2;
	if (drawend >= HEIGHT)
		drawend = HEIGHT - 1;
	ray->drawstart = drawstart;
	ray->drawend = drawend;
	ray->lineheight = lineheight;
}

uint32_t	get_pixel_from_texture(mlx_image_t *img, int x, int y)
{
	int	i;

	i = (y * img->width + x) * 4;
	return (
		(img->pixels[i] << 24)
		| (img->pixels[i + 1] << 16)
		| (img->pixels[i + 2] << 8)
		| (img->pixels[i + 3])
	);
}

void	draw_wall_slice_2(t_map *game, t_ray *ray, int x, t_ray_aux *aux)
{
	if ((ray->side == 0 && ray->raydirx > 0)
		|| (ray->side == 1 && ray->raydiry < 0))
		aux->tex_x = aux->texture->width - aux->tex_x - 1;
	aux->y = ray->drawstart;
	while (aux->y < ray->drawend)
	{
		aux->d = aux->y * 256 - HEIGHT * 128 + ray->lineheight * 128;
		aux->tex_y = (aux->d * aux->texture->height) / ray->lineheight / 256;
		aux->color = get_pixel_from_texture(aux->texture,
				aux->tex_x, aux->tex_y);
		mlx_put_pixel(game->img, x, aux->y, aux->color);
		aux->y++;
	}
}

void	draw_wall_slice(t_map *game, t_ray *ray, int x)
{
	t_ray_aux	aux;

	if (ray->side == 0)
	{
		if (ray->raydirx > 0)
			aux.texture = game->images.ea;
		else
			aux.texture = game->images.we;
	}
	else
	{
		if (ray->raydiry > 0)
			aux.texture = game->images.so;
		else
			aux.texture = game->images.no;
	}
	if (ray->side == 0)
		aux.wall_x = game->player.y + ray->perpwalldist * ray->raydiry;
	else
		aux.wall_x = game->player.x + ray->perpwalldist * ray->raydirx;
	aux.wall_x -= floor(aux.wall_x);
	aux.tex_x = (int)(aux.wall_x * (double)aux.texture->width);
	draw_wall_slice_2(game, ray, x, &aux);
}

void	raycast_all_columns(t_map *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(game, &ray, x);
		calculate_steps_and_sidedist(game, &ray);
		perform_dda(game, &ray);
		calculate_projection(&ray);
		draw_wall_slice(game, &ray, x);
	}
}
