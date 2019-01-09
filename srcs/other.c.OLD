/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms_shmalgorithms.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:18:01 by callen            #+#    #+#             */
/*   Updated: 2019/01/05 19:18:20 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	lemon_hcf()
{
	ft_dprintf(STDERR_FILENO, "ERROR\n");
	exit(EXIT_FAILURE);
}

static unsigned	ft_lstln(t_list *l)
{
	unsigned	i;
	t_list		*tmp;

	i = 0;
	tmp = l;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void		prnt_lem(t_lem *info)
{//Definitely will not norme
	t_list *ctmp, *tmp;
	int i, j;

	RET_NONE(!info);
	ft_printf("info = %p\n", info);
	ft_printf("info->num_rooms = %u\n", info->num_rooms);
	ft_printf("info->num_ants = %u\n", info->num_ants);
	ft_printf("info->rooms = %p\n", info->rooms);
	ft_printf("info->start = %p\n", info->start);
	ft_printf("info->end = %p\n", info->end);
	RET_NONE(!info->rooms);
	ft_printf("lstlen(info->rooms) = %d\n", ft_lstln(info->rooms));
	for (i = 0, tmp = info->rooms; tmp; i++)
	{
		ft_printf("  info->rooms[%d]) = %p\n", i, R(tmp));
		ft_printf("    info->rooms[%d]->next = %p\n", i, tmp->next);
		ft_printf("    info->rooms[%d])->full = %hhd\n", i, R(tmp)->full);
		ft_printf("    info->rooms[%d])->visited = %hhd\n", i, R(tmp)->visited);
		ft_printf("    info->rooms[%d])->start_end = %hhd\n", i, R(tmp)->start_end);
		ft_printf("    info->rooms[%d])->coord_x = %d\n", i, R(tmp)->coord_x);
		ft_printf("    info->rooms[%d])->coord_y = %d\n", i, R(tmp)->coord_y);
		ft_printf("    info->rooms[%d])->name = %s\n", i, R(tmp)->name);
		ft_printf("    info->rooms[%d])->conns = %p\n", i, R(tmp)->conns);
		for (j = 0, ctmp = R(tmp)->conns; ctmp; j++)
		{
			ctmp ? ft_printf("      R(R(info->rooms[%d])->conns[%d]) = %p\n", i, j, R(ctmp)) : 0;
			ctmp->next ? ft_printf("      R(R(info->rooms[%d])->conns[%d]->next) = %p\n", i, j, R(ctmp->next)) : 0;
			ctmp = ctmp->next;
		}
		tmp = tmp->next;
	}
}

static void		prnt_lem_addr(t_lem *info)
{
	t_list *cctmp, *ttmp;
	int i, j;

	RET_NONE(!info);
	ft_printf("info = %p\n", info);
	ft_printf("info->rooms = %p\n", info->rooms);
	ft_printf("info->start = %p\n", info->start);
	ft_printf("info->end = %p\n", info->end);
	for (i = 0, ttmp = info->rooms; ttmp; i++, ttmp = ttmp->next)
	{
		ft_printf("R(info->rooms[%d]) = %p\n", i, R(ttmp));
		ttmp->next ? ft_printf("  R(info->rooms[%d]->next) = %p\n", i, R(ttmp->next)) : 0;
		ttmp->next ? ft_printf("    R(info->rooms[%d]->next) = %p\n", i, R(ttmp->next)) : 0;
		ttmp->next && ttmp->next->next ? ft_printf("    R(info->rooms[%d]->next->next) = %p\n", i, R(ttmp->next->next)) : 0;
		ft_printf("  R(info->rooms[%d])->name = %p\n", i, R(ttmp)->name);
		ft_printf("  R(info->rooms[%d])->conns = %p\n", i, R(ttmp)->conns);
		for (j = 0, cctmp = R(ttmp)->conns; cctmp; j++, cctmp = cctmp->next)
		{
			ft_printf("    R(R(info->rooms[%d])->conns[%d]) = %p\n", i, j, R(cctmp));
			ft_printf("    R(R(info->rooms[%d])->conns[%d]->next) = %p\n", i, j, R(cctmp->next));
		}
	}
}

void	check_graph(t_lem *l)
{//TODO: check rooms for loops and such
	int		i;
	t_room	*tmp[2];

	if (!l->start || !l->end)
		panic(ROOM_ERR);
	i = 0;
	tmp[0] = R(l->rooms);
	while (tmp[0]->start_end != END && i <= l->num_rooms)
	{
		if (tmp[0] && !tmp[0]->visited)
		{
			tmp[0]->visited = 1;
			tmp[1] = tmp[0];
			tmp[0] = R(tmp[0]->conns);
		}
	}
}
