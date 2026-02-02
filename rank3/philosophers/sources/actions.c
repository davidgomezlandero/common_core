/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:40 by davigome          #+#    #+#             */
/*   Updated: 2025/05/17 10:03:57 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	should_continue(t_args *args)
{
	int	result;

	pthread_mutex_lock(&args->table->mutex_flag);
	result = args->table->flag;
	pthread_mutex_unlock(&args->table->mutex_flag);
	return (result);
}

void	eat(t_args *args, int i)
{
	struct timeval	tv;
	long long		aux;

	ft_printf(args, 2, i);
	gettimeofday(&tv, NULL);
	aux = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_lock(&args->table->philosophers[i]->eat);
	args->table->philosophers[i]->last_eat = aux;
	pthread_mutex_unlock(&args->table->philosophers[i]->eat);
	if (!should_continue(args))
		return ;
	usleep(0.95 * args->table->time_eat * 1000);
}

void	sleep_and_think(t_args *args, int i)
{
	ft_printf(args, 3, i);
	usleep(0.95 * args->table->time_sleep * 1000);
	if (!should_continue(args))
		return ;
	ft_printf(args, 4, i);
}
