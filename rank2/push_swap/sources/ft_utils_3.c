/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:39:31 by davigome          #+#    #+#             */
/*   Updated: 2025/01/03 23:47:02 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_target_pos(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*temp_b;
	int		pos_min;

	ft_initialize_positions(stack_a, stack_b);
	pos_min = ft_find_min_position(stack_a);
	temp_b = *stack_b;
	while (temp_b)
	{
		ft_update_target(stack_a, temp_b, pos_min);
		temp_b = temp_b->next;
	}
}

void	ft_calculate_cost(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*temp_b;

	temp_b = *stack_b;
	while (temp_b)
	{
		if (temp_b->pos <= ft_size_lst(stack_b) / 2)
			temp_b->cost_b = temp_b->pos;
		else
			temp_b->cost_b = temp_b->pos - ft_size_lst(stack_b);
		if (temp_b->target_pos <= ft_size_lst(stack_a) / 2)
			temp_b->cost_a = temp_b->target_pos;
		else
			temp_b->cost_a = temp_b->target_pos - ft_size_lst(stack_a);
		temp_b = temp_b->next;
	}
}

int	ft_the_cheap(t_stack **stack_b)
{
	t_stack	*temp;
	int		cheap;
	int		prize;

	temp = *stack_b;
	prize = abs(temp->cost_a) + abs(temp->cost_b);
	cheap = temp->value;
	while (temp)
	{
		if ((abs(temp->cost_a) + abs(temp->cost_b)) < prize)
		{
			cheap = temp->value;
			prize = abs(temp->cost_a) + abs(temp->cost_b);
		}
		temp = temp->next;
	}
	return (cheap);
}

int	ft_size_lst(t_stack **stack)
{
	t_stack	*temp;
	int		i;

	i = 0;
	temp = *stack;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
