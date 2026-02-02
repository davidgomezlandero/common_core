/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:13:24 by davigome          #+#    #+#             */
/*   Updated: 2025/06/02 21:26:31 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_aux_flood(char **cpy, int i, int j, t_map *game)
{
	if ((cpy[i][j + 1] != '0' && cpy[i][j + 1] != 'N'
		&& cpy[i][j + 1] != 'S' && cpy[i][j + 1] != 'E'
		&& cpy[i][j + 1] != 'W' && cpy[i][j + 1] != 'V'
		&& cpy[i][j + 1] != '1') || (cpy[i][j - 1] != '0'
		&& cpy[i][j - 1] != 'N' && cpy[i][j - 1] != 'S'
		&& cpy[i][j - 1] != 'E' && cpy[i][j - 1] != 'W'
		&& cpy[i][j - 1] != 'V' && cpy[i][j - 1] != '1')
		|| (cpy[i + 1][j] != '0' && cpy[i + 1][j] != 'N'
		&& cpy[i + 1][j] != 'S' && cpy[i + 1][j] != 'E'
		&& cpy[i + 1][j] != 'W' && cpy[i + 1][j] != 'V'
		&& cpy[i + 1][j] != '1') || (cpy[i - 1][j] != '0'
		&& cpy[i - 1][j] != 'N' && cpy[i - 1][j] != 'S'
		&& cpy[i - 1][j] != 'E' && cpy[i - 1][j] != 'W'
		&& cpy[i - 1][j] != 'V' && cpy[i - 1][j] != '1'))
	{
		fprintf(stderr, "Error\nYour map have not the correct structure.\n");
		ft_free_matrix(cpy);
		ft_bad_close(game);
	}
}
