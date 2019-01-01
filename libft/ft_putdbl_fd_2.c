/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdbl_fd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:23:40 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/05 17:23:52 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putdbl_fd_2(double n, size_t precision, int fd)
{
	int		n1;
	int		ret;
	size_t	p;

	p = precision;
	n1 = n < 0 ? ft_ceil(n) : ft_floor(n);
	ret = ft_putnbr_fd_2(n1, fd);
	n -= (double)n1;
	n = n < 0 ? -n : n;
	RET_IF(p == 0, ret);
	ret += ft_putchar_fd_2('.', fd);
	while (p > 0)
	{
		n *= 10;
		ret += ft_putchar_fd_2(ft_floor(n) + '0', fd);
		n -= (double)ft_floor(n);
		p--;
	}
	return (ret);
}
