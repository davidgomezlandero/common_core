/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:47:03 by davigome          #+#    #+#             */
/*   Updated: 2025/06/04 13:36:34 by jotrujil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_color_value(t_map *game, int i, int *j)
{
	int	aux;
	int	value;

	aux = *j;
	ft_check_text_num(game, i, *j);
	while (game->grid[i][*j] >= '0' && game->grid[i][*j] <= '9')
		(*j)++;
	value = ft_atoi(&game->grid[i][aux]);
	return (value);
}

static void	assign_floor_color(t_map *game, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		fprintf(stderr, "Error\nThe texture of f is num,num,num and ");
		fprintf(stderr, "num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
	game->floor_r = (uint8_t)r;
	game->floor_g = (uint8_t)g;
	game->floor_b = (uint8_t)b;
}

void	ft_check_f(t_map *game, int i, int j)
{
	int	r;
	int	g;
	int	b;

	j = 0;
	ft_check_text_space(game, i, j);
	while (game->grid[i][++j] <= 32)
		;
	r = get_color_value(game, i, &j);
	ft_check_text_comma(game, 0, i, j++);
	g = get_color_value(game, i, &j);
	ft_check_text_comma(game, 1, i, j++);
	b = get_color_value(game, i, &j);
	ft_check_text_comma(game, 2, i, j);
	assign_floor_color(game, r, g, b);
	ft_check_next(game, i, j);
}

static void	assign_ceiling_color(t_map *game, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		fprintf(stderr, "Error\nThe texture of c is num,num,num and ");
		fprintf(stderr, "num must be between 0 and 255, both include.\n");
		ft_bad_close(game);
	}
	game->ceiling_r = (uint8_t)r;
	game->ceiling_g = (uint8_t)g;
	game->ceiling_b = (uint8_t)b;
}

void	ft_check_c(t_map *game, int i, int j)
{
	int	r;
	int	g;
	int	b;

	j = 0;
	ft_check_text_space(game, i, j);
	while (game->grid[i][++j] <= 32)
		;
	r = get_color_value(game, i, &j);
	ft_check_text_comma(game, 0, i, j++);
	g = get_color_value(game, i, &j);
	ft_check_text_comma(game, 1, i, j++);
	b = get_color_value(game, i, &j);
	ft_check_text_comma(game, 2, i, j);
	assign_ceiling_color(game, r, g, b);
	ft_check_next(game, i, j);
}
