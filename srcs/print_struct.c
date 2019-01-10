/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:28:23 by callen            #+#    #+#             */
/*   Updated: 2019/01/09 16:36:25 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// TODO: remove this file eventually.  These are not needed anywhere

void		print_rooms(t_lem *info)
{
	t_list	*ptr;

	ptr = info->rooms;
	while (ptr)
	{
		ft_printf("Room %s ", R(ptr)->name);
		ft_printf("x %2d y %2d ", R(ptr)->x, R(ptr)->y);
		ft_printf("start_end %3d\n", R(ptr)->start_end);
		ptr = ptr->next;
	}
}

void		print_conns(t_lem *info)
{
	t_list	*ptr;
	t_list	*p2;

	ptr = info->rooms;
	while (ptr)
	{
		p2 = R(ptr)->conns;
		while (p2)
		{
			ft_printf("%s-%s\n", R(ptr)->name, R(p2)->name);
			p2 = p2->next;
		}
		ptr = ptr->next;
	}
}
