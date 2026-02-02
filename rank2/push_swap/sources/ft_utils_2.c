/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:37:20 by davigome          #+#    #+#             */
/*   Updated: 2025/01/03 23:38:39 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_addfront_lst(t_stack **stack, t_stack *new)
{
	new->next = *stack;
	*stack = new;
}

void	ft_calculate_pos(t_stack **stack)
{
	t_stack	*temp;
	int		i;

	i = 0;
	temp = *stack;
	while (temp)
	{
		temp->pos = i;
		i++;
		temp = temp->next;
	}
}

void	ft_initialize_positions(t_stack **stack_a, t_stack **stack_b)
{
	ft_calculate_pos(stack_a);
	ft_calculate_pos(stack_b);
}

int	ft_find_min_position(t_stack **stack_a)
{
	t_stack	*temp_a;
	int		min_index;
	int		pos_min;

	temp_a = *stack_a;
	min_index = temp_a->index;
	pos_min = temp_a->pos;
	while (temp_a)
	{
		if (temp_a->index < min_index)
		{
			pos_min = temp_a->pos;
			min_index = temp_a->index;
		}
		temp_a = temp_a->next;
	}
	return (pos_min);
}

void	ft_update_target(t_stack **stack_a, t_stack *temp_b, int pos_min)
{
	t_stack	*temp_a;
	int		temp_max;
	int		pos_max;

	temp_a = *stack_a;
	temp_max = -1;
	while (temp_a)
	{
		if (temp_max == -1 && temp_a->index > temp_b->index)
		{
			temp_max = temp_a->index;
			pos_max = temp_a->pos;
		}
		if (temp_a->index > temp_b->index && temp_a->index < temp_max)
		{
			temp_max = temp_a->index;
			pos_max = temp_a->pos;
		}
		temp_a = temp_a->next;
	}
	if (temp_max == -1)
		temp_b->target_pos = pos_min;
	else
		temp_b->target_pos = pos_max;
}
