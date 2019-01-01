/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:56:30 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/04 17:57:41 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrev(t_list **alst)
{
	t_list *head;
	t_list *curr;
	t_list *next;

	curr = NULL;
	head = *alst;
	while (head)
	{
		next = head->next;
		head->next = curr;
		curr = head;
		head = next;
	}
	*alst = curr;
}
