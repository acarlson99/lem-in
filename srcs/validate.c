/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:46:20 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/08 20:39:03 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** TODO: make sure validate_room and validate_conn work
*/

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

unsigned	ft_lstlen(t_list *l)
{
	unsigned	i;
	t_list		*tmp;

	i = 0;
	tmp = l;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/*
** TODO: check room connections and coordinates and info->num_rooms is borked
*/

void		check_struct(t_lem *info)
{
	if (!info)
		panic(PARS_ERR);
	if (!info->num_rooms || !info->num_ants)
		panic(PARS_ERR);
	if (!info->lines || !info->rooms || !info->start || !info->end)
		panic(PARS_ERR);
}
