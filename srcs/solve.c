/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/19 12:19:18 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define M_ERR MALLOC_ERR
#define IN(v) (v * 2)
#define OUT(v) (v * 2 + 1)

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

	DO_IF(!(visited = (int *)ft_memalloc(sizeof(int) * size)), panic(M_ERR));
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

int			fordFulkerson(t_room **rooms, int **rgraph, size_t size, t_list **list)
{
	int			*parent;
	int			max_flow;
	int			path_flow;
	size_t		u;
	size_t		v;
	t_list		*ptr = NULL;
	size_t		index;

	index = 0;
	max_flow = 0;
	path_flow = 0;
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
		// Start new list
		list[index] = ptr;
		index++;
		t_list *p2 = ptr;
		int flag = 0;
		while (p2 && p2->next)
		{
			for (size_t i = 0; i < index - 1; i++)
			{
				t_list *p1 = list[i];
				while (p1 && p1->next)
				{
					if (!ft_strcmp(p1->content, p2->content))
					{
						/* ft_printf("Freeing list "); */
						/* print_list(list[i]); */
						/* ft_printf("Line '%s' overlaps\n", p1->content); */
						ft_lstdel(&list[i], free_);
						index--;
						list[i] = list[index];
						list[index] = NULL;
						flag = 1;
						break ;
					}
					p1 = p1->next;
				}
			}
			if (flag)
				break ;
			p2 = p2->next;
		}
		ptr = NULL;
		while (v != S)
		{
			u = parent[v];
			rgraph[u][v] -= path_flow;
			rgraph[v][u] += path_flow;
			v = parent[v];
		}
		ptr = NULL;
		max_flow += path_flow;
	}
	free(parent);
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

#define CONT_IF(n) if (n) continue ;
#define PLSHLP (len_tmp > len_min + (info->num_ants - n) && ++i)
#define PLSHLPP (len_tmp + (abs_max >= 5 ? 1 : 0) > (info->num_ants - n + (abs_max >= 5 ? 0 : len_min - 2)) && ++i) // If it requires adjusting to "work," then it does not work

void		ant_loop(t_lem *info, t_list **list,\
					t_antq *all_ants, size_t len_min, size_t num_paths, size_t avg_path_len)
{
	size_t		i;
	size_t		len_tmp;
	size_t		n;

	size_t		len_max = 0;
	size_t		abs_max = 0;

	n = 1;
	while (1)
	{
		i = 0;
		while (list[i])
		{
			len_tmp = ft_lstlen(list[i]);
			if (len_tmp > abs_max)
				abs_max = len_tmp;
			CONT_IF(PLSHLPP);	// FIXME: This line is broken.  Exemplified by map_06.  So we have to figure out whether it would be better for the ant to go down the suggested path or a different path AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA HOLY FUCK THIS LINE OH MY GOD FIX THIS RUN LEMIN WITH TEST MAP 06 AND FIX THE THING THAT IS FUCKED OHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGODOHMYGOD
			if (len_max < len_tmp)
				len_max = len_tmp;
			if (n <= info->num_ants)
			{
				CONT_IF(!list[i] && !(i = 0));
				add_ant(all_ants, list[i], n);
				n++;
			}
			i++;
		}
		if (!move_ants(all_ants))
		{
			ft_dprintf(2, "longest path %zu\n", abs_max);
			ft_dprintf(2, "len_max: longest path taken %zu\n", len_max);
			ft_dprintf(2, "len_min %zu\n", len_min);
			i = 0;
			while (list[i])
				i++;
			ft_dprintf(2, "Number of paths: %zu\n", i);
			exit(0);
		}
		ft_putchar('\n');
	}
}

/*
** The max flow for test_01 is 3, but that doesn't count the number of ants	\
** per room.  Only ants per edge.  Counting rooms as full gives a max flow of 2
*/

#include <fcntl.h>

void		solve(t_lem *info)
{
	size_t		i[3];

	info->rgraph = copy_graph(info->conns, info->num_rooms);
	info->list = ft_memalloc(sizeof(t_list *) * info->num_rooms);
	ft_dprintf(2, "max flow = %d\n",fordFulkerson(info->rooms, info->rgraph, info->num_rooms, info->list)); // TODO: make a better function to find all paths to take
	if (!(info->all_ants = (t_antq *)ft_memalloc(sizeof(t_antq))))
		panic(MALLOC_ERR);
	i[2] = FT_SIZE_T_MAX;
	info->l2 = find_path(info);
	i[0] = 0;

	size_t avg_path_len = 0;

	while (info->l2[i[0]])
	{
		i[1] = ft_lstlen(info->l2[i[0]]);
		avg_path_len += i[1];
		if (i[1] < i[2])
			i[2] = i[1];
		i[0]++;
	}
	avg_path_len /= i[0];
	ant_loop(info, info->l2, info->all_ants, i[2], i[0], avg_path_len);
}
