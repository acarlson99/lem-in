/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:29:19 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/15 15:31:30 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void		add_ant(t_antq *a, t_list *start, int n)
{
	t_ant		*ant;

	if (!(ant = (t_ant *)ft_memalloc(sizeof(t_ant))))
		panic(MALLOC_ERR);
	ant->num = n;
	ant->room = start;
	ant->next = NULL;
	if (!a->head)
		a->head = ant;
	if (!a->tail)
		a->tail = ant;
	else
	{
		a->tail->next = ant;
		a->tail = ant;
	}
}
