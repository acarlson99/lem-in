/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:55:50 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/11 00:42:02 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#ifdef LEAKS
# define exit while (1); exit	// TODO: remove
#endif

void		panic(int code)	// TODO" only print "ERROR\n" to stderr
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
	else if (code == NOPATH_ERR)
		ft_dprintf(FT_STDERR_FILENO, "No path from start to end\n");
	else if (code == ANTNUM_ERR)
		ft_dprintf(FT_STDERR_FILENO, "Illegal number of ants\n");
	else
		ft_dprintf(FT_STDERR_FILENO, "ERROR\n");
	exit(EXIT_FAILURE);
}

int			main(void)
{
	t_lem		*info;

#ifdef LLDB	// TODO: remove
	int			i;

	i = 1;
	while (i)
		;
#endif

	init_lem(&info);
	parse_input(info);
	print_input(info);
	ft_putchar('\n');
	solve(info);
	exit(EXIT_SUCCESS);
}
