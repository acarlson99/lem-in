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

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
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
		lst->r->connections = 0;
		lst->r ? free(lst->r) : 0;
		lst = lst->next;
		tmp ? free(tmp) : 0;
	}
	lst = 0;
	tmp = 0;
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

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	new->r = r;
	new->next = *h;
	*h = new;
}

void		read_connections(t_lem *info, char **line)
{
	t_lst	*tmp[2];

	if (!line)
		return ;
	tmp[0] = info->rooms;
	while (tmp[0])
	{
		ft_printf("rc.tmp0.lstlen(info->rooms) = %u\n", lstlen(info->rooms));
		if (!ft_strcmp(tmp[0]->r->name, line[0]))
		{
			tmp[1] = info->rooms;
			while (tmp[1])
			{
				ft_printf("rc.tmp1.lstlen(info->rooms) = %u\n", lstlen(info->rooms));
				if (!ft_strcmp(tmp[1]->r->name, line[1]))
				{
					ft_printf("rc.lstpush.lstlen(info->rooms) = %u\n", lstlen(info->rooms));
					lstpush(&tmp[0]->r->connections, tmp[1]->r);
					lstpush(&tmp[1]->r->connections, tmp[0]->r);
					ft_printf("rc.break.lstlen(info->rooms) = %u\n", lstlen(info->rooms));
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
	t_lst	*tl;
	t_room	*tr;

	t = ft_strsplit(line, ' ');
	tr = init_room(t[0], t[1], t[2]);
	tl = lstnew(tr);
	lstpush(&(info->rooms), tl);
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
			read_connections((*info), ft_strsplit(line, '-'));
			ft_printf("readmap[%d].conn.lstlen((*info)->rooms) = %d\n", i[0], (i[3] = lstlen((*info)->rooms)));
			free(line);
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
	ft_printf("readmap.end.lstlen((*info)->rooms) = %d\n", lstlen((*info)->rooms));
}

void		ft_debug()
{
	return ;
}

void		print_lem(t_lem *info)
{
	if (!info)
		return ;
	ft_printf("info = %p\n", info);
	ft_printf("info->num_rooms = %u\n", info->num_rooms);
	ft_printf("info->num_ants = %u\n", info->num_ants);
	ft_printf("info->rooms = %p\n", info->rooms);
	ft_printf("info->start = %p\n", info->start);
	ft_printf("info->end = %p\n", info->end);
	// if (!info->rooms)
	// 	return ;
	// ft_printf("info->rooms->r = %p\n", info->rooms->r);
	// if (!info->rooms->r)
	// 	return ;
	// ft_printf("info->rooms->r->name = %s\n", info->rooms->r->name);
	// ft_printf("info->rooms->r->coord_x = %d\n", info->rooms->r->coord_x);
	// ft_printf("info->rooms->r->coord_y = %d\n", info->rooms->r->coord_y);
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

void	begone_ants(t_lem **info)
{//TODO: ack
	free(*info);
	*info = NULL;
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
	ft_printf("main.lstlen(info->rooms) = %d\n", lstlen(info->rooms));//Where in the world is info->rooms
	info->end->start_end = (char)420;
	info->start->start_end = 69;
	ft_printf("main.lstlen(info->rooms) = %d\n", lstlen(info->rooms));
	ft_debug();
	print_lem(info);
	free_lst(info->rooms);
	begone_ants(&info);
	ft_printf("info = %p\n", info);
	exit(0);
}
