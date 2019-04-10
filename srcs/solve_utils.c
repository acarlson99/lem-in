/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:46:03 by callen            #+#    #+#             */
/*   Updated: 2019/04/09 17:46:08 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		path_helper(t_queue *q, int vu[2], int *parent, int *visited)
{
	enqueue_num(q, vu[0]);
	if (parent)
		parent[vu[0]] = vu[1];
	visited[vu[0]] = 1;
}

int			is_path(int **graph, int *parent, size_t size)
{
	t_queue		*q;
	size_t		u;
	size_t		v;
	int			*visited;
	int			n;

	DO_IF(!(visited = ft_memalloc(sizeof(int) * size)), panic(MALLOC_ERR));
	q = ft_queueinit();
	enqueue_num(q, S);
	while (!ft_queueisempty(q))
	{
		u = dequeue_num(q);
		v = 0;
		while (v < size)
		{
			if (visited[v] == 0 && graph[u][v] > 0)
				path_helper(q, (int[2]){v, u}, parent, visited);
			v++;
		}
	}
	n = visited[T];
	free(visited);
	free(q);
	return (n);
}

int			**copy_graph(int **graph, size_t size)
{
	size_t	u;
	size_t	v;
	int		**rgraph;

	rgraph = malloc_conns(size);
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
	return (rgraph);
}
