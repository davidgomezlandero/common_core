/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:34:24 by davigome          #+#    #+#             */
/*   Updated: 2025/01/04 12:50:27 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_select_algorithm(t_nums *nums)
{
	if (nums->num_of_values == 2)
		ft_two_values(nums);
	if (nums->num_of_values == 3)
		ft_three_values(nums);
	else
		ft_more_values(nums);
}

void	ft_two_values(t_nums *nums)
{
	ft_printf("sa\n");
	ft_free_nums(nums);
	exit(0);
}

void	ft_three_values(t_nums *nums)
{
	t_stack	**stack_a;

	stack_a = malloc(sizeof(t_stack *));
	*stack_a = NULL;
	ft_values_to_stack_a(stack_a, nums);
	ft_index_to_stack_a(stack_a, nums);
	ft_sort_three(stack_a);
	ft_free_nums(nums);
	ft_free_stack(stack_a);
	exit(0);
}

void	ft_more_values(t_nums *nums)
{
	t_stack	**stack_a;
	t_stack	**stack_b;

	stack_a = malloc(sizeof(t_stack *));
	*stack_a = NULL;
	stack_b = malloc(sizeof(t_stack *));
	*stack_b = NULL;
	ft_values_to_stack_a(stack_a, nums);
	ft_index_to_stack_a(stack_a, nums);
	ft_tostackb_vague(stack_a, stack_b, nums);
	ft_target_pos(stack_a, stack_b);
	ft_calculate_cost(stack_a, stack_b);
	ft_move_cheap_to_stack_a(stack_a, stack_b);
	ft_rotate_order(stack_a, stack_b);
	ft_free_stack(stack_a);
	ft_free_stack(stack_b);
	free(stack_a);
	free(stack_b);
}
