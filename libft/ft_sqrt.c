/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 14:50:16 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/23 15:46:13 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_sqrt(double n)
{
	double old;
	double new;

	old = n;
	new = 0;
	while (old > 0)
	{
		new = 0.5 * (old + (n / old));
		if (ft_abs(new - old) / old < 0.0001)
			break ;
		old = new;
	}
	return (new);
}
