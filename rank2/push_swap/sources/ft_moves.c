/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 21:36:17 by davigome          #+#    #+#             */
/*   Updated: 2025/01/03 23:45:02 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_ra(t_stack **stack_a)
{
	t_stack	*temp;
	t_stack	*new_head;

	temp = *stack_a;
	new_head = temp->next;
	while (temp->next)
		temp = temp->next;
	temp->next = *stack_a;
	temp = temp->next;
	temp->next = NULL;
	*stack_a = new_head;
}

void	ft_rb(t_stack **stack_b)
{
	ft_ra(stack_b);
}

void	ft_rra(t_stack **stack_a)
{
	t_stack	*temp;
	t_stack	*penultimate;
	t_stack	*last;

	temp = *stack_a;
	while (temp->next->next)
		temp = temp->next;
	penultimate = temp;
	last = temp->next;
	penultimate->next = NULL;
	temp = *stack_a;
	last->next = temp;
	*stack_a = last;
}

void	ft_rrb(t_stack **stack_b)
{
	ft_rra(stack_b);
}

void	ft_sa(t_stack **stack_a)
{
	t_stack	*temp;
	t_stack	*aux;

	temp = *stack_a;
	aux = temp->next;
	temp->next = aux->next;
	aux->next = temp;
	*stack_a = aux;
}
