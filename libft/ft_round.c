/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:34:03 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/25 14:35:50 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Rounds the double n to the pth place
*/

#include "libft.h"

double		ft_round(double n, size_t p)
{
	size_t	shift;
	int		fl;

	shift = 0;
	while (shift <= p)
	{
		n *= 10;
		shift++;
	}
	fl = ft_floor(n);
	if (fl % 10 >= 5)
	{
		n = (double)(fl + 10 - fl % 10);
		while (shift--)
			n /= 10;
	}
	if (fl % 10 <= 4)
	{
		n = (double)(fl - fl % 10);
		while (shift--)
			n /= 10;
	}
	return (n);
}
