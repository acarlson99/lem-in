/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/11 15:48:28 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			is_path(int **graph, int *parent, size_t s, size_t t, size_t size)
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
				if (parent)
					parent[v] = u;
				// ft_printf("parent[%d] = %d\n", v, u);
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

int			fordFulkerson(t_room **rooms, int **graph, size_t s, size_t t, size_t size)
{
	int			**rgraph;
	int			*parent;
	int			max_flow;
	int			path_flow;
	size_t		u;
	size_t		v;

	rgraph = malloc_conns(size);
	max_flow = 0;
	path_flow = 0;
	u = 0;
	while (u < size)
	{
		v = 0;
		while (v < size)
		{
			rgraph[u][v] = graph[u][v];
			v++;
		}
		u++;
	}
	if (!(parent = malloc(sizeof(int) * size)))
		panic(MALLOC_ERR);
	while (is_path(rgraph, parent, s, t, size))
	{
		ft_printf("L1-%s\n", rooms[size - 1]->name);
		path_flow = FT_INT_MAX;
		v = t;
		while (v != s)
		{
			u = parent[v];
			ft_printf("L1-%s\n", rooms[parent[v]]->name);
			path_flow = MIN(path_flow, rgraph[u][v]);
			v = parent[v];
		}
		v = t;
		while (v != s)
		{
			u = parent[v];
			rgraph[u][v] -= path_flow;
			rgraph[v][u] += path_flow;
			v = parent[v];
		}
//		ft_putchar('\n');
		max_flow += path_flow;
	}
	return (max_flow);
}

void		solve(t_lem *info)	// TODO: implement
{
	fordFulkerson(info->rooms, info->conns, 0, info->num_rooms - 1, info->num_rooms);	// The max flow for test_01 is 3, but that doesn't count the number of ants per room.  Only ants per edge.  Counting rooms as full gives a max flow of 2
//	ft_printf("Find path from %s to %s\n", info->rooms[0]->name,	\
//				info->rooms[info->num_rooms - 1]->name);
}

/*
** 0  1  2  3  4  5  6  7  8
** 3->6->4->0->3->0->3->0->4
** 8->4->3->0
** 2->5->6->1
*/
