/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:46:22 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 13:30:17 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_pair_2(t_args *args, int i)
{
	while (1)
	{
		pthread_mutex_lock(&args->table->mutex_flag);
		if (args->table->flag != -1)
		{
			pthread_mutex_unlock(&args->table->mutex_flag);
			break ;
		}
		pthread_mutex_unlock(&args->table->mutex_flag);
		if (!take_forks_pair(args, i))
			break ;
		eat(args, i);
		release_forks_pair(args, i);
		if (!should_continue(args))
			break ;
		sleep_and_think(args, i);
		pthread_mutex_lock(&args->table->philosophers[i]->mutex_lunchs);
		if (--args->table->philosophers[i]->lunchs == 0)
		{
			pthread_mutex_unlock(&args->table->philosophers[i]->mutex_lunchs);
			break ;
		}
		else
			pthread_mutex_unlock(&args->table->philosophers[i]->mutex_lunchs);
	}
}

void	ft_pair(t_args *args, int i)
{
	while (1)
	{
		pthread_mutex_lock(&args->table->mutex_init);
		if (args->table->init != -1)
		{
			pthread_mutex_unlock(&args->table->mutex_init);
			break ;
		}
		pthread_mutex_unlock(&args->table->mutex_init);
		usleep(100);
	}
	ft_pair_2(args, i);
}

void	ft_impair_2(t_args *args, int i)
{
	while (1)
	{
		pthread_mutex_lock(&args->table->mutex_flag);
		if (args->table->flag != -1)
		{
			pthread_mutex_unlock(&args->table->mutex_flag);
			break ;
		}
		pthread_mutex_unlock(&args->table->mutex_flag);
		if (!take_forks_impair(args, i))
			break ;
		eat(args, i);
		release_forks_impair(args, i);
		if (!should_continue(args))
			break ;
		sleep_and_think(args, i);
		pthread_mutex_lock(&args->table->philosophers[i]->mutex_lunchs);
		if (--args->table->philosophers[i]->lunchs == 0)
		{
			pthread_mutex_unlock(&args->table->philosophers[i]->mutex_lunchs);
			break ;
		}
		else
			pthread_mutex_unlock(&args->table->philosophers[i]->mutex_lunchs);
	}
}

void	ft_impair(t_args *args, int i)
{
	while (1)
	{
		pthread_mutex_lock(&args->table->mutex_init);
		if (args->table->init != -1)
		{
			pthread_mutex_unlock(&args->table->mutex_init);
			break ;
		}
		pthread_mutex_unlock(&args->table->mutex_init);
		usleep(100);
	}
	if (args->table->time_die > args->table->time_eat)
		ft_impair_2(args, i);
}

void	*ft_philo(void *data)
{
	t_args	*args;
	int		i;

	args = (t_args *)data;
	pthread_mutex_lock(&args->table->id_philo);
	i = ++args->idphilo;
	pthread_mutex_unlock(&args->table->id_philo);
	while (1)
	{
		pthread_mutex_lock(&args->table->mutex_init);
		if (args->table->init != -1)
		{
			pthread_mutex_unlock(&args->table->mutex_init);
			break ;
		}
		pthread_mutex_unlock(&args->table->mutex_init);
		usleep(100);
	}
	if ((i + 1) % 2 == 0)
		usleep(10);
	if ((i + 1) % 2 == 0)
		ft_pair(args, i);
	else
		ft_impair(args, i);
	return (NULL);
}
