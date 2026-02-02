/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:28:29 by davigome          #+#    #+#             */
/*   Updated: 2024/11/30 15:47:06 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_map	*game;

	game = NULL;
	if (argc != 2)
	{
		ft_printf("Error:\n");
		ft_printf(E_NUMBER);
		return (FAILURE);
	}
	if (argc == 2)
	{
		game = ft_map(argv[1], game);
		if (ft_checks(argv[1], game) >= 1)
		{
			ft_printf("Error:\n");
			ft_write_check(argv[1], game);
			return (FAILURE);
		}
	}
	ft_start(game);
	return (SUCCESS);
}
