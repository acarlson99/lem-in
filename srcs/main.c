/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:55:50 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/06 16:23:37 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		panic(int code)
{//TODO: print to STDERR_FILENO and only print out "ERROR\n"
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
	exit(EXIT_FAILURE);
}

int			main(void)
{
	t_lem		*info;

	init_lem(&info);
	parse_input(info);
	exit(EXIT_SUCCESS);
}
