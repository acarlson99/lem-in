/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:46:20 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/10 23:27:35 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			validate_room(char *line)
{
	if (*line == '#')
		return (0);
	if (*line == 'L')
		panic(ROOM_ERR);
	while (*line && *line != ' ' && *line != '-')
		line++;
	RET_IF(!*line || *line == '-', 1);
	line++;
	while (ISDIGIT(*line))
		line++;
	RET_IF(!*line || *line != ' ', 1);
	line++;
	while (ISDIGIT(*line))
		line++;
	RET_IF(*line, 1);
	return (0);
}

void		validate_conn(char *line)
{
	char		**split;
	char		*ptr;

	RET_NONE(*line == '#');
	split = ft_strsplit(line, '-');
	if (!split[0] || split[0][0] == 'L')
		panic(CONN_ERR);
	ptr = split[0];
	while (*ptr && !ISWHITE2(*ptr))
		ptr++;
	if (ISWHITE2(*ptr))
		panic(CONN_ERR);
	if (!split[1] || split[1][0] == 'L')
		panic(CONN_ERR);
	ptr = split[1];
	while (*ptr && !ISWHITE2(*ptr))
		ptr++;
	if (ISWHITE2(*ptr))
		panic(CONN_ERR);
	else if (split[2])
		panic(CONN_ERR);
	free_str_tab(&split);
}

int			path_to_end(t_room *start)
{
	t_list	*ptr;

	if (!start || start->visited)
		return (0);
	start->visited = 1;
	if (start->start_end == END)
		return (1);
	ptr = start->conns;
	while (ptr)
	{
		if (path_to_end(R(ptr)))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

/* void		check_struct(t_lem *info)	// TODO: this */
/* { */
/* 	t_list	*p1; */
/* 	t_list	*p2; */

/* 	if (!info) */
/* 		panic(PARS_ERR); */
/* 	if (!info->num_rooms || !info->num_ants) */
/* 		panic(PARS_ERR); */
/* 	if (!info->lines || !info->rooms || !info->start || !info->end) */
/* 		panic(PARS_ERR); */
/* 	p1 = info->rooms; */
/* 	while (p1) */
/* 	{ */
/* 		p2 = p1->next; */
/* 		while (p2) */
/* 		{ */
/* 			if (!ft_strcmp(R(p1)->name, R(p2)->name)) */
/* 				panic(ROOM_ERR); */
/* 			p2 = p2->next; */
/* 		} */
/* 		p1 = p1->next; */
/* 	} */
/* 	if (!path_to_end(info->start)) */
/* 		panic(NOPATH_ERR); */
/* } */
