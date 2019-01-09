/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:59:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/09 13:36:03 by acarlson         ###   ########.fr       */
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
	char		**sp;

	sp = ft_strsplit(line, ' ');
	room = make_room(sp[0], ft_atoi(sp[1]), ft_atoi(sp[2]), start_end);
	free_str_tab(&sp);
	new = ft_lstnew(room, sizeof(t_room));
	ft_lstadd(&info->rooms, new);
	if (start_end == START)
		info->start = info->rooms->content;
	else if (start_end == END)
		info->end = info->rooms->content;
	info->num_rooms++;
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
	!ft_strcmp(split[0], split[1]) ? panic(CONN_ERR) : 0;
	ptr = info->rooms;
	p1 = NULL;
	p2 = NULL;
	while (ptr)
	{
		if (!ft_strcmp(R(ptr)->name, split[0]))
			!p1 ? p1 = ptr : panic(CONN_ERR);
		if (!ft_strcmp(R(ptr)->name, split[1]))
			!p2 ? p2 = ptr : panic(ROOM_ERR);
		ptr = ptr->next;
	}
	if (!p1 || !p2)
		panic(END_ERR);
	free_str_tab(&split);
	ft_lstadd(&R(p1)->conns, ft_lstnew_nocpy(R(p2), sizeof(R(p2))));
	ft_lstadd(&R(p2)->conns, ft_lstnew_nocpy(R(p1), sizeof(R(p1))));
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
