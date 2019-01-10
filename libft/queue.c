/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:15:18 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/10 14:24:28 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_queue	*ft_queueinit(void)
{
	struct s_queue	*new;

	if (!(new = (struct s_queue *)malloc(sizeof(struct s_queue))))
		return (NULL);
	new->first = NULL;
	new->last = NULL;
	return (new);
}

void			ft_enqueue(struct s_queue *queue, void *content)
{
	struct s_qnode		*ptr;
	struct s_qnode		*new;

	if (!(queue && content))
		return ;
	if (!(new = (struct s_qnode *)malloc(sizeof(struct s_qnode))))
		return ;
	new->content = content;
	new->next = NULL;
	ptr = queue->first;
	if (!ptr)
	{
		queue->first = new;
		queue->last = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	queue->last = new;
}

void			*ft_dequeue(struct s_queue *queue)
{
	struct s_qnode		*a;
	struct s_qnode		*b;
	void				*content;

	if (!queue)
		return (NULL);
	if (!queue->first)
		return (NULL);
	a = queue->first;
	b = a->next;
	queue->first = b;
	if (!queue->first)
		queue->last = NULL;
	content = a->content;
	free(a);
	return (content);
}

void			*ft_queuepeek(struct s_queue *queue)
{
	if (!queue)
		return (NULL);
	if (!queue->first)
		return (NULL);
	return (queue->first->content);
}

int				ft_queueisempty(struct s_queue *queue)
{
	if (!queue)
		return (1);
	return (queue->first == NULL);
}
