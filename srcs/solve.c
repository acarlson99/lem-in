/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/15 15:14:01 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_(void *ptr, size_t size)
{
	(void)size;
	free(ptr);
}

void		print_list(t_list *l)
{
	int		p = 0;

	while (l) {
		ft_printf("%s%s", p ? "-" : "", l->content);
		p = 1;
		l = l->next;
	}
	ft_putchar('\n');
}

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
	u = 0;
	while (u < size)
	{
		free(rgraph[u]);
		u++;
	}
	free(rgraph);
	return (max_flow);
	// heh nice
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

size_t		ft_lstlen(t_list *ptr)
{
	size_t	i;

	i = 0;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

#define CONT_IF(n) if (n) continue ;

void		ant_loop(t_lem *info, t_list **list,\
						t_antq *all_ants, size_t len_min)
{
	size_t		i;
	size_t		len_tmp;
	size_t		n;

	n = 1;
	while (1)
	{
		i = 0;
		while (list[i])
		{
			len_tmp = ft_lstlen(list[i]);
			CONT_IF(len_tmp > len_min + (info->num_ants - n) && ++i);
			if (n <= info->num_ants)
			{
				CONT_IF(!list[i] && !(i = 0));
				add_ant(all_ants, list[i], n);
				n++;
			}
			i++;
		}
		if (!move_ants(all_ants))
			exit(0);
		ft_putchar('\n');
	}
}

/*
** The max flow for test_01 is 3, but that doesn't count the number of ants	\
** per room.  Only ants per edge.  Counting rooms as full gives a max flow of 2
*/

void		solve(t_lem *info)
{
	t_list		**list;
	t_antq		*all_ants;
	size_t		i;
	size_t		len_tmp;
	size_t		len_min;

	list = ft_memalloc(sizeof(t_list *) * info->num_rooms);
	fordFulkerson(info->rooms, info->conns, info->num_rooms, list);
	if (!(all_ants = (t_antq *)ft_memalloc(sizeof(t_antq))))
		panic(MALLOC_ERR);
	len_min = FT_SIZE_T_MAX;
	i = 0;
	while (list[i])
	{
		len_tmp = ft_lstlen(list[i]);
		if (len_tmp < len_min)
			len_min = len_tmp;
		i++;
	}
	ant_loop(info, list, all_ants, len_min);
}
