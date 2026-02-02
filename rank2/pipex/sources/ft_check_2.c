/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:47:47 by davigome          #+#    #+#             */
/*   Updated: 2024/12/28 11:51:15 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_init_pipex(t_pipex *pipex)
{
	pipex->here = NULL;
	pipex->pipes = NULL;
	pipex->path = NULL;
}

void	ft_get_path(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", ft_strlen("PATH=")) == 0)
		{
			pipex->path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
}
