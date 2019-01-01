/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 17:27:54 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/29 20:12:17 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putflt(float n, size_t precision)
{
	int		n1;
	size_t	p;

	p = precision;
	n1 = n < 0 ? ft_ceil(n) : ft_floor(n);
	ft_putnbr(n1);
	n -= (float)n1;
	n = n < 0 ? -n : n;
	RET_NONE(p == 0);
	ft_putchar('.');
	while (p > 0)
	{
		n *= 10;
		ft_putchar(ft_floor(n) + '0');
		n -= (float)ft_floor(n);
		p--;
	}
}
