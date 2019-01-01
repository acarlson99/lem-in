/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdbl_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:22:16 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/29 20:12:18 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putdbl_fd(double n, size_t precision, int fd)
{
	int		n1;
	size_t	p;

	p = precision;
	n1 = n < 0 ? ft_ceil(n) : ft_floor(n);
	ft_putnbr_fd(n1, fd);
	n -= (double)n1;
	n = n < 0 ? -n : n;
	RET_NONE(p == 0);
	ft_putchar_fd('.', fd);
	while (p > 0)
	{
		n *= 10;
		ft_putchar_fd(ft_floor(n) + '0', fd);
		n -= (double)ft_floor(n);
		p--;
	}
}
