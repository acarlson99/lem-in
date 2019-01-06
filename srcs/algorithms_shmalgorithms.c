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
	t_lst *ctmp, *tmp;
	int i, j;

	RET_NONE(!info);
	ft_printf("info = %p\n", info);
	ft_printf("info->num_rooms = %u\n", info->num_rooms);
	ft_printf("info->num_ants = %u\n", info->num_ants);
	ft_printf("info->rooms = %p\n", *info->rooms);
	ft_printf("info->start = %p\n", info->start);
	ft_printf("info->end = %p\n", info->end);
	RET_NONE(!info->rooms);
	ft_printf("lstlen(info->rooms) = %d\n", ft_lstln(info->rooms));
	for (i = 0, tmp = info->rooms; tmp; i++)
	{
		ft_printf("  info->rooms[%d]->r = %p\n", i, tmp->r);
		ft_printf("    info->rooms[%d]->next = %p\n", i, tmp->next);
		ft_printf("    info->rooms[%d]->r->full = %hhd\n", i, tmp->r->full);
		ft_printf("    info->rooms[%d]->r->visited = %hhd\n", i, tmp->r->visited);
		ft_printf("    info->rooms[%d]->r->start_end = %hhd\n", i, tmp->r->start_end);
		ft_printf("    info->rooms[%d]->r->coord_x = %d\n", i, tmp->r->coord_x);
		ft_printf("    info->rooms[%d]->r->coord_y = %d\n", i, tmp->r->coord_y);
		ft_printf("    info->rooms[%d]->r->name = %s\n", i, tmp->r->name);
		ft_printf("    info->rooms[%d]->r->connections = %p\n", i, tmp->r->connections);
		for (j = 0, ctmp = tmp->r->connections; ctmp; j++)
		{
			ft_printf("      info->rooms[%d]->r->connections[%d]->r = %p\n", i, j, ctmp->r);
			ft_printf("      info->rooms[%d]->r->connections[%d]->next = %p\n", i, j, ctmp->next);
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
	ft_printf("info->conns = %p\n", info->conns);
	ft_printf("info->start = %p\n", info->start);
	ft_printf("info->end = %p\n", info->end);
	for (i = 0, ttmp = info->conns; ttmp; i++, ttmp = ttmp->next)
	{
		ft_printf("info->conns[%d]->r = %p\n", i, R(ttmp));
		ft_printf("  info->conns[%d]->next = %p\n", i, ttmp->next);
		ttmp->next ? ft_printf("    info->conns[%d]->next->r = %p\n", i, R(ttmp->next)) : 0;
		ttmp->next ? ft_printf("    info->conns[%d]->next->next = %p\n", i, ttmp->next->next) : 0;
		ft_printf("  info->conns[%d]->r->name = %p\n", i, R(ttmp)->name);
		ft_printf("  info->conns[%d]->r->conns = %p\n", i, R(ttmp)->conns);
		for (j = 0, cctmp = R(ttmp)->conns; cctmp; j++, cctmp = cctmp->next)
		{
			ft_printf("    info->conns[%d]->r->connections[%d]->r = %p\n", i, j, R(cctmp));
			ft_printf("    info->conns[%d]->r->connections[%d]->next = %p\n", i, j, cctmp->next);
		}
	}
}

void	check_graph(t_lem *l)
{
	if (!l->start || !l->end)
		lemon_hcf();
	
}
