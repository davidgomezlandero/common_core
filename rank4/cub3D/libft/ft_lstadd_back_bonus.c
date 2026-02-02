/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:54:26 by davigome          #+#    #+#             */
/*   Updated: 2025/01/02 01:17:52 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*now;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		now = *lst;
		while (now-> next)
			now = now-> next;
		now->next = new;
	}
}
