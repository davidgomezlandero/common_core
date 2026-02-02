/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:03:48 by davigome          #+#    #+#             */
/*   Updated: 2024/06/27 19:08:46 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*now;

	while (*lst)
	{
		now = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = now;
	}
	free(*lst);
	*lst = NULL;
}
