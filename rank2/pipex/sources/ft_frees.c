/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:40:01 by davigome          #+#    #+#             */
/*   Updated: 2024/12/28 11:47:23 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->path[++i])
		free(pipex->path[i]);
	free(pipex->here);
	free(pipex->path);
	free(pipex->pipes);
	free(pipex);
}

void	ft_free_matrix(char	**matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}
