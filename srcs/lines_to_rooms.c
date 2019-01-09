/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:59:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/08 16:57:14 by acarlson         ###   ########.fr       */
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

void		add_room(t_lem *info, char *line, char start_end)
{
	t_room		*room;
	t_list		*new;
	char		**split;

	split = ft_strsplit(line, ' ');
	room = make_room(split[0], ft_atoi(split[1]), ft_atoi(split[2]), start_end);
	free_str_tab(&split);
	new = ft_lstnew(room, sizeof(t_room));
	ft_lstadd(&info->rooms, new);
	if (start_end == START)
		info->start = info->rooms->content;
	else if (start_end == END)
		info->end = info->rooms->content;
	free(room);
}

void		add_conn(t_lem *info, char *line)
{
	char		**split;
	t_list		*ptr;
	t_list		*p1;
	t_list		*p2;

	split = ft_strsplit(line, '-');
	RET_IF(!split[0] || !split[1] || split[2], panic(CONN_ERR));
	ptr = info->rooms;
	p1 = NULL;
	p2 = NULL;
	while (ptr)
	{
		if (!ft_strcmp(R(ptr)->name, split[0]))
		{
			if (!p1)
				p1 = ptr;
			else
				panic(CONN_ERR);
		}
		if (!ft_strcmp(R(ptr)->name, split[1]))
		{
			if (!p2)
				p2 = ptr;
			else
				panic(ROOM_ERR);
		}
		ptr = ptr->next;
	}
	if (!p1 || !p2)
		panic(END_ERR);
	free_str_tab(&split);
	ft_lstadd(&R(p1)->conns, ft_lstnew_nocpy(R(p2), sizeof(R(p2))));	// TODO: make sure this actually makes another reference to the same address rather than copy the data
	ft_lstadd(&R(p2)->conns, ft_lstnew_nocpy(R(p1), sizeof(R(p1))));	// TODO: also make sure it works properly
}

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

void		print_rooms(t_lem *info)	// TODO: remove
{
	t_list	*ptr;

	ptr = info->rooms;
	while (ptr)
	{
		ft_printf("Room %s x %2d y %2d start_end %3d\n", R(ptr)->name, R(ptr)->x, R(ptr)->y, R(ptr)->start_end);
		ptr = ptr->next;
	}
}

void		print_conns(t_lem *info)	// TODO: remove
{
	t_list	*ptr;
	t_list	*p2;

	ptr = info->rooms;
	while (ptr)
	{
		p2 = R(info->rooms)->conns;
		while (p2)
		{
			ft_printf("%s-%s\n", R(ptr)->name, R(p2)->name);
			p2 = p2->next;
		}
		ptr = ptr->next;
	}
}

void		add_to_struct(t_lem *info)
{
	t_list		*ptr;
	char		conn;
	char		n;
	char		start_end;

	ptr = info->lines;
	conn = 0;
	start_end = 0;
	while (ptr)
	{
		n = is_start_end(ptr->content);
		(n && n != 1 ? start_end = n : 0);
		DO_IF(n, ptr = ptr->next);
		if (n)
			continue ;
		(!conn && validate_room(ptr->content) ? conn = 1 : 0);
		(conn ? validate_conn(ptr->content) : 0);
		(!conn ? add_room(info, ptr->content, start_end) : 0);
		(conn ? add_conn(info, ptr->content) : 0);
		start_end = 0;
		ptr = ptr->next;
	}
	print_rooms(info);
	print_conns(info);
}
