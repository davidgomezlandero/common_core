/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:21:12 by davigome          #+#    #+#             */
/*   Updated: 2024/12/28 11:49:03 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**here;
	int		**pipes;
	char	**path;
	int		num_pipes;
}		t_pipex;

// FT_CHECK.C //
void	ft_check(char **argv, int argc, t_pipex *pipex, char **envp);
void	ft_check_narg(char **argv, int argc);
void	ft_check_read(char **argv);
void	ft_check_cmds(char **argv, int argc, t_pipex *pipex, char **envp);
void	ft_check_cmds_2(char **argv, t_pipex *pipex, int *flag, int j);

// FT_CHECK_2.C //
void	ft_init_pipex(t_pipex *pipex);
void	ft_get_path(t_pipex *pipex, char **envp);

// FT_FREES.C //
void	ft_free(t_pipex *pipex);
void	ft_free_matrix(char	**matrix);

// PIPEX.C //
void	ft_allocate_pipes(int argc, t_pipex *pipex);
void	ft_init(char **argv, int argc, t_pipex *pipex);
void	ft_file(char **argv, t_pipex *pipex, int argc);
void	ft_child_proccess(t_pipex *pipex, int fd_in, char **argv);

#endif