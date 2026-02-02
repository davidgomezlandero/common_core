/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:34:57 by davigome          #+#    #+#             */
/*   Updated: 2025/02/12 18:38:22 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Obtein the actual user with orange colour*/
static char	*ms_get_user(t_prompt prompt)
{
	char	**user;
	char	*temp;

	temp = NULL;
	user = NULL;
	ms_get_exec(&user, "/usr/bin/whoami", "whoami", prompt.envp);
	if (!user)
		user = ms_add_end_env(user, "guest");
	temp = ft_strjoin(GREEN, *user);
	ft_free_matrix(user);
	return (temp);
}

static char	*ms_get_home(t_prompt prompt)
{
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("no");
	home = ms_get_env("HOME", prompt.envp, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(temp);
	}
	free(home);
	return (pwd);
}

char	*ms_get_prompt(t_prompt prompt)
{
	char	*temp[2];
	char	*aux;

	temp[0] = ms_get_user(prompt);
	temp[1] = ft_strjoin(temp[0], "@ms:");
	free(temp[0]);
	aux = ms_get_home(prompt);
	temp[0] = ft_strjoin(temp[1], ORANGE);
	free(temp[1]);
	temp[1] = ft_strjoin(temp[0], aux);
	free(aux);
	free(temp[0]);
	temp[0] = ft_strjoin(temp[1], DEFAULT);
	free(temp[1]);
	temp[1] = ft_strjoin(temp[0], " $ ");
	free(temp[0]);
	return (temp[1]);
}
