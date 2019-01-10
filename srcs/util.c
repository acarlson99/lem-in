/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 16:24:32 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/10 14:57:56 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_str_tab(char ***tab)
{
	int i;

	i = 0;
	while ((*tab)[i] != NULL)
	{
		free((*tab)[i]);
		i++;
	}
	free((*tab));
}

void		print_input(t_lem *info)
{
	t_list		*ptr;

	ptr = info->lines;
	ft_printf("%d\n", info->num_ants);
	while (ptr)
	{
		ft_printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
}

void		reset_visited(t_room *room)
{
	t_list		*ptr;

	if (!room || room->visited)
		return ;
	ptr = room->conns;
	room->visited = 1;
	while (ptr)
	{
		reset_visited(R(ptr));
		ptr = ptr->next;
	}
	room->visited = 0;
}

unsigned	ft_lstlen(t_list *l)
{
	unsigned	i;
	t_list		*tmp;

	i = 0;
	tmp = l;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_list		*ft_lstnew_nocpy(void *content, size_t content_size)
{
	t_list			*new;

	NULL_CHECK(!(new = (t_list *)malloc(sizeof(t_list))));
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = content;
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
