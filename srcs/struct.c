/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:21:52 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/06 16:00:44 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		init_lem(t_lem **info)
{
	if (!(*info = (t_lem *)malloc(sizeof(t_lem))))
		panic(MALLOC_ERR);
	(*info)->num_rooms = 0;
	(*info)->num_ants = 0;
	(*info)->lines = NULL;
	(*info)->rooms = NULL;
	(*info)->start = NULL;
	(*info)->end = NULL;
}
