/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:55:50 by acarlson          #+#    #+#             */
/*   Updated: 2019/02/11 18:01:10 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		panic(int code)
{
	if (code == MALLOC_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: Malloc error\n");
	else if (code == ROOM_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: Room error\n");
	else if (code == START_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: Start error\n");
	else if (code == END_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: End error\n");
	else if (code == CONN_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: Connection error\n");
	else if (code == PARS_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: File read error\n");
	else if (code == READ_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: Read error\n");
	else if (code == NOPATH_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: No path from start to end\n");
	else if (code == ANTNUM_ERR)
		ft_dprintf(FT_STDERR_FILENO, "ERROR: Illegal number of ants\n");
	else
		ft_dprintf(FT_STDERR_FILENO, "ERROR: Unhandled panic code\n");
	exit(EXIT_FAILURE);
}

int			main(void)
{
	t_lem		*info;

	init_lem(&info);
	parse_input(info);
	print_input(info->num_ants, info->lines);
	ft_putchar('\n');
	solve(info);
	exit(EXIT_SUCCESS);
}
