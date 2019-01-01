/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 14:37:05 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/12 00:37:47 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*head;
	t_list	*ptr;

	NULL_CHECK(!(lst));
	ptr = f(lst);
	NULL_CHECK(!(new = ft_lstnew(ptr->content, ptr->content_size)));
	head = new;
	lst = lst->next;
	while (lst)
	{
		ptr = f(lst);
		NULL_CHECK(!(new->next = ft_lstnew(ptr->content, ptr->content_size)));
		new = new->next;
		lst = lst->next;
	}
	return (head);
}
