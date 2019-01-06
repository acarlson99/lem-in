/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 17:48:41 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/02 22:40:22 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
//TODO: move functions into separate files as necessary
//TODO: Personal: listen to acarlson
void		print_lem(t_lem *info)
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
	ft_printf("lstlen(info->rooms) = %d\n", lstlen(info->rooms));
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

void		print_lem_addr(t_lem *info)
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

int			ft_strccount(const char *s, int c)
{
	int total;

	total = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == c)
			total++;
		s++;
	}
	return (total);
}

void		free_str_tab(char ***tab)
{
	int i;

	i = 0;
	while ((*tab)[i] != NULL)
	{
		free((*tab)[i]);
		i++;
	}
	free((*tab));
}

t_lst		*lstnew(t_room *r)
{//replace with ft_lstnew
	t_lst *new;

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))//TODO: give cork
		return (0);
	new->r = r;
	new->next = 0;
	return (new);
}

void		free_lst(t_lst *lst)
{
	t_lst *tmp;

	while (lst)
	{
		tmp = lst;
		lst->r->name ? free(lst->r->name) : 0;
		lst->r ? free(lst->r) : 0;
		lst = lst->next;
		tmp ? free(tmp) : 0;
	}
}

void	lemin_hcf()
{
	ft_dprintf(STDERR_FILENO, "ERROR\n");
	exit(EXIT_FAILURE);
}

void	init_lem(t_lem **l)
{
	if (!(*l = (t_lem*)malloc(sizeof(t_lem))))
		lemin_hcf();
	(*l)->num_rooms = 0;
	(*l)->num_ants = 0;
	(*l)->rooms = 0;
	(*l)->conns = 0;
	(*l)->start = 0;
	(*l)->end = 0;
}

t_room		*init_room(char *name, char *x, char *y)
{
	t_room	*new;
	char	*tmp;

	if (!(new = (t_room*)malloc(sizeof(t_room))))
		lemin_hcf();
	new->full = 0;
	new->visited = 0;
	new->start_end = 0;
	new->coord_x = ft_atoi(x);
	new->coord_y = ft_atoi(y);
	tmp = ft_strdup(name);
	new->name = tmp;
	new->connections = 0;
	new->conns = 0;
	return (new);
}

void		free_room(t_room *r)
{
	if (r)
	{
		if (r->name)
			free(r->name);
		free(r);
	}
}

void		lstadd(t_lst **h, t_lst *n)
{//replace with ft_listadd
	n->next = *h;
	*h = n;
}

void		lstpush(t_lst **h, t_room *r)
{//modify to use t_list
	t_lst *new;

	RET_NONE((!(new = lstnew(r))));//TODO: acquire plug
	lstadd(h, new);
	ft_printf("(t_lst*) h = %p\n", *h);
	ft_printf("lstlen(*h) = %d\n", lstlen(*h));
}

void		ft_lstpush(t_list **h, t_room *r)
{
	t_list *new;

	new = ft_lstnew(r, sizeof(*r));
	ft_lstadd(h, new);
}

void		read_connections(t_lem *info, char **line)
{
	t_list	*tmp[2];

	if (!line)
		return ;
	tmp[0] = info->conns;
	while (tmp[0])
	{
		if (R(tmp[0]) && R(tmp[0])->name && !ft_strcmp(R(tmp[0])->name, line[0]))
		{
			tmp[1] = info->conns;
			while (tmp[1])
			{
				if (!ft_strcmp(R(tmp[1])->name, line[1]))
				{
					ft_lstpush(&(R(tmp[0])->conns), R(tmp[1]));//TODO: get the mario brothers
					ft_lstpush(&(R(tmp[1])->conns), R(tmp[0]));//TODO: call another plumber
					ft_printf("ft_lstlen(R(info->conns)->conns) = %d\n", ft_lstlen(R(info->conns)->conns));
					break ;
				}
				tmp[1] = tmp[1]->next;
			}
		}
		tmp[0] = tmp[0]->next;
	}
	free_str_tab(&line);
}

void		read_node(t_lem *info, char *line)
{
	char	**t;
	t_room	*tr;

	t = ft_strsplit(line, ' ');
	tr = init_room(t[0], t[1], t[2]);
	ft_lstpush(&(info->conns), tr);
	free_str_tab(&t);
	info->num_rooms++;
}

void		readmap(t_lem **info)
{
	char	*line;
	int		i[3] = {0};

	while (get_next_line(0, &line) > 0)
	{
		!i[0] ? (*info)->num_ants = ft_atoi(line) : 0;
		if (!ft_strccount(line, '#') && ft_strccount(line, '-') == 1)
		{
			ft_printf("--------begin read_connections---------\n");
			read_connections((*info), ft_strsplit(line, '-'));
			free(line);
			ft_printf("---------end read_connections----------\n");
			continue ;
		}
		else if (i[0] && ft_strccount(line, ' ') == 2)
			read_node((*info), line);
		i[1] ? (*info)->start = R((*info)->conns) : 0;
		(*info)->start ? i[1] = 0 : 0;
		i[2] ? (*info)->end = R((*info)->conns) : 0;
		(*info)->end ? i[2] = 0 : 0;
		(!ft_strcmp("##end", line) && !i[2]) ? i[2] = 1 : 0;
		(!ft_strcmp("##start", line) && !i[1]) ? i[1] = 1 : 0;
		i[0]++;
		free(line);
	}
}

void		ft_debug()
{
	return ;
}

unsigned	ft_lstlen(t_list *l)
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

unsigned	lstlen(t_lst *l)
{
	unsigned	i;
	t_lst		*tmp;

	i = 0;
	tmp = l;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/*
** read file lines into linked list, then put info into properly sized array?
** -1 if start
** 1 if end
*/

int			main(void)
{// perhaps use array of t_room* for faster access
	t_lem	*info;

	init_lem(&info);
	readmap(&info);
	if (info->conns)
	{
		info->start->start_end = START;
		info->end->start_end = END;
		ft_debug();
		print_lem_addr(info);
	}
	ft_printf("info = %p\n", info);pause();
	exit(0);
}
