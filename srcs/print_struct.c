/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:28:23 by callen            #+#    #+#             */
/*   Updated: 2019/01/13 19:32:46 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TODO: remove this file

void		print_rooms(t_room **rooms, size_t size)
{
	t_room		**ptr;

	ptr = rooms;
	while (ptr && *ptr && size--)
	{
		ft_printf("Room %s ", (*ptr)->name);
		ft_printf("x %2d y %2d ", (*ptr)->x, (*ptr)->y);
		ft_printf("start_end %3d\n", (*ptr)->start_end);
		ptr++;
	}
}

void		print_conns(int **graph, size_t size)
{
	size_t		x;
	size_t		y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			ft_printf("%d ", graph[y][x]);
			x++;
		}
		y++;
		ft_putchar('\n');
	}
}
