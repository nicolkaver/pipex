/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:02:43 by nboratko          #+#    #+#             */
/*   Updated: 2021/11/30 17:02:04 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!new || !alst)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
	}
}
