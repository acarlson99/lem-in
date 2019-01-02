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

struct	s_lst
{
	t_room		*r;
	t_lst		*next;
};

struct	s_room
{
	char		full;
	char		visited;
	char		start_end;
	int			coord_x;
	int			coord_y;
	char		*name;
	t_lst		*connections;
};

struct	s_lem
{
	unsigned	num_rooms;
	t_lst		*rooms;
	t_room		*start;
	t_room		*end;
};

#endif
