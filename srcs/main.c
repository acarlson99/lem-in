/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 17:48:41 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/01 18:13:42 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_room(void *ptr, size_t n)
{
	t_room	*room;

	RET_NONE(!ptr);
	(void)n;
	room = (t_room *)ptr;
	room->full = 0;
	room->visited = 0;
	room->start_end = 0;
	room->coord_x = 0;
	room->coord_y = 0;
	ft_memdel((void **)&(room->name));
}

void	free_struct(t_lem **info)
{
	ft_lstdel(&((*info)->rooms), del_room);
	ft_memdel((void *)&((*info)->start));
	ft_memdel((void *)&((*info)->end));
	ft_memdel((void **)info);
}

t_lem	*init_lem()
{
	t_lem	*new;

	new = (t_lem *)malloc(sizeof(t_lem));
	new->num_rooms = 0;
	new->rooms = NULL;
	new->start = NULL;
	new->end = NULL;
	return (new);
}

int		main(void)
{
	t_lem	*info;

	info = init_lem();
	ft_printf("%s\n", info->rooms);
	free_struct(&info);
}
