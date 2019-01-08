/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:59:54 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/07 22:11:30 by acarlson         ###   ########.fr       */
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

void		add_room(t_lem *info, char *line, char start_end)	// TODO: impl
{
	(void)info;
	(void)line;
	ft_printf("room: %s%s\n", line, (start_end == START ? " is the source" \
							: (start_end == END ? " is the sink" : "")));
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
}
