/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/11 03:25:04 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_path(int **graph, size_t s, size_t t, size_t size)
{
	t_queue		*q;
	size_t		u;
	size_t		v;
	int			*visited;
	int			n;

	if (!(visited = (int *)ft_memalloc(sizeof(int) * size)))
			panic(MALLOC_ERR);
	q = ft_queueinit();
	enqueue_num(q, s);
	while (!ft_queueisempty(q))
	{
		u = dequeue_num(q);
		v = 0;
		while (v < size)
		{
			if (visited[v] == 0 && graph[u][v] > 0)
			{
				enqueue_num(q, v);
				ft_printf("parent[%d] = %d\n", v, u);
				visited[v] = 1;
			}
			v++;
		}
	}
	n = visited[t];
	free(visited);
	free(q);
	return (n);
}

void		solve(t_lem *info)	// TODO: implement
{
	(void)info;
	ft_printf("Find path from %s to %s\n", info->rooms[0]->name,\
				info->rooms[info->num_rooms - 1]->name);
}

/*
** 0  1  2  3  4  5  6  7  8
** 3->6->4->0->3->0->3->0->4
** 8->4->3->0
** 2->5->6->1
*/
