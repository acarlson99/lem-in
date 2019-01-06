/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 14:03:45 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/05 19:52:45 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

/*
** START == 69 == 'E'
** END == -92
** R(a): macro for typecasting t_list->content from void* to t_room*
** adjacency list struct as array of linked lists
*/

# define START	((char)69)
# define END	((char)420)
# define R(a)	((!a) ? (0) : ((t_room*)a->content))

# define MALLOC_ERR 1
# define ROOM_ERR 2
# define START_ERR 4
# define END_ERR 8
# define CONN_ERR 16
# define PARS_ERR 32
# define READ_ERR 64

typedef struct s_room	t_room;
typedef struct s_lem	t_lem;
typedef struct s_lst	t_lst;
typedef struct s_lsts	t_lsts;

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
	t_list		*conns;
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
	t_list		*conns;
	t_room		*start;
	t_room		*end;
};

void		parse_input(t_lem *info);
void		panic(int code);
void		init_lem(t_lem **info);

#endif
