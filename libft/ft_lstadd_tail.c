/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_tail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:53:17 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/21 12:42:15 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_tail(t_list **alst, t_list *new)
{
	t_list		*head;
	t_list		*tmp;

	tmp = *alst;
	head = tmp;
	if (!tmp)
	{
		*alst = head;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	*alst = head;
}
