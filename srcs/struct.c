/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:21:52 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/10 14:57:57 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_room(t_room **room)
{
	ft_memdel((void **)&((*room)->name));
	(*room)->x = 0;
	(*room)->y = 0;
	ft_memdel((void **)room);
}

t_room		*make_room(char *name, int x, int y, char start_end)
{
	t_room		*new;

	new = (t_room *)malloc(sizeof(t_room));
	new->full = 0;
	new->visited = 0;
	new->start_end = start_end;
	new->x = x;
	new->y = y;
	new->name = ft_strdup(name);
	new->conns = NULL;
	return (new);
}

void		init_lem(t_lem **info)
{
	if (!(*info = (t_lem *)malloc(sizeof(t_lem))))
		panic(MALLOC_ERR);
	(*info)->num_rooms = 0;
	(*info)->num_ants = 0;
	(*info)->lines = NULL;
	(*info)->rooms = NULL;
	(*info)->start = NULL;
	(*info)->end = NULL;
}
