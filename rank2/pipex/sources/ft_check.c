/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:26:09 by davigome          #+#    #+#             */
/*   Updated: 2024/12/28 11:54:17 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_check(char **argv, int argc, t_pipex *pipex, char **envp)
{
	ft_check_narg(argv, argc);
	ft_check_read(argv);
	ft_check_cmds(argv, argc, pipex, envp);
}

void	ft_check_narg(char **argv, int argc)
{
	if (argc != 5)
	{
		ft_printf("Your pipe has not the correct structure\n");
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		if (argc < 6)
		{
			ft_printf("Your pipe has not the correct structure\n");
			exit(1);
		}
	}
}

void	ft_check_read(char **argv)
{
	int	fd;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) != 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			ft_printf("Your first file does not exist\n");
			exit(1);
		}
		close(fd);
	}
}

void	ft_check_cmds(char **argv, int argc, t_pipex *pipex, char **envp)
{
	int		*flag;
	int		j;

	j = 2;
	ft_get_path(pipex, envp);
	flag = malloc(sizeof(int) * 1);
	while (j < argc - 1)
	{
		ft_check_cmds_2(argv, pipex, flag, j);
		if (*flag == 0)
			break ;
		j++;
	}
	if (*flag == 0)
	{
		ft_printf("Some command does not exists or works\n");
		free(flag);
		exit(1);
	}
}

void	ft_check_cmds_2(char **argv, t_pipex *pipex, int *flag, int j)
{
	char	**command;
	int		i;
	char	*line;

	i = -1;
	*flag = 0;
	command = ft_split(argv[j], ' ');
	while (pipex->path[++i])
	{
		line = ft_strjoin(pipex->path[i], "/");
		line = ft_strjoin_g(line, command[0]);
		if (access(line, X_OK) == 0)
		{
			*flag = 1;
			free(line);
			break ;
		}
		free(line);
	}
}
