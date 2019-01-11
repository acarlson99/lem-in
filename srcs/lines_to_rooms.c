/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:59:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/11 03:10:04 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define COMMENT 1

void		add_room(t_lem *info, char *str, size_t rm_index, char start_end)
{
	char		**split;

	split = ft_strsplit(str, ' ');
	DO_IF(!split[0] || !split[1] || !split[2] || split[3], panic(ROOM_ERR));
	if (start_end == END)
	{
		DO_IF(info->rooms[info->num_rooms - 1], panic(END_ERR));
		info->rooms[info->num_rooms - 1] = make_room(split[0],\
							ft_atoi(split[1]), ft_atoi(split[2]), start_end);
		info->end = info->rooms[info->num_rooms - 1];
	}
	else if (start_end == START)
	{
		DO_IF(info->rooms[0], panic(START_ERR));
		info->rooms[0] = make_room(split[0], ft_atoi(split[1]),\
									ft_atoi(split[2]), start_end);
		info->start = info->rooms[0];
	}
	else
	{
		DO_IF(info->rooms[rm_index], panic(ROOM_ERR));
		info->rooms[rm_index] = make_room(split[0], ft_atoi(split[1]),\
										ft_atoi(split[2]), start_end);
	}
	free_str_tab(&split);
}

void		malloc_conns(t_lem *info)
{
	size_t	n;

	n = 0;
	DO_IF((!(info->conns = (int **)ft_memalloc((info->num_rooms + 1)\
									* sizeof(int *)))), panic(MALLOC_ERR));
	while (n <= info->num_rooms)
	{
		if (!(info->conns[n] = (int *)ft_memalloc((info->num_rooms)\
											* sizeof(int))))
			panic(MALLOC_ERR);
		n++;
	}
}

void		add_conn(t_lem *info, char **split)
{
	size_t	n;
	size_t	x;
	size_t	y;

	n = 0;
	x = 0;
	y = 0;
	while (n < info->num_rooms)
	{
		if (!ft_strcmp(info->rooms[n]->name, split[0]))
		{
			DO_IF(y, panic(CONN_ERR));
			y = n;
		}
		if (!ft_strcmp(info->rooms[n]->name, split[1]))
		{
			DO_IF(x, panic(CONN_ERR));
			x = n;
		}
		n++;
	}
	info->conns[x][y] = 1;
	info->conns[y][x] = 1;
}

void		create_conns(t_lem *info, t_list *ptr)
{
	char		**split;

	malloc_conns(info);
	if (!ptr)
		panic(CONN_ERR);
	while (ptr)
	{
		split = ft_strsplit(ptr->content, '-');
		add_conn(info, split);
		free_str_tab(&split);
		ptr = ptr->next;
	}
}

void		create_rooms(t_lem *info)
{
	t_list		*ptr;
	char		n;
	char		start_end;
	size_t		rm_index;

	DO_IF(!(info->rooms = (t_room **)ft_memalloc((info->num_rooms + 1)	\
									* sizeof(t_room *))), panic(MALLOC_ERR));
	start_end = 0;
	ptr = info->lines;
	rm_index = 1;
	while (ptr)
	{
		n = is_start_end(ptr->content);
		(n && n != 1 ? start_end = n : 0);
		DO_IF(n, ptr = ptr->next);
		if (n)
			continue ;
		if (validate_room(ptr->content))
			if ((info->rooms[info->num_rooms] = NULL) || 1)
				return (create_conns(info, ptr));
		add_room(info, (char *)ptr->content, rm_index, start_end);
		(!start_end ? rm_index++ : 0);
		start_end = 0;
		ptr = ptr->next;
	}
}
