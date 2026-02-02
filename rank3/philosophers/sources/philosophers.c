/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:14:57 by davigome          #+#    #+#             */
/*   Updated: 2025/05/19 13:29:16 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_printf(t_args *args, int type, int i)
{
	pthread_mutex_lock(&args->table->mutex_printf);
	if (type == 1)
		printf("%lld %i has taken a fork\n", ft_time(args),
			args->table->philosophers[i]->name);
	else if (type == 2)
		printf("%lld %i is eating\n", ft_time(args),
			args->table->philosophers[i]->name);
	else if (type == 3)
		printf("%lld %i is sleeping\n", ft_time(args),
			args->table->philosophers[i]->name);
	else if (type == 4)
		printf("%lld %i is thinking\n", ft_time(args),
			args->table->philosophers[i]->name);
	else if (type == 5)
		printf("%lld %i died\n", ft_time(args),
			args->table->philosophers[i]->name);
	pthread_mutex_unlock(&args->table->mutex_printf);
}

void	ft_init(t_args *args, char **argv, int argc)
{
	int	i;

	i = -1;
	args->table->philosophers = malloc(
			sizeof(t_philo) * (args->table->numphilo + 1));
	args->table->philosophers[args->table->numphilo] = NULL;
	while (++i < args->table->numphilo)
	{
		args->table->philosophers[i] = malloc(sizeof(t_philo));
		pthread_mutex_init(&args->table->philosophers[i]->fork, NULL);
		pthread_mutex_init(&args->table->philosophers[i]->mutex_lunchs, NULL);
		pthread_mutex_init(&args->table->philosophers[i]->eat, NULL);
		if (argc == 6)
		{
			args->table->philosophers[i]->lunchs = ft_atoi(argv[5]);
			args->eats = ft_atoi(argv[5]);
		}
		else
		{
			args->eats = -1;
			args->table->philosophers[i]->lunchs = -1;
		}
	}
}

void	ft_start(t_args *args)
{
	int	i;

	i = -1;
	args->idphilo = -1;
	args->table->init = -1;
	args->table->flag = -1;
	while (++i < args->table->numphilo)
	{
		args->table->philosophers[i]->name = i + 1;
		pthread_create(&args->table->philosophers[i]->id, NULL, ft_philo, args);
	}
	pthread_create(&args->table->dead, NULL, ft_dead, args);
	i = -1;
	while (++i < args->table->numphilo)
		pthread_join(args->table->philosophers[i]->id, NULL);
	pthread_join(args->table->dead, NULL);
}

void	ft_free(t_args *args)
{
	int	i;

	i = -1;
	while (args->table->philosophers[++i])
	{
		pthread_mutex_destroy(&args->table->philosophers[i]->fork);
		pthread_mutex_destroy(&args->table->philosophers[i]->mutex_lunchs);
		pthread_mutex_destroy(&args->table->philosophers[i]->eat);
	}
	i = -1;
	while (args->table->philosophers[++i])
		free(args->table->philosophers[i]);
	pthread_mutex_destroy(&args->table->mutex_flag);
	pthread_mutex_destroy(&args->table->mutex_init);
	pthread_mutex_destroy(&args->table->mutex_start);
	pthread_mutex_destroy(&args->table->mutex_printf);
	pthread_mutex_destroy(&args->table->id_philo);
	free(args->table->philosophers);
	free(args->table);
	free(args);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	args->table = malloc(sizeof(t_table));
	if (argc < 5 || argc > 6)
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	ft_check(argv);
	args->table->numphilo = ft_atoi(argv[1]);
	args->table->time_die = ft_atoi(argv[2]);
	args->table->time_eat = ft_atoi(argv[3]);
	args->table->time_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&args->table->mutex_flag, NULL);
	pthread_mutex_init(&args->table->mutex_init, NULL);
	pthread_mutex_init(&args->table->mutex_start, NULL);
	pthread_mutex_init(&args->table->mutex_printf, NULL);
	pthread_mutex_init(&args->table->id_philo, NULL);
	ft_init(args, argv, argc);
	ft_start(args);
	ft_free(args);
}
