/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:28:23 by callen            #+#    #+#             */
/*   Updated: 2019/01/11 01:18:40 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TODO: remove this file eventually.  These are not needed anywhere

void		print_rooms(t_lem *info)
{
	t_room		**ptr;

	ptr = info->rooms;
	while (ptr && *ptr)
	{
		ft_printf("Room %s ", (*ptr)->name);
		ft_printf("x %2d y %2d ", (*ptr)->x, (*ptr)->y);
		ft_printf("start_end %3d\n", (*ptr)->start_end);
		ptr++;
	}
}

void		print_conns(t_lem *info)
{
	size_t		x;
	size_t		y;

	y = 0;
	while (y < info->num_rooms)
	{
		x = 0;
		while (x < info->num_rooms)
		{
			ft_printf("%d ", info->conns[y][x]);
			x++;
		}
		y++;
		ft_putchar('\n');
	}
}
