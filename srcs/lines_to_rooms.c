/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:59:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/07 19:51:59 by acarlson         ###   ########.fr       */
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

void		add_room(t_lem *info, char *line)	// TODO: implement
{
	(void)info;
	(void)line;
}

void		add_conn(t_lem *info, char *line)	// TODO: implement
{
	(void)info;
	(void)line;
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
	size_t		i;
	int			room_or_conn;
	char		n;
	char		start_end;

	ptr = info->lines;
	i = 0;
	room_or_conn = 0;
	while (ptr)
	{
		n = is_start_end(ptr->content);
		start_end = (n == START || n == END ? n : 0);
		if (n == 1)
			continue ;
		if (!room_or_conn && !is_room(ptr->content))
			room_or_conn = 1;
		if (room_or_conn && !is_conn(ptr->content))
			panic(CONN_ERR);
		(room_or_conn ? add_conn(info, ptr->content) : add_room(info, ptr->content));
		ptr = ptr->next;
	}
}
