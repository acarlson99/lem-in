/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 16:24:32 by acarlson          #+#    #+#             */
/*   Updated: 2019/02/11 11:58:58 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define COMMENT 1

/*
** returns START if start
** returns END if end
** returns 1 if comment
** returns 0 otherwise
*/

int			is_start_end(char *line)
{
	if (*line == '#')
	{
		if (!strcmp("##start", line))
			return (START);
		else if (!strcmp("##end", line))
			return (END);
		else
			return (COMMENT);
	}
	return (0);
}

void		print_input(unsigned num_ants, t_line *ptr)
{
	ft_printf("%u\n", num_ants);
	while (ptr)
	{
		ft_printf("%s\n", (char *)ptr->line);
		ptr = ptr->next;
	}
}

void		free_(void *ptr, size_t size)
{
	(void)size;
	free(ptr);
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
