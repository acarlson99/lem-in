/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 14:03:45 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/01 18:12:31 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define START -1
# define END 1

typedef struct s_room	t_room;
typedef struct s_lem	t_lem;
typedef struct s_lst	t_lst;

/*
** sizeof(t_lst) = 16 bytes
*/

struct		s_lst
{
	t_room		*r;
	t_lst		*next;
};

/*
** sizeof(t_room) = 32 bytes
*/

struct		s_room
{
	char		full;
	char		visited;
	char		start_end;
	int			coord_x;
	int			coord_y;
	char		*name;
	t_lst		*connections;
};

/*
** sizeof(t_lem) = 32 bytes
*/

struct		s_lem
{
	unsigned	num_rooms;
	unsigned	num_ants;
	t_lst		*rooms;
	t_room		*start;
	t_room		*end;
};

int			ft_strccount(const char *s, int c);
void		free_str_tab(char ***t);
t_lst		*lstnew(t_room *r);
void		free_lst(t_lst *l);
t_room		*init_room(char *name, char *x, char *y);
void		lstpush(t_lst **h, t_lst *n);
void		readmap(t_lem **info);
unsigned	lstlen(t_lst *l);
void		print_lem(t_lem *info);
void		begone_ants(t_lem **info);
void		read_connections(t_lem *info, char **line);

#endif
