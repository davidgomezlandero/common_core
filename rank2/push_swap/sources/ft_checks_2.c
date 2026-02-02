/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:27:34 by davigome          #+#    #+#             */
/*   Updated: 2025/01/03 23:30:00 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_atoi_list_and_max_min(t_nums *nums)
{
	int	i;

	i = -1;
	nums->list = malloc(sizeof(int) * nums->num_of_values);
	while (nums->values[++i])
	{
		if (ft_atoi_long(nums->values[i]) > 2147483647
			|| ft_atoi_long(nums->values[i]) < -2147483648)
		{
			write(2, "Error\n", 6);
			ft_free_nums(nums);
			exit(2);
		}
		else
			nums->list[i] = ft_atoi(nums->values[i]);
	}
	i = -1;
}

void	ft_check_reps(t_nums *nums)
{
	int	reps;
	int	i;
	int	j;

	reps = 0;
	i = -1;
	while (++i < nums->num_of_values)
	{
		j = -1;
		reps = 0;
		while (++j < nums->num_of_values)
		{
			if (nums->list[i] == nums->list[j])
				reps++;
		}
		if (reps > 1)
		{
			write(2, "Error\n", 6);
			ft_free_nums(nums);
			exit(2);
		}
	}
}

void	ft_check_sort(t_nums *nums)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (++i < nums->num_of_values - 1)
	{
		if (nums->list[i] > nums->list[i + 1])
			flag++;
	}
	if (flag == 0)
	{
		ft_free_nums(nums);
		exit(0);
	}
}

void	ft_nothing_after_sign(t_nums *nums)
{
	write(2, "Error\n", 6);
	ft_free_nums(nums);
	exit(2);
}

void	ft_more_sign(t_nums *nums)
{
	write(2, "Error\n", 6);
	ft_free_nums(nums);
	exit(2);
}
