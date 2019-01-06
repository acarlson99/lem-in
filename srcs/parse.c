/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:51:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/05 19:52:54 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		read_first_line(t_lem *info)
{
	char		*line;
	char		*ptr;
	
	RET_IF(get_next_line(FT_STDIN_FILENO, &line) < 1, panic(PARS_ERR));
	ptr = line;
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	if (*ptr)
		panic(READ_ERR);
	info->num_ants = ft_atoi(line);
	free(line);
}

void		read_rooms_conns(t_lem *info)
{
	(void)info;
}

void		parse_input(t_lem *info)
{
	read_first_line(info);
	read_rooms_conns(info);
}
