/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:51:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/07 16:35:36 by acarlson         ###   ########.fr       */
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
	free(line);
}

void		validate_conn(char *line)		// TODO: make sure this works
{
	char		**split;

	RET_NONE(*line == '#');
	split = ft_strsplit(line, '-');
	if (!split[0] || split[0][0] == 'L')
		panic(1);
	if (!split[1] || split[1][0] == 'L')
		panic(2);
	else if (split[2])
		panic(4);
	free_str_tab(&split);
}

int			validate_room(char *line)		// TODO: make sure this works
{
	if (*line == '#')
		return (0);;
	if (*line == 'L')
		panic(1);
	while (*line && *line != ' ' && *line != '-')
		line++;
	RET_IF(!*line || *line == '-', 1);
	line++;
	while (ISDIGIT(*line))
		line++;
	RET_IF(!*line, 1);
	line++;
	while (ISDIGIT(*line))
		line++;
	RET_IF(*line, 1);
	return (0);
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
		ft_printf("%s\n", line);
		(!strcmp(line, "##start") ? start++ : 0);
		(!strcmp(line, "##end") ? end++ : 0);
		if (start > 1 || end > 1)
			panic(0);
		ft_lstadd_tail(ptr, ft_lstnew(line, ft_strlen(line) + 1));
		free(line);
	}
	DO_IF(start != 1 || end != 1, panic(0));
}

void		read_and_validate(t_lem *info)
{
	read_first_line(info);
	read_rooms_conns(info);
}

void		parse_input(t_lem *info)
{
	read_and_validate(info);
	print_input(info);
}
