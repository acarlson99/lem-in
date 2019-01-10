/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:51:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/10 14:40:41 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		read_first_line(t_lem *info)
{
	char		*line;
	char		*ptr;

	RET_IF(get_next_line(STDIN_FILENO, &line) < 1, panic(PARS_ERR));
	ptr = line;
	while (ISDIGIT(*ptr))
		ptr++;
	if (*ptr)
		panic(READ_ERR);
	info->num_ants = ft_atoi(line);
	if (info->num_ants < 1)
		panic(ANTNUM_ERR);
	free(line);
}

void		read_rooms_conns(t_lem *info)
{
	t_list		**ptr;
	int			room_or_conn;
	char		start;
	char		end;
	char		*line;

	ptr = &(info->lines);
	start = 0;
	end = 0;
	room_or_conn = 0;
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		if (!room_or_conn && validate_room(line))
			room_or_conn = 1;
		if (room_or_conn)
			validate_conn(line);
		(!strcmp(line, "##start") ? start++ : 0);
		(!strcmp(line, "##end") ? end++ : 0);
		if (start > 1 || end > 1)
			panic(ROOM_ERR);
		ft_lstadd_tail(ptr, ft_lstnew(line, ft_strlen(line) + 1));
		free(line);
	}
	DO_IF(start != 1 || end != 1, panic(ROOM_ERR));
}

void		parse_input(t_lem *info)
{
	read_first_line(info);
	read_rooms_conns(info);
	add_to_struct(info);
	check_struct(info);
	reset_visited(info->start);
}
