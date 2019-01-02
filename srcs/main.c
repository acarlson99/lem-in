/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 17:48:41 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/01 18:13:42 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_lst(t_lst *lst)
{
	t_lst *tmp;

	while (lst)
	{
		tmp = lst;
		lst->r->name ? free(lst->r->name) : 0;
		lst->r->connections ? free_lst(lst->r->connections) : 0;
		lst->r ? free(lst->r) : 0;
		lst = lst->next;
		tmp ? free(tmp) : 0;
	}
	lst = 0;
	tmp = 0;
}

void	free_struct(t_lem **info)
{
	free_lst((*info)->rooms);
	free((*info)->start);
	(*info)->start = 0;
	free((*info)->end);
	(*info)->end = 0;
	free((*info));
	*info = 0;
	info = 0;
}

t_lem	*init_lem()
{
	t_lem	*new;

	new = (t_lem*)malloc(sizeof(t_lem));
	new->num_rooms = 0;
	new->rooms = 0;
	new->start = 0;
	new->end = 0;
	return (new);
}

t_room	*init_room(char *name, int x, int y)
{
	t_room *new;

	if (!(new = (t_room*)malloc(sizeof(t_room))))
		return (0);
	new->full = 0;
	new->visited = 0;
	new->start_end = 0;
	new->coord_x = x;
	new->coord_y = y;
	new->name = ft_strdup(name);
	new->connections = 0;
	return (new);
}

t_lst	*lstnew(t_room *r)
{
	t_lst *new;

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (0);
	new->r = r;
	new->next = 0;
	return (new);
}

int		main(void)
{
	t_lem	*info;
	t_room	*tmp;

	info = init_lem();
	tmp = init_room("puscetti", 2, 5);
	info->rooms = lstnew(tmp);
	ft_printf("info->rooms->r->name = %s\n", info->rooms->r->name);
	ft_printf("info->rooms->r = %p\n", info->rooms->r);
	free_struct(&info);
	ft_printf("info = %p\n", info);
}
