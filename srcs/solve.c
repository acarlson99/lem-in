/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/02/11 14:53:32 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define M_ERR MALLOC_ERR
#define IN(v) (v * 2)
#define OUT(v) (v * 2 + 1)

size_t		g_moves;

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

int			is_invalid(unsigned ants_left, size_t total_paths, size_t num_paths, size_t path_len_sum, size_t len_min, size_t cand_len)	// TODO: check if cand_len is too long
{
	(void)total_paths;
	(void)len_min;
	// for every path
	// find the number of moves if the path is there
	// find the number of moves if the path is absent
	return ((path_len_sum / num_paths / ants_left) > ((path_len_sum - cand_len) / (num_paths - 1) / ants_left));
	// compare candidate path to average of all other paths
	return (cand_len > (path_len_sum - cand_len) / (num_paths - 1) + ants_left / (num_paths - 1));
}

/*
** Holy parameters
*/

void		update_array(t_list **list, size_t *lens, int *valid_arr, unsigned ants_left, size_t total_paths, size_t *num_paths, size_t *path_len_sum, size_t len_min)	// TODO: make this factor in multiple viable paths of multiple lengths.  Works when only comparing two paths.  Breaks on more than 2 paths
{
	size_t i = 0;

	ft_dprintf(FT_STDERR_FILENO, "valid: [");
	for (size_t m = 0; list[m]; m++)
		ft_dprintf(FT_STDERR_FILENO, "%zu, ", valid_arr[m]);
	ft_dprintf(FT_STDERR_FILENO, "]\n");
	ft_dprintf(FT_STDERR_FILENO, "lens: [");
	for (size_t m = 0; list[m]; m++)
		ft_dprintf(FT_STDERR_FILENO, "%zu, ", lens[m]);
	ft_dprintf(FT_STDERR_FILENO, "]\n");
	ft_dprintf(FT_STDERR_FILENO, "total_paths: %zu\n", total_paths);
	ft_dprintf(FT_STDERR_FILENO, "num_paths: %zu\n", *num_paths);
	ft_dprintf(FT_STDERR_FILENO, "path_len_sum: %zu\n", *path_len_sum);
	ft_dprintf(FT_STDERR_FILENO, "num_ants: %zu\n", ants_left);

	while (list[i])
	{
		if (*num_paths == 1)
			return ;
		// else if (valid_arr[i] && is_invalid(ants_left, total_paths, *num_paths, *path_len_sum, len_min, lens[i]))
		else if (valid_arr[i] && lens[i] >= (*path_len_sum - lens[i]) / (*num_paths - 1) + ants_left / (*num_paths - 1))
		{
			*path_len_sum = *path_len_sum - lens[i];
			lens[i] = -1;
			*num_paths = *num_paths - 1;
			valid_arr[i] = 0;
			ft_dprintf(2, "valid_arr[%zu]: %d len %zu num_ants: %u paths left: %zu path_len_sum: %zu name: %s\n", i, valid_arr[i], lens[i], ants_left, *num_paths, *path_len_sum, list[i]->content);
			return (update_array(list, lens, valid_arr, ants_left, total_paths, num_paths, path_len_sum, len_min));
		}
		else if (valid_arr[i]) {
			ft_dprintf(2, "Index %zu of len %zu lives name: %s\n", i, lens[i], list[i]->content);
		}
		i++;
	}
	return ;
}

void		print_path_chain(t_list *path)
{
	t_list	*tmp;
	int		z;

	z = 0;
	tmp = path;
	while (tmp)
	{
		if (!z)
		{
			ft_dprintf(2, "%s", tmp->content);
			z = 1;
		}
		else
			ft_dprintf(2, " -> %s", tmp->content);
		tmp = tmp->next;
	}
}

void		print_candidate_path_list(t_list **path)
{
	size_t	i;

	i = -1;
	ft_dprintf(2, "-------- List of Paths --------\n");
	while (path[++i])
	{
		ft_dprintf(2, " list[%zu] = ", i);
		print_path_chain(path[i]);
		ft_dprintf(2, "\n");
	}
}

