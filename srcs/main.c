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

void		lstpush(t_lst **h, t_lst *n)
{
	if (n && h)
	{
		n->next = *h;
		*h = n;
	}
}

void		read_connections(t_lem *info, char **line)
{
	t_lst	*tmp1;
	t_lst	*tmp2;

	if (!line)
		return ;
	tmp1 = info->rooms;
	while (tmp1)
	{
		if (!ft_strcmp(tmp1->r->name, line[0]))
		{
			tmp2 = info->rooms;
			while (tmp2)
			{
				if (!ft_strcmp(tmp2->r->name, line[1]))
				{
					lstpush(&tmp1->r->connections, tmp2);
					lstpush(&tmp2->r->connections, tmp1);
					break ;
				}
				tmp2 = tmp2->next;
			}
		}
		tmp1 = tmp1->next;
	}
	free_str_tab(&line);
}

int			readmap(t_lem *info)
{//TODO: test that this actually works, and figure out parsing map connections
	char	*line;
	char	**t;
	int		i[3] = {0};

	while (get_next_line(0, &line) > 0)
	{
		!i[0] ? info->num_ants = ft_atoi(line) : 0;
		if (line[0] != '#' && ft_strccount(line, '-') == 1)
			read_connections(info, ft_strsplit(line, '-'));//TODO: this is some Bowsers Dog Dick
		else if (i[0] && ft_strccount(line, ' ') == 2)
		{
			t = ft_strsplit(line, ' ');
			lstpush(&info->rooms, lstnew(init_room(t[0], t[1], t[2])));
			DO_ALL(1, free_str_tab(&t), info->num_rooms++);
		}
		i[1] ? info->start = info->rooms->r : 0;
		info->start ? i[1] = 0 : 0;
		i[2] ? info->end = info->rooms->r : 0;
		info->end ? i[2] = 0 : 0;
		(!ft_strcmp("##end", line) && !i[2]) ? i[2] = 1 : 0;
		(!ft_strcmp("##start", line) && !i[1]) ? i[1] = 1 : 0;
		i[0]++;
		free(line);
	}
	return (0);
}

void		ft_debug()
{
	return ;
}

void	begone_ants(t_lem **info)
{//TODO: ack
	free(*info);
	*info = NULL;
}

/*
** take care when using info.rooms->r->connections as it's infinitely recursive
** -1 if start
** 1 if end
*/

int			main(void)
{// perhaps use array of t_room* for faster access
	t_lem	*info;

	init_lem(&info);
	readmap(info);
	info->start->start_end = (char)420;
	info->start->start_end = 69;
	ft_debug();
	ft_printf("info = %p\n", info);
	ft_printf("info->num_rooms = %u\n", info->num_rooms);
	ft_printf("info->num_ants = %u\n", info->num_ants);
	ft_printf("info->rooms = %p\n", info->rooms);
	ft_printf("info->start = %p\n", info->start);
	ft_printf("info->end = %p\n", info->end);
	ft_printf("info->rooms->r = %p\n", info->rooms->r);
	ft_printf("info->rooms->r->name = %s\n", info->rooms->r->name);
	ft_printf("info->rooms->r->coord_x = %d\n", info->rooms->r->coord_x);
	ft_printf("info->rooms->r->coord_y = %d\n", info->rooms->r->coord_y);
	free_lst(info->rooms);
	begone_ants(&info);
	ft_printf("info = %p\n", info);
	return (0);
}
