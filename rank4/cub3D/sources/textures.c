/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:37:57 by davigome          #+#    #+#             */
/*   Updated: 2025/06/09 20:23:44 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*ft_search_texture(t_map *game, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (game->grid[++i])
	{
		if (game->grid[i][0] == c)
		{
			while (game->grid[i][++j] <= 32)
				;
			break ;
		}
	}
	return (ft_substr(game->grid[i], j, ft_strlen(game->grid[i])));
}

void	ft_load_textures(t_map *game)
{
	mlx_texture_t	*texture;
	char			*path;

	path = ft_search_texture(game, 'N');
	texture = mlx_load_png(path);
	if (!texture)
	{
		mlx_terminate(game->mlx);
		free(path);
		ft_bad_close(game);
		exit(EXIT_FAILURE);
	}
	free(path);
	game->images.no = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	ft_load_textures_2(game, texture);
	ft_load_textures_3(game, texture);
	ft_load_textures_4(game, texture);
}

void	ft_load_textures_2(t_map *game, mlx_texture_t *texture)
{
	char	*path;

	path = ft_search_texture(game, 'E');
	texture = mlx_load_png(path);
	if (!texture)
	{
		mlx_terminate(game->mlx);
		free(path);
		ft_bad_close(game);
		exit(EXIT_FAILURE);
	}
	free(path);
	game->images.ea = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
}

void	ft_load_textures_3(t_map *game, mlx_texture_t *texture)
{
	char	*path;

	path = ft_search_texture(game, 'S');
	texture = mlx_load_png(path);
	if (!texture)
	{
		mlx_terminate(game->mlx);
		free(path);
		ft_bad_close(game);
		exit(EXIT_FAILURE);
	}
	free(path);
	game->images.so = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
}

void	ft_load_textures_4(t_map *game, mlx_texture_t *texture)
{
	char	*path;

	path = ft_search_texture(game, 'W');
	texture = mlx_load_png(path);
	if (!texture)
	{
		mlx_terminate(game->mlx);
		free(path);
		ft_bad_close(game);
		exit(EXIT_FAILURE);
	}
	free(path);
	game->images.we = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
}