void		ant_loop(t_lem *info, t_list **list, t_antq *all_ants, size_t len_min, size_t num_paths, size_t path_len_sum, size_t *lens)
{
	size_t		i;
	size_t		len_tmp;
	size_t		n;

	size_t		len_max = 0;
	size_t		abs_max = 0;
	size_t		total_paths = num_paths;
	int			flag = 0;
	unsigned	k = 0;
	unsigned	j = 0;
	char		*tmp_path_name = NULL;
	char		*long_path_name = NULL;
	int			*valid_arr = ft_memalloc(sizeof(int) * num_paths + 1);
	for (j = 0; j < num_paths; j++)
		valid_arr[j] = 1;

	n = 1;
	while (1)
	{
		i = 0;
		while (list[i] && !flag && n <= info->num_ants)
		{
			update_array(list, lens, valid_arr, info->num_ants - n + 1, total_paths, &num_paths, &path_len_sum, len_min);
			len_tmp = ft_lstlen(list[i]);
			tmp_path_name = list[i]->content;
			if (len_tmp > abs_max)
				abs_max = len_tmp;
			CONT_IF(!valid_arr[i] && ++i);	// FIXME: This line is broken. Exemplified by map_06. So we have to figure out whether it would be better for the ant to go down the suggested path or a different path
			if (n <= info->num_ants)
			{
				if (len_max < len_tmp)
				{
					len_max = len_tmp;
					long_path_name = tmp_path_name;
				}
				ft_dprintf(2, "taking path in list[%zu] (k = %u, j = %u, n = %zu)\n",i,k,j,n);
				add_ant(all_ants, list[i], n);
				n++;
			}
			else
				flag = 1;
			i++;
		}
		if (!move_ants(all_ants))
		{
			ft_dprintf(2, "%slongest path %zu%s\n",FG(GRN), abs_max, FG(DFT));
			ft_dprintf(2, "%slen_max: longest path taken %zu name %s%s\n", FG(GRN), len_max, long_path_name, FG(DFT));
			ft_dprintf(2, "%slen_min %zu%s\n", FG(GRN), len_min, FG(DFT));
			i = 0;
			while (list[i])
				i++;
			ft_dprintf(2, "%sNumber of paths: %zu%s\n", FG(GRN), i, FG(DFT));
			print_candidate_path_list(list);
			ft_dprintf(2, "%sTotal moves: %zu%s\n", FG(GRN), g_moves, FG(DFT));
			exit(0);
		}
		g_moves++;
		ft_putchar('\n');
	}
}

/*
** The max flow for test_01 is 3, but that doesn't count the number of ants	\
** per room.  Only ants per edge.  Counting rooms as full gives a max flow of 2
*/

void		solve(t_lem *info)
{
	size_t		i[3];

	info->rgraph = copy_graph(info->conns, info->num_rooms);
	info->list = ft_memalloc(sizeof(t_list *) * info->num_rooms);
	ft_dprintf(2, "%smax flow = %d%s\n",FG(GRN),fordFulkerson(info->rooms, info->rgraph, info->num_rooms, info->list),FG(DFT)); // TODO: make a better function to find all paths to take
	if (!(info->all_ants = (t_antq *)ft_memalloc(sizeof(t_antq))))
		panic(MALLOC_ERR);
	i[2] = FT_SIZE_T_MAX;
//	info->l2 = find_path(info);
	info->l2 = find_path(info->conns, info->rgraph, info->num_rooms, info->rooms);
	i[0] = 0;

	size_t path_len_sum = 0;
	size_t *lens = ft_memalloc(sizeof(size_t) * info->num_rooms);

	while (info->l2[i[0]])
	{
		i[1] = ft_lstlen(info->l2[i[0]]);
		lens[i[0]] = i[1];
		path_len_sum += i[1];
		if (i[1] < i[2])
			i[2] = i[1];
		i[0]++;
	}
	g_moves = 0;
	ant_loop(info, info->l2, info->all_ants, i[2], i[0], path_len_sum, lens);
}
