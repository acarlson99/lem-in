/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:28:23 by callen            #+#    #+#             */
/*   Updated: 2019/01/18 18:10:26 by acarlson         ###   ########.fr       */
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
		ft_dprintf(2, "Room %s ", (*ptr)->name);
		ft_dprintf(2, "x %2d y %2d ", (*ptr)->x, (*ptr)->y);
		ft_dprintf(2, "start_end %3d\n", (*ptr)->start_end);
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
			ft_dprintf(2, "%d ", graph[y][x]);
			x++;
		}
		y++;
		ft_putchar_fd('\n', 2);
	}
}

void		print_list(t_list *l)
{
	int		p;

	p = 0;
	while (l)
	{
		ft_printf("%s%s", p ? "-" : "", l->content);
		p = 1;
		l = l->next;
	}
	ft_putchar('\n');
}
