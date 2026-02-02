/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:10:03 by davigome          #+#    #+#             */
/*   Updated: 2025/01/04 12:45:42 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_checks(char **argv, t_nums *nums)
{
	ft_alloc_mem_values(argv, nums);
	ft_cpy_values(argv, nums);
	ft_check_sign_digit(nums);
	ft_atoi_list_and_max_min(nums);
	ft_check_reps(nums);
	ft_check_sort(nums);
}

void	ft_alloc_mem_values(char **argv, t_nums *nums)
{
	int		i;
	int		j;
	char	**aux_val;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		aux_val = ft_split(argv[i], ' ');
		while (aux_val[++j])
			nums->num_of_values++;
		ft_free_matrix(aux_val);
	}
	nums->values = malloc(sizeof(char *) * ((nums->num_of_values) + 1));
	if (!nums->values)
	{
		ft_free_nums(nums);
		write(2, "Error\n", 6);
		exit(2);
	}
	i = -1;
	while (++i < nums->num_of_values)
		nums->values[i] = NULL;
	nums->values[i] = NULL;
}

void	ft_cpy_values(char **argv, t_nums *nums)
{
	int		i;
	int		j;
	char	**aux_val;
	int		k;

	i = 0;
	j = 1;
	k = 0;
	while (i < nums->num_of_values)
	{
		aux_val = ft_split(argv[j], ' ');
		k = 0;
		while (aux_val[k])
		{
			nums->values[i] = malloc(sizeof(char) * (ft_strlen(aux_val[k])
						+ 1));
			ft_strlcpy(nums->values[i], aux_val[k], ft_strlen(aux_val[k]) + 1);
			i++;
			k++;
		}
		j++;
		ft_free_matrix(aux_val);
	}
}

void	ft_check_sign_digit(t_nums *nums)
{
	int	i;
	int	j;

	i = -1;
	while (nums->values[++i])
	{
		j = 0;
		while (nums->values[i][j] == ' ')
			j++;
		if (nums->values[i][j] == '+' || nums->values[i][j] == '-')
			j++;
		if (nums->values[i][j] == '+' || nums->values[i][j] == '-')
			ft_more_sign(nums);
		if (nums->values[i][j] == '\0')
			ft_nothing_after_sign(nums);
		while (nums->values[i][j] != '\0')
		{
			if (!ft_isdigit(nums->values[i][j]))
				ft_not_digit(nums);
			j++;
		}
	}
}

void	ft_not_digit(t_nums *nums)
{
	write(2, "Error\n", 6);
	ft_free_nums(nums);
	exit(2);
}
