/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/17 14:41:51 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define S (0)
#define T (size - 1)
#define IN(v) (v * 2)
#define OUT(v) (v * 2 + 1)

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

t_list		**find_paths(int **conns, int **rgraph, size_t size, t_room **rooms)	// Uses original graph and residual graph and finds which paths were taken
{
	size_t		x;
	size_t		y;
	size_t		v;
	size_t		i;
	t_list		**l;
	size_t		j;
	t_list		*p1;
	t_list		*p2;
	int			flag;

	if (!(l = ft_memalloc(size * sizeof(t_list *))))
		panic(MALLOC_ERR);
	j = 0;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (conns[y][x] && !rgraph[y][x])
			{
				v = S;
				while (v != T)
				{
//					ft_printf("%s%s", v ? "-" : "", rooms[v]->name);
					if (v != S)
						ft_lstadd_tail(&l[j], ft_lstnew(rooms[v]->name, ft_strlen(rooms[v]->name) + 1));
					i = 0;
					while (i < size)
					{
						if (!rgraph[v][i] && rgraph[i][v])
						{
							rgraph[i][v] = 1;
							rgraph[v][i] = 1;
							v = i;
							break ;
						}
						i++;
					}
				}
//				ft_printf("-%s\n", rooms[T]->name);
				ft_lstadd_tail(&l[j], ft_lstnew(rooms[v]->name, ft_strlen(rooms[v]->name) + 1));
				j++;
				p2 = l[j - 1];
				flag = 0;
				while (p2 && p2->next)
				{
					for (size_t m = 0; m < j - 1; m++)
					{
						p1 = l[m];
						while (p1 && p1->next)
						{
							if (!ft_strcmp(p1->content, p2->content))
							{
								if (ft_lstlen(p1) > ft_lstlen(p2))	// TODO: del p1 and move p2 to p1
								{
									flag = 1;
									ft_lstdel(&l[m], free_);
									l[m] = l[j - 1];
									l[j - 1] = NULL;
									j--;
								}
								else	// TODO: del p2 and set it to NULL
								{
									flag = 1;
									ft_lstdel(&l[j - 1], free_);
									l[j - 1] = NULL;
									j--;
								}
							}
							p1 = p1->next;
						}
					}
					if (flag)
						break ;
					p2 = p2->next;
				}
//				ft_printf("L1-%s\n", rooms[T]->name);
			}
			x++;
		}
		y++;
	}
	l[j] = NULL;
	return (l);
}

/*
** The max flow for test_01 is 3, but that doesn't count the number of ants	\
** per room.  Only ants per edge.  Counting rooms as full gives a max flow of 2
*/

void		solve(t_lem *info)
{
	t_list		**list;
	t_list		**l2;
	t_antq		*all_ants;
	size_t		i;
	size_t		len_tmp;
	size_t		len_min;
	int			**rgraph;

	rgraph = copy_graph(info->conns, info->num_rooms);
	list = ft_memalloc(sizeof(t_list *) * info->num_rooms);
	fordFulkerson(info->rooms, rgraph, info->num_rooms, list);	// TODO: make a better function to find all paths to take
	if (!(all_ants = (t_antq *)ft_memalloc(sizeof(t_antq))))
		panic(MALLOC_ERR);
	len_min = FT_SIZE_T_MAX;
	l2 = find_paths(info->conns, rgraph, info->num_rooms, info->rooms);
	i = 0;
	while (l2[i])
	{
		len_tmp = ft_lstlen(l2[i]);
		if (len_tmp < len_min)
			len_min = len_tmp;
		i++;
	}
	ant_loop(info, l2, all_ants, len_min);
}
