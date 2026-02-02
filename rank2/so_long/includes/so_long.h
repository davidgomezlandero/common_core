/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:29:28 by davigome          #+#    #+#             */
/*   Updated: 2024/11/30 16:42:29 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define NAME "so_long"
# define TITRE "So Long"

# define TILE_SIZE 64
# define IMG_SIZE 48

# define WIDTH 1920
# define HEIGHT 1080

//  ERROR MESSAGES//

# define E_FILENAME "The file is not a .ber file.\n"
# define E_NO_INIT "The map does not have a starting point.\n"
# define E_NO_EXIT "The map does not have an exit.\n"
# define E_NO_OBJ "The map does not have any collectible objects.\n"
# define E_MORE_INIT "The map has two or more starting points.\n"
# define E_MORE_EXIT "The map has two or more exits.\n"
# define E_NO_BLOCK "The map is not surrounded by walls or\
 the map is not rectangular. \n"
# define E_NO_PATH "There is no valid path in the map.\n"
# define E_CHAR "The map contains invalid characters.\n"
# define E_PLAYER "The map must contain one player.\n"
# define E_EMPTYLINE "The map contains one or more empty lines.\n"
# define E_NUMBER "The program must receive exactly one valid .ber\
 file as an argmunet.\n"
# define E_CHAR "The map contains invalid characters.\n"

// RETURN VALUES //
# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

// MAP STRUCTURE
typedef struct s_coord
{
	int		x;
	int		y;
}			t_coord;

typedef struct s_size
{
	int			height;
	int			width;
}			t_size;

typedef struct s_player
{
	int			moves;
	t_coord		position;
}			t_player;

typedef struct s_images
{
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*collectibles;
	mlx_image_t	*exit;
}			t_images;
typedef struct s_map
{
	char		**grid;			//STORE THE MAP GRID
	t_size		size;			//WIDTH OF THE MAP AND HEIGHT OF THE MAP
	t_coord		start;			//PLAYER STARTING
	t_coord		exit;			//MAP EXIT
	int			exit_reach;		//MAP EXIT REACHED
	int			collectibles;	//TOTAL NUMBER OF COLLECTIBLES
	int			valid_path;		//FLAG TO INDICATE IF THERE IS A VALID PATH
	mlx_t		*mlx;			//CONTEXT OF MLX
	t_player	player;			//PLAYER INFORMATION
	t_images	images;			//TEXTURES AND IMAGES
}			t_map;

// FT_CHECKS_TOOLS.C //
int		ft_checks(char *map, t_map *game);
void	ft_write_check(char *map, t_map *game);
int		ft_check_ber(char *map);
int		ft_check_no(t_map *game, char c);
int		ft_more(t_map *game, char c);

// FT_CHECKS_TOOLS_2.C //
int		ft_invalid_char(t_map *game);
int		ft_no_rec(t_map *game);
int		ft_no_surrounded(t_map *game);
int		ft_valid_path(t_map *game);
void	ft_cont_collectables(t_map *game);

// FT_CHECK.TOOLS_3.C //
void	ft_check_path(char **cpy, t_map *game, t_coord now);
int		ft_jump(t_map *game);

// FT_TOOLS.C //
char	**ft_cpy_matrix(char **src);

// FT_START_MAP.C //
t_map	*ft_map(char *map, t_map *game);
t_map	*ft_init_map(t_map *game);
t_map	*ft_read_map(char *map, t_map *game);
void	ft_read_2(int fd, char *line, t_map *game);
int		ft_count_lines(char *map, t_map *game);

// FT_INIT_MLX.C //
void	ft_init_mlx(t_map	*game);
void	ft_start(t_map *game);

// FT_MOVES.C //
void	ft_key_hook(mlx_key_data_t keydata, void *param);
void	ft_move_player(t_map *game, int x, int y);
void	ft_finish(t_map *game);
// FT_IMAGES.C //
void	ft_load_textures(t_map *game);
void	ft_load_textures_2(t_map *game, mlx_texture_t *texture);
void	ft_render_map(t_map *game);
void	ft_render_background(t_map *game);

// FT_FREE.C //
void	ft_free_map(t_map	*game);

#endif