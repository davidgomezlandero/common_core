/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:20:47 by davigome          #+#    #+#             */
/*   Updated: 2025/01/03 23:46:50 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	space(const char *str, int cont)
{
	if ((str[cont] >= 9 && str[cont] <= 13) || str[cont] == 32)
		return (1);
	return (0);
}

long long	ft_atoi_long(const char *str)
{
	size_t		cont;
	long long	number;
	int			neg;

	cont = 0;
	number = 0;
	neg = 1;
	while (space(str, cont))
		cont++;
	if (str[cont] == '-' || str[cont] == '+')
	{
		if (str[cont] == '-')
			neg = -1;
		cont++;
	}
	while (ft_isdigit(str[cont]))
	{
		number = number * 10 + (str[cont] - 48);
		cont++;
	}
	number = neg * number;
	return (number);
}

t_stack	*ft_newlst_value(t_nums *nums, int i)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
	{
		ft_printf("Error\n");
		ft_free_nums(nums);
		exit(1);
	}
	new->value = nums->list[i];
	new->next = NULL;
	return (new);
}

void	ft_addback_lst(t_stack **stack, t_stack *new)
{
	t_stack	*now;

	if (*stack == NULL)
	{
		*stack = new;
	}
	else
	{
		now = *stack;
		while (now->next)
			now = now->next;
		now->next = new;
	}
}

void	ft_sort(t_nums *nums)
{
	int	i;
	int	j;
	int	aux;

	i = -1;
	while (++i < nums->num_of_values)
	{
		j = -1;
		while (++j < nums->num_of_values)
		{
			if (nums->list[i] < nums->list[j])
			{
				aux = nums->list[i];
				nums->list[i] = nums->list[j];
				nums->list[j] = aux;
			}
		}
	}
}
