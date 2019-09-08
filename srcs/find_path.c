/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:53:25 by callen            #+#    #+#             */
/*   Updated: 2019/02/11 19:25:33 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Uses original graph and residual graph and finds which paths were taken
*/

t_list		**find_path(int **conns, int **rgraph, size_t size, t_room **rooms)
{
	size_t		x;
	size_t		y;
	size_t		v;
	size_t		i;
	t_list		**l;
	size_t		j;
	t_list		*p1;
	t_list		*p2;
	int			flag;

	if (!(l = ft_memalloc(size * sizeof(t_list *))))
		panic(MALLOC_ERR);
	j = 0;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (conns[y][x] && !rgraph[y][x])
			{
				v = S;
				while (v != T)
				{
					if (v != S)
						ft_lstadd_tail(&l[j], ft_lstnew(rooms[v]->name, ft_strlen(rooms[v]->name) + 1));
					i = 0;
					while (i < size)
					{
						if (!rgraph[v][i] && rgraph[i][v])
						{
							rgraph[i][v] = 1;
							rgraph[v][i] = 1;
							v = i;
							break ;
						}
						i++;
					}
				}
				ft_lstadd_tail(&l[j], ft_lstnew(rooms[v]->name, ft_strlen(rooms[v]->name) + 1));
				j++;
				p2 = l[j - 1];
				flag = 0;
				while (p2 && p2->next)
				{
					for (size_t m = 0; m < j - 1; m++)
					{
						p1 = l[m];
						while (p1 && p1->next)
						{
							if (!ft_strcmp(p1->content, p2->content))
							{
								if (ft_lstlen(p1) > ft_lstlen(p2))	// TODO: del p1 and move p2 to p1
								{
									flag = 1;
									ft_lstdel(&l[m], free_);
									l[m] = l[j - 1];
									l[j - 1] = NULL;
									j--;
								}
								else	// TODO: del p2 and set it to NULL
								{
									flag = 1;
									ft_lstdel(&l[j - 1], free_);
									l[j - 1] = NULL;
									j--;
								}
							}
							if (flag)
								break ;
							p1 = p1->next;
						}
						if (flag)
							break ;
					}
					if (flag)
						break ;
					p2 = p2->next;
				}
			}
			x++;
		}
		y++;
	}
	l[j] = NULL;
	return (l);
}
