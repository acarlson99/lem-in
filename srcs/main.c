/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:55:50 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/08 20:52:22 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** TODO: only print out "ERROR\n"
*/

void		panic(int code)
{
	if (code == MALLOC_ERR)
		ft_dprintf(FT_STDERR_FILENO, "Malloc error\n");
	else if (code == ROOM_ERR)
		ft_dprintf(FT_STDERR_FILENO, "Room error\n");
	else if (code == START_ERR)
		ft_dprintf(FT_STDERR_FILENO, "Start error\n");
	else if (code == END_ERR)
		ft_dprintf(FT_STDERR_FILENO, "End error\n");
	else if (code == CONN_ERR)
		ft_dprintf(FT_STDERR_FILENO, "Connection error\n");
	else if (code == PARS_ERR)
		ft_dprintf(FT_STDERR_FILENO, "File read error\n");
	else if (code == READ_ERR)
		ft_dprintf(FT_STDERR_FILENO, "Read error\n");
	else
		ft_dprintf(FT_STDERR_FILENO, "ERROR\n");
	exit(EXIT_FAILURE);
}

/*
** TODO: remove ifdef
** current format minimizes norm errors
*/

int			main(void)
{
	t_lem		*info;
	int			i;

	i = 0;
#ifdef LLDB
	i = 1;
#endif
	while (i)
		;
	init_lem(&info);
	parse_input(info);
	exit(EXIT_SUCCESS);
}
