/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 14:03:45 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/31 14:03:52 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct		s_room
{
	unsigned char	full;
	unsigned char	visited;
	unsigned char	is_end;
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
