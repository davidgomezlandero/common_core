/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:41:05 by davigome          #+#    #+#             */
/*   Updated: 2025/01/03 23:42:33 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_move_cheap_to_stack_a(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*temp;
	int		cheap;

	temp = *stack_b;
	while (temp)
	{
		cheap = ft_the_cheap(stack_b);
		while (temp)
		{
			if (temp->value == cheap)
				break ;
			temp = temp->next;
		}
		ft_handle_costs(stack_a, stack_b, temp);
		ft_moves(stack_a, stack_b, 2);
		ft_target_pos(stack_a, stack_b);
		ft_calculate_cost(stack_a, stack_b);
		temp = *stack_b;
	}
}

void	ft_handle_costs(t_stack **stack_a, t_stack **stack_b, t_stack *temp)
{
	while (temp->cost_a > 0 && temp->cost_b > 0)
	{
		ft_moves(stack_a, stack_b, 5);
		temp->cost_a--;
		temp->cost_b--;
	}
	while (temp->cost_a < 0 && temp->cost_b < 0)
	{
		ft_moves(stack_a, stack_b, 8);
		temp->cost_a++;
		temp->cost_b++;
	}
	ft_handle_individual_costs(stack_a, stack_b, temp);
}

void	ft_handle_individual_costs(t_stack **stack_a, t_stack **stack_b,
		t_stack *temp)
{
	while (temp->cost_a > 0)
	{
		ft_moves(stack_a, stack_b, 3);
		temp->cost_a--;
	}
	while (temp->cost_a < 0)
	{
		ft_moves(stack_a, stack_b, 6);
		temp->cost_a++;
	}
	while (temp->cost_b > 0)
	{
		ft_moves(stack_a, stack_b, 4);
		temp->cost_b--;
	}
	while (temp->cost_b < 0)
	{
		ft_moves(stack_a, stack_b, 7);
		++(temp->cost_b);
	}
}

void	ft_values_to_stack_a(t_stack **stack_a, t_nums *nums)
{
	t_stack	*temp;
	int		i;

	i = -1;
	while (++i < nums->num_of_values)
	{
		temp = ft_newlst_value(nums, i);
		ft_addback_lst(stack_a, temp);
	}
}

void	ft_index_to_stack_a(t_stack **stack_a, t_nums *nums)
{
	int		i;
	t_stack	*temp;

	ft_sort(nums);
	temp = *stack_a;
	while (temp->next)
	{
		i = -1;
		while (++i < nums->num_of_values)
		{
			if (temp->value == nums->list[i])
			{
				temp->index = i + 1;
				temp = temp->next;
				break ;
			}
		}
	}
	i = -1;
	while (++i < nums->num_of_values)
	{
		if (temp->value == nums->list[i])
			temp->index = i + 1;
	}
}
