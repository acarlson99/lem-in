/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:27:29 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/18 10:26:53 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vect3	*ft_vectnew(double x, double y, double z)
{
	t_vect3	*new;

	new = (t_vect3 *)malloc(sizeof(t_vect3));
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}
