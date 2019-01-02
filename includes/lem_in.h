/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 14:03:45 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/01 17:07:29 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define START -1
# define END 1

typedef struct		s_room
{
	unsigned char	full;
	unsigned char	visited;
	char			start_end;
	int				coord_x;
	int				coord_y;
	char			*name;
	t_list			*connections;
}					t_room;

typedef struct		s_lem
{
	unsigned	num_rooms;
	t_list		*rooms;
	t_list		*start;
	t_list		*end;
}					t_lem;

#endif
