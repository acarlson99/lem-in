/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:51:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/13 16:14:02 by acarlson         ###   ########.fr       */
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

void		read_lines(t_lem *info)
{
	int			room_or_conn;
	char		start;
	char		end;
	char		*line;

	start = 0;
	end = 0;
	room_or_conn = 0;
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		if (!room_or_conn && validate_room(line))
			room_or_conn = 1;
		if (room_or_conn)
			validate_conn(line);
		else if (*line != '#')
			info->num_rooms++;
		(!strcmp(line, "##start") ? start++ : 0);
		(!strcmp(line, "##end") ? end++ : 0);
		DO_IF(start > 1 || end > 1, panic(ROOM_ERR));
		add_line(&info->lines, line);
	}
	DO_IF(start != 1 || end != 1, panic(ROOM_ERR));
}

void		parse_input(t_lem *info)
{
	read_first_line(info);
	read_lines(info);
	create_rooms(info);
//	print_rooms(info->rooms, info->num_rooms);
//	print_conns(info->conns, info->num_rooms);
	if (!is_path(info->conns, NULL, info->num_rooms))
		panic(NOPATH_ERR);
}
