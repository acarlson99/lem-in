/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/12 17:09:50 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define S (0)
#define T (size - 1)

int			is_path(int **graph, int *parent, size_t size)
{
	t_queue		*q;
	size_t		u;
	size_t		v;
	int			*visited;
	int			n;

	if (!(visited = (int *)ft_memalloc(sizeof(int) * size)))
		panic(MALLOC_ERR);
	q = ft_queueinit();
	enqueue_num(q, S);
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
				visited[v] = 1;
			}
			v++;
		}
	}
	n = visited[T];
	free(visited);
	free(q);
	return (n);
}

int			fordFulkerson(t_room **rooms, int **graph, size_t size, t_list **list)
{
	int			**rgraph;
	int			*parent;
	int			max_flow;
	int			path_flow;
	size_t		u;
	size_t		v;
	t_list		*ptr = NULL;
	size_t		index;

	index = 0;

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
	while (is_path(rgraph, parent, size))
	{
		// Add 'end' to list of paths
		ft_lstadd(&ptr, ft_lstnew(rooms[size - 1]->name, ft_strlen(rooms[size - 1]->name) + 1));
//		ft_printf("%s\n", ptr->content);
//		ft_printf("L1-%s\n", rooms[size - 1]->name);
		path_flow = FT_INT_MAX;
		v = T;
		while (v != S)
		{
			u = parent[v];
			// Push room to list
			if (ft_strcmp(rooms[parent[v]]->name, rooms[0]->name))
				ft_lstadd(&ptr, ft_lstnew(rooms[parent[v]]->name, ft_strlen(rooms[parent[v]]->name) + 1));
//			ft_printf("L1-%s\n", rooms[parent[v]]->name);
			path_flow = MIN(path_flow, rgraph[u][v]);
			v = parent[v];
		}
		v = T;
		while (v != S)
		{
			u = parent[v];
			rgraph[u][v] -= path_flow;
			rgraph[v][u] += path_flow;
			v = parent[v];
		}
		max_flow += path_flow;
		// Start new list
		list[index] = ptr;
		index++;
		ptr = NULL;
	}
	free(parent);
	u = 0;
	while (u < size)
	{
		free(rgraph[u]);
		u++;
	}
	free(rgraph);
	return (max_flow);
}

/*
** Make list of shortest augmenting paths
** This would be a t_list **ptr
** Null terminating string of t_list *ptrs
** Make list of ants
** Send ants down paths
**
** for n in paths:
**     send ant down path
** for a in ants:
**     move a closer to end
*/

void		solve(t_lem *info)	// TODO: implement
{
	t_list		**list;
	t_list		*ptr;
	size_t		n;

	list = ft_memalloc(sizeof(t_list *) * info->num_rooms);
	fordFulkerson(info->rooms, info->conns, info->num_rooms, list);	// The max flow for test_01 is 3, but that doesn't count the number of ants per room.  Only ants per edge.  Counting rooms as full gives a max flow of 2
	n = 0;
	while (list[n])
	{
		ptr = list[n];
		while (ptr)
		{
			ft_printf("L%d-%s\n", n + 1, ptr->content);
			ptr = ptr->next;
		}
//		ft_putchar('\n');
		n++;
	}
}
