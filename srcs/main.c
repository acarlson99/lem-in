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
void		print_lem(t_lem *info)
{
	t_lst *ctmp, *tmp = info->rooms;
	int i, j;

	if (!info)
		return ;
	ft_printf("info = %p\n", info);
	ft_printf("info->num_rooms = %u\n", info->num_rooms);
	ft_printf("info->num_ants = %u\n", info->num_ants);
	ft_printf("info->rooms = %p\n", info->rooms);
	ft_printf("info->start = %p\n", info->start);
	ft_printf("info->end = %p\n", info->end);
	if (!info->rooms)
		return ;
	ft_printf("lstlen(info->rooms) = %d\n", lstlen(info->rooms));
	for (i = 0; tmp; i++)
	{
		ft_printf("  info->rooms[%d]->r = %p\n", i, tmp->r);
		ft_printf("  info->rooms[%d]->next = %p\n", i, tmp->next);
		ft_printf("  info->rooms[%d]->r->full = %hhd\n", i, tmp->r->full);
		ft_printf("  info->rooms[%d]->r->visited = %hhd\n", i, tmp->r->visited);
		ft_printf("  info->rooms[%d]->r->start_end = %hhd\n", i, tmp->r->start_end);
		ft_printf("  info->rooms[%d]->r->coord_x = %d\n", i, tmp->r->coord_x);
		ft_printf("  info->rooms[%d]->r->coord_y = %d\n", i, tmp->r->coord_y);
		ft_printf("  info->rooms[%d]->r->name = %s\n", i, tmp->r->name);
		ft_printf("  info->rooms[%d]->r->connections = %p\n", i, tmp->r->connections);
		for (j = 0, ctmp = tmp->r->connections; ctmp; j++)
		{
			ft_printf("    info->rooms[%d]->r->connections[%d]->r = %p\n", i, j, ctmp->r);
			ft_printf("    info->rooms[%d]->r->connections[%d]->next = %p\n", i, j, ctmp->next);
			ctmp = ctmp->next;
		}
		tmp = tmp->next;
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
{
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
	(*l)->rooms = 0;
	(*l)->start = 0;
	(*l)->end = 0;
}

t_room		*init_room(char *name, char *x, char *y)
{
	t_room *new;

	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (0);
	new->full = 0;
	new->visited = 0;
	new->start_end = 0;
	new->coord_x = ft_atoi(x);
	new->coord_y = ft_atoi(y);
	new->name = ft_strdup(name);
	new->connections = 0;
	return (new);
}

void		free_room(t_room *r)
{
	if (r && r->name)
		free(r->name);
	if (r)
		free(r);
}

void		lstadd(t_lst **h, t_lst *n)
{
	n->next = *h;
	*h = n;
}

void		lstpush(t_lst **h, t_room *r)
{
	t_lst *new;

	if (!(new = lstnew(r)))//TODO: acquire plug
		return ;
	lstadd(h, new);
}

void		read_connections(t_lem *info, char **line)
{
	t_lst	*tmp[2];

	if (!line)
		return ;
	tmp[0] = info->rooms;
	while (tmp[0])
	{
		if (tmp[0]->r && tmp[0]->r->name && !ft_strcmp(tmp[0]->r->name, line[0]))
		{
			tmp[1] = info->rooms;
			while (tmp[1])
			{
				if (!ft_strcmp(tmp[1]->r->name, line[1]))
				{
					lstpush(&tmp[0]->r->connections, tmp[1]->r);//TODO: call plumber
					lstpush(&tmp[1]->r->connections, tmp[0]->r);//TODO: call another plumber
					print_lem(info);
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
	lstpush(&(info->rooms), tr);
	free_str_tab(&t);
	info->num_rooms++;
}

void		readmap(t_lem **info)
{
	char	*line;
	int		i[4] = {0};

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
		i[1] ? (*info)->start = (*info)->rooms->r : 0;
		(*info)->start ? i[1] = 0 : 0;
		i[2] ? (*info)->end = (*info)->rooms->r : 0;
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
	info->start->start_end = START;
	info->end->start_end = END;
	ft_debug();
	print_lem(info);
	free_lst(info->rooms);
	free(info);
	ft_printf("info = %p\n", info);pause();
	exit(0);
}
