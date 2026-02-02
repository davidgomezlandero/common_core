/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:35:15 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 13:20:24 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_dead_2(t_args *args, struct timeval tv, int i)
{
	long long	aux;

	aux = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (args->table->philosophers[++i])
	{
		pthread_mutex_lock(&args->table->philosophers[i]->eat);
		if (args->table->time_die
			< (aux - args->table->philosophers[i]->last_eat))
		{
			pthread_mutex_unlock(&args->table->philosophers[i]->eat);
			if (args->table->philosophers[i]->lunchs == 0)
				break ;
			pthread_mutex_lock(&args->table->mutex_flag);
			args->table->flag = 0;
			pthread_mutex_unlock(&args->table->mutex_flag);
			ft_printf(args, 5, i);
			break ;
		}
		else
			pthread_mutex_unlock(&args->table->philosophers[i]->eat);
	}
}

void	ft_dead_3(t_args *args, struct timeval tv)
{
	pthread_mutex_lock(&args->table->mutex_init);
	args->table->init = 0;
	pthread_mutex_unlock(&args->table->mutex_init);
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&args->table->mutex_start);
	args->table->time_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_unlock(&args->table->mutex_start);
}

int	ft_checkeats(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->table->numphilo)
	{
		pthread_mutex_lock(&args->table->philosophers[i]->mutex_lunchs);
		if (args->table->philosophers[i]->lunchs > 0)
		{
			pthread_mutex_unlock(&args->table->philosophers[i]->mutex_lunchs);
			return (1);
		}
		pthread_mutex_unlock(&args->table->philosophers[i]->mutex_lunchs);
	}
	return (0);
}

void	*ft_dead(void *data)
{
	t_args			*args;
	struct timeval	tv;
	int				i;

	args = (t_args *)data;
	i = -1;
	ft_dead_3(args, tv);
	while (args->table->philosophers[++i])
	{
		pthread_mutex_lock(&args->table->philosophers[i]->eat);
		args->table->philosophers[i]->last_eat = args->table->time_start;
		pthread_mutex_unlock(&args->table->philosophers[i]->eat);
	}
	while (args->table->flag == -1)
	{
		i = -1;
		gettimeofday(&tv, NULL);
		ft_dead_2(args, tv, i);
		if (args->eats != -1)
			if (ft_checkeats(args) == 0)
				break ;
	}
	return (NULL);
}
