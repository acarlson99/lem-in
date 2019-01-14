/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:17:41 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/13 15:42:53 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			add_line(t_line **list, char *line)
{
	static t_line	*ptr = NULL;
	t_line			*new;

	if (!ptr)
	{
		ptr = *list;
		while (ptr && ptr->next)
			ptr = ptr->next;
	}
	else if (ptr->next)
		ptr = ptr->next;
	if (!(new = (t_line *)malloc(sizeof(t_line))))
		panic(MALLOC_ERR);
	new->line = line;
	new->next = NULL;
	if (!ptr)
		ptr = new;
	else
	{
		ptr->next = new;
		ptr = ptr->next;
	}
	if (!*list)
		*list = new;
}
