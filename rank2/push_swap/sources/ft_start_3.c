/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:43:31 by davigome          #+#    #+#             */
/*   Updated: 2025/01/03 23:43:54 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_sort_three(t_stack **stack)
{
	t_stack	*temp;

	temp = *stack;
	if (temp->index > temp->next->index
		&& temp->index > temp->next->next->index)
	{
		ft_ra(stack);
		ft_printf("ra\n");
	}
	else if (temp->next->index > temp->index
		&& temp->next->index > temp->next->next->index)
	{
		ft_rra(stack);
		ft_printf("rra\n");
	}
	temp = *stack;
	if (temp->index > temp->next->index)
	{
		ft_sa(stack);
		ft_printf("sa\n");
	}
}

void	ft_tostackb_vague(t_stack **stack_a, t_stack **stack_b, t_nums *nums)
{
	t_stack	*temp;
	int		i;
	int		j;

	i = 0;
	temp = *stack_a;
	while (temp)
	{
		if (temp->index < nums->num_of_values / 2)
		{
			j = -1;
			while (++j < i)
				ft_moves(stack_a, stack_b, 3);
			ft_moves(stack_a, stack_b, 1);
			temp = *stack_a;
			i = 0;
		}
		else
		{
			temp = temp->next;
			i++;
		}
	}
	ft_tostackb_vague_2(stack_a, stack_b);
}

void	ft_tostackb_vague_2(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*temp;

	temp = *stack_a;
	while (temp->next->next->next)
	{
		ft_moves(stack_a, stack_b, 1);
		temp = *stack_a;
	}
	ft_sort_three(stack_a);
}

void	ft_rotate_order(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*temp;
	int		pos;
	int		rot;

	temp = *stack_a;
	rot = -1;
	ft_calculate_pos(stack_a);
	while (temp)
	{
		if (temp->index == 1)
			pos = temp->pos;
		temp = temp->next;
	}
	if (pos <= ft_size_lst(stack_a) / 2)
	{
		while (++rot < pos)
			ft_moves(stack_a, stack_b, 3);
	}
	else
	{
		rot = 1;
		while (--rot > pos - ft_size_lst(stack_a))
			ft_moves(stack_a, stack_b, 6);
	}
}
