/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/12 20:07:40 by acarlson         ###   ########.fr       */
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

void		add_ant(t_antq *a, t_list *start, int n)
{
	t_ant		*ant;

	if (!(ant = (t_ant *)ft_memalloc(sizeof(t_ant))))
		panic(MALLOC_ERR);
	ant->num = n;
	ant->room = start;
	ant->next = NULL;
	if (!a->head)
		a->head = ant;
	if (!a->tail)
		a->tail = ant;
	else
	{
		a->tail->next = ant;
		a->tail = ant;
	}
}

int			move_ants(t_antq *all_ants)
{
	t_ant		*ant;
	char		a;

	ant = all_ants->head;
	a = 0;
	while (ant)
	{
		if (ant->room)
		{
			ft_printf("%sL%d-%s", (a ? " " : ""), ant->num, ant->room->content);
			ant->room = ant->room->next;
			a = 1;
		}
		ant = ant->next;
	}
	return (a);
}

void		solve(t_lem *info)	// TODO: implement
{
	t_list		**list;
	t_antq		*all_ants;
	size_t		n;
	size_t		i;
	size_t		lstindex;

	list = ft_memalloc(sizeof(t_list *) * info->num_rooms);
	fordFulkerson(info->rooms, info->conns, info->num_rooms, list);	// The max flow for test_01 is 3, but that doesn't count the number of ants per room.  Only ants per edge.  Counting rooms as full gives a max flow of 2
	// TODO: print all ant movements possible followed by a newline
	if (!(all_ants = (t_antq *)ft_memalloc(sizeof(t_antq))))
		panic(MALLOC_ERR);
	n = 0;
	i = 0;
	while (1)
	{
		lstindex = 0;
		while (list[lstindex])
		{
			n++;
			if (n <= info->num_ants)
			{
				if (!list[i])
					i = 0;
				add_ant(all_ants, list[i], n);
				i++;
			}
			lstindex++;
		}
		if (!move_ants(all_ants))
			exit(0);
		ft_putchar('\n');
	}
}
