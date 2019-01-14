/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 16:24:32 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/13 16:15:32 by acarlson         ###   ########.fr       */
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

void		print_input(unsigned num_ants, t_line *ptr)
{
	ft_printf("%u\n", num_ants);
	while (ptr)
	{
		ft_printf("%s\n", (char *)ptr->line);
		ptr = ptr->next;
	}
}

void		enqueue_num(t_queue *q, size_t n)
{
	size_t	*n_;

	if (!(n_ = (size_t *)malloc(sizeof(size_t))))
		panic(MALLOC_ERR);
	*n_ = n;
	ft_enqueue(q, n_);
}

size_t		dequeue_num(t_queue *q)
{
	void		*ptr;
	size_t		n;

	ptr = ft_dequeue(q);
	n = ((size_t *)ptr)[0];
	free(ptr);
	return (n);
}
