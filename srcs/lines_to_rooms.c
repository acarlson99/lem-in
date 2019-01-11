/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:59:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/11 01:19:16 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define COMMENT 1

/*
** returns START if start
** returns END if end
** returns 1 if comment
** returns 0 otherwise
*/

/* void		add_room(t_lem *info, char *line, char start_end) */
/* { */
/*	t_room		*room; */
/*	t_list		*new; */
/*	char		**sp; */

/*	sp = ft_strsplit(line, ' '); */
/*	room = make_room(sp[0], ft_atoi(sp[1]), ft_atoi(sp[2]), start_end); */
/*	free_str_tab(&sp); */
/*	new = ft_lstnew(room, sizeof(t_room)); */
/*	ft_lstadd(&info->rooms, new); */
/*	if (start_end == START) */
/*		info->start = info->rooms->content; */
/*	else if (start_end == END) */
/*		info->end = info->rooms->content; */
/*	free(room); */
/* } */

/* void		add_conn(t_lem *info, char *line) */
/* { */
/*	char		**split; */
/*	t_list		*ptr; */
/*	t_list		*p1; */
/*	t_list		*p2; */

/*	split = ft_strsplit(line, '-'); */
/*	RET_IF(!split[0] || !split[1] || split[2], panic(CONN_ERR)); */
/*	!ft_strcmp(split[0], split[1]) ? panic(CONN_ERR) : 0; */
/*	ptr = info->rooms; */
/*	p1 = NULL; */
/*	p2 = NULL; */
/*	while (ptr) */
/*	{ */
/*		if (!ft_strcmp(R(ptr)->name, split[0])) */
/*			!p1 ? p1 = ptr : panic(CONN_ERR); */
/*		if (!ft_strcmp(R(ptr)->name, split[1])) */
/*			!p2 ? p2 = ptr : panic(ROOM_ERR); */
/*		ptr = ptr->next; */
/*	} */
/*	if (!p1 || !p2) */
/*		panic(END_ERR); */
/*	free_str_tab(&split); */
/*	ft_lstadd(&R(p1)->conns, ft_lstnew_nocpy(R(p2), sizeof(R(p2)))); */
/*	ft_lstadd(&R(p2)->conns, ft_lstnew_nocpy(R(p1), sizeof(R(p1)))); */
/* } */

int			is_start_end(char *line)
{
	if (*line == '#')
	{
		if (!strcmp("##start", line))
			return (START);
		else if (!strcmp("##end", line))
			return (END);
		else
			return (COMMENT);
	}
	return (0);
}

/* void		add_to_struct(t_lem *info) */
/* { */
/*	t_list		*ptr; */
/*	char		conn; */
/*	char		n; */
/*	char		start_end; */

/*	ptr = info->lines; */
/*	conn = 0; */
/*	start_end = 0; */
/*	while (ptr) */
/*	{ */
/*		n = is_start_end(ptr->content); */
/*		(n && n != 1 ? start_end = n : 0); */
/*		DO_IF(n, ptr = ptr->next); */
/*		if (n) */
/*			continue ; */
/*		(!conn && validate_room(ptr->content) ? conn = 1 : 0); */
/*		(conn ? validate_conn(ptr->content) : 0); */
/*		(!conn ? add_room(info, ptr->content, start_end) : 0); */
/*		(conn ? add_conn(info, ptr->content) : 0); */
/*		start_end = 0; */
/*		ptr = ptr->next; */
/*	} */
/* } */

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

void		malloc_conns(t_lem *info)	// TODO: this may be mallocing more than we need
{
	unsigned	n;

	n = 0;
	DO_IF((!(info->conns = (int **)ft_memalloc((info->num_rooms + 1)\
									* sizeof(int *)))), panic(MALLOC_ERR));
	while (n < info->num_rooms)
	{
		if (!(info->conns[n] = (int *)ft_memalloc((info->num_rooms + 1)\
											* sizeof(int))))
			panic(MALLOC_ERR);
		n++;
	}
	info->conns[n] = NULL;
}

void		create_conns(t_lem *info, t_list *ptr)
{
	char		**split;
	unsigned	n;
	unsigned	x;
	unsigned	y;

	malloc_conns(info);
	if (!ptr)
		panic(CONN_ERR);
	while (ptr)
	{
		n = 0;
		x = 0;
		y = 0;
		split = ft_strsplit((char *)ptr->content, '-');
		while (n < info->num_rooms)
		{
			if (!ft_strcmp(info->rooms[n]->name, split[0]))
			{
				if (y)
					panic(CONN_ERR);
				y = n;
			}
			if (!ft_strcmp(info->rooms[n]->name, split[1]))
			{
				if (x)
					panic(CONN_ERR);
				x = n;
			}
			n++;
		}
		info->conns[x][y] = 1;
		info->conns[y][x] = 1;
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
