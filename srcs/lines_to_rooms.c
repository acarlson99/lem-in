/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:59:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/07 21:14:05 by acarlson         ###   ########.fr       */
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

void		add_room(t_lem *info, char *line, char start_end)	// TODO: implement
{
	(void)info;
	(void)line;
	ft_printf("room: %s%s\n", line, (start_end == START ? " is the source" : (start_end == END ? " is the sink" : "")));
}

void		add_conn(t_lem *info, char *line)	// TODO: implement
{
	(void)info;
	(void)line;
	ft_printf("conn: %s\n", line);
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

/* void		add_to_struct(t_lem *info) */
/* { */
/* 	t_list		*ptr; */
/* 	char		room_or_conn; */
/* 	char		n; */
/* 	char		start_end; */

/* 	ptr = info->lines; */
/* 	room_or_conn = 0; */
/* 	while (ptr) */
/* 	{ */
/* 		n = is_start_end(ptr->content); */
/* 		start_end = (n == START || n == END ? n : 0); */
/* 		if (n == 1) */
/* 			continue ; */
/* 		if (!room_or_conn && validate_room(ptr->content)) */
/* 			room_or_conn = 1; */
/* 		if (room_or_conn) */
/* 			validate_conn(ptr->content); */
/* 		(room_or_conn ? add_conn(info, ptr->content)	\ */
/* 			: add_room(info, ptr->content, start_end)); */
/* 		ptr = ptr->next; */
/* 	} */
/* } */

void		add_to_struct(t_lem *info)
{
	t_list		*ptr;
	char		conn;
	char		n;
	char		start_end;

	ptr = info->lines;
	conn = 0;
	while (ptr)
	{
		n = is_start_end(ptr->content);
		if (n && n != 1)
			start_end = n;
		else if (n)
			continue ;
		if (!conn && validate_room(ptr->content))
			conn = 1;
		if (conn)
			validate_conn(ptr->content);
		if (!conn)
		{
			add_room(info, ptr->content, n);
			start_end = 0;
		}
		else if (conn)
		{
			add_conn(info, ptr->content);
			start_end = 0;
		}
		ptr = ptr->next;
	}
}
