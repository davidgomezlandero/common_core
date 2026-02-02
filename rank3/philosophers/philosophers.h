/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:57:21 by davigome          #+#    #+#             */
/*   Updated: 2025/06/09 13:28:30 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_mutex_t	mutex_lunchs;
	pthread_t		id;
	pthread_mutex_t	eat;
	long long		last_eat;
	int				lunchs;
	int				name;
}				t_philo;

typedef struct s_table
{
	t_philo			**philosophers;
	int				flag;
	long long		time_eat;
	long long		time_sleep;
	long long		time_die;
	long long		time_start;
	int				numphilo;
	pthread_t		dead;
	int				init;
	pthread_mutex_t	mutex_flag;
	pthread_mutex_t	mutex_init;
	pthread_mutex_t	mutex_start;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	id_philo;
}				t_table;

typedef struct s_args
{
	t_table			*table;
	int				idphilo;
	int				eats;
}				t_args;

// PHILOSOPHERS.C //
void		ft_printf(t_args *args, int type, int i);

//	FT_CHECK.C //
void		ft_check(char **argv);

// UTILS.C //
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
long long	ft_time(t_args *args);

// PHILOS.C //
void		*ft_philo(void *data);
void		ft_impair(t_args *args, int i);
void		ft_pair(t_args *args, int i);

// FORKS.C //
int			take_forks_pair(t_args *args, int i);
int			take_forks_impair(t_args *args, int i);
void		release_forks_pair(t_args *args, int i);
void		release_forks_impair(t_args *args, int i);

// ACTIONS.C //
int			should_continue(t_args *args);
void		eat(t_args *args, int i);
void		sleep_and_think(t_args *args, int i);

// FT_DEAD.C //
void		ft_dead_2(t_args *args, struct timeval tv, int i);
void		*ft_dead(void *data);

#endif