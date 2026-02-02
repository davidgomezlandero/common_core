/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:44:22 by davigome          #+#    #+#             */
/*   Updated: 2025/01/03 23:45:06 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_pb(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*aux;

	aux = *stack_a;
	*stack_a = aux->next;
	ft_addfront_lst(stack_b, aux);
}

void	ft_pa(t_stack **stack_a, t_stack **stack_b)
{
	ft_pb(stack_b, stack_a);
}

void	ft_moves(t_stack **stack_a, t_stack **stack_b, int move)
{
	if (move == 1)
	{
		ft_printf("pb\n");
		ft_pb(stack_a, stack_b);
	}
	if (move == 2)
	{
		ft_printf("pa\n");
		ft_pa(stack_a, stack_b);
	}
	if (move == 3)
	{
		ft_printf("ra\n");
		ft_ra(stack_a);
	}
	if (move == 4)
	{
		ft_printf("rb\n");
		ft_rb(stack_b);
	}
	ft_moves_2(stack_a, stack_b, move);
}

void	ft_moves_2(t_stack **stack_a, t_stack **stack_b, int move)
{
	if (move == 5)
	{
		ft_printf("rr\n");
		ft_rb(stack_b);
		ft_ra(stack_a);
	}
	if (move == 6)
	{
		ft_printf("rra\n");
		ft_rra(stack_a);
	}
	if (move == 7)
	{
		ft_printf("rrb\n");
		ft_rrb(stack_b);
	}
	if (move == 8)
	{
		ft_printf("rrr\n");
		ft_rrb(stack_b);
		ft_rra(stack_a);
	}
}
