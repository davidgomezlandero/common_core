/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:36:53 by davigome          #+#    #+#             */
/*   Updated: 2024/11/30 16:52:36 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*game;

	game = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_UP)
			ft_move_player(game, 0, -1);
		if (keydata.key == MLX_KEY_DOWN)
			ft_move_player(game, 0, 1);
		if (keydata.key == MLX_KEY_LEFT)
			ft_move_player(game, -1, 0);
		if (keydata.key == MLX_KEY_RIGHT)
			ft_move_player(game, 1, 0);
	}
}

void	ft_move_player(t_map *game, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = game->player.position.x + x;
	new_y = game->player.position.y + y;
	if (game->grid[new_y][new_x] == 'E' && game->collectibles <= 0)
		ft_finish(game);
	if (game->grid[new_y][new_x] == 'X')
		ft_lose(game);
	if (game->grid[new_y][new_x] != '1' && game->grid[new_y][new_x] != 'E')
	{
		game->player.moves++;
		ft_printf("Move: %d\n", game->player.moves);
		if (game->grid[new_y][new_x] == 'C')
			game->collectibles--;
		mlx_image_to_window(game->mlx, game->images.floor,
			game->player.position.x * 64, game->player.position.y * 64);
		mlx_image_to_window(game->mlx, game->images.floor,
			new_x * 64, new_y * 64);
		mlx_image_to_window(game->mlx, game->images.player,
			new_x * 64, new_y * 64);
		ft_print_move(game);
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

void	ft_finish(t_map *game)
{
	ft_printf("YOU WIN!\n");
	ft_free_map(game);
	mlx_terminate(game->mlx);
	exit(SUCCESS);
}

void	ft_lose(t_map *game)
{
	ft_printf("YOU LOSE :(.\n");
	ft_free_map(game);
	mlx_terminate(game->mlx);
	exit(SUCCESS);
}

void	ft_print_move(t_map *game)
{
	char	*line;

	line = ft_itoa(game->player.moves);
	line = ft_strjoin("Move: ", line);
	mlx_image_to_window(game->mlx, game->images.wall, 0, 0);
	mlx_image_to_window(game->mlx, game->images.wall, 64, 0);
	mlx_put_string(game->mlx, line, 0, 0);
	free(line);
}
