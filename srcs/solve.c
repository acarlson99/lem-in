/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/10 15:22:30 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		dumb_free(void *ptr, size_t size)
{
	(void)size;
	free(ptr);
}

void		solve(t_lem *info)	// TODO: implement
{
	unsigned	n;
	t_list		*ants;

	n = 1;
	ants = NULL;
	while (1)
	{
		if (n <= info->num_ants)
			ft_lstadd_tail(&ants, ft_lstnew((void *)&((t_ant){.num=n++,\
								.room=info->start}), sizeof(t_ant)));
		else
			break ;
	}
	ft_lstdel(&ants, dumb_free);
}
