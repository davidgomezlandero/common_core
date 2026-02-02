/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:49:09 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 13:43:48 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	take_forks_pair(t_args *args, int i)
{
	pthread_mutex_lock(&args->table->philosophers[i]->fork);
	if (!should_continue(args))
		return (0);
	ft_printf(args, 1, i);
	if (args->table->numphilo == 1)
	{
		pthread_mutex_unlock(&args->table->philosophers[i]->fork);
		return (0);
	}
	if (args->table->numphilo == i + 1)
		pthread_mutex_lock(&args->table->philosophers[0]->fork);
	else
		pthread_mutex_lock(&args->table->philosophers[i + 1]->fork);
	if (!should_continue(args))
		return (0);
	ft_printf(args, 1, i);
	return (1);
}

int	take_forks_impair(t_args *args, int i)
{
	if (args->table->numphilo == i + 1)
		pthread_mutex_lock(&args->table->philosophers[0]->fork);
	else
		pthread_mutex_lock(&args->table->philosophers[i + 1]->fork);
	if (!should_continue(args))
		return (0);
	ft_printf(args, 1, i);
	if (args->table->numphilo == 1)
	{
		pthread_mutex_unlock(&args->table->philosophers[i]->fork);
		return (0);
	}
	pthread_mutex_lock(&args->table->philosophers[i]->fork);
	if (!should_continue(args))
		return (0);
	ft_printf(args, 1, i);
	return (1);
}

void	release_forks_pair(t_args *args, int i)
{
	if (args->table->numphilo == i + 1)
		pthread_mutex_unlock(&args->table->philosophers[0]->fork);
	else
		pthread_mutex_unlock(&args->table->philosophers[i + 1]->fork);
	pthread_mutex_unlock(&args->table->philosophers[i]->fork);
}

void	release_forks_impair(t_args *args, int i)
{
	if (args->table->numphilo == i + 1)
		pthread_mutex_unlock(&args->table->philosophers[0]->fork);
	else
		pthread_mutex_unlock(&args->table->philosophers[i + 1]->fork);
	pthread_mutex_unlock(&args->table->philosophers[i]->fork);
}
