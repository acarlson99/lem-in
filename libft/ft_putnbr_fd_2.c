/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:22:40 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/05 17:22:51 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_fd_2(int n, int fd)
{
	int ret;

	ret = 0;
	if (n <= -10 || n >= 10)
		ret += ft_putnbr_fd_2(n / 10, fd);
	else if (n < 0)
		ret += ft_putchar_fd_2('-', fd);
	if (n < 0)
		ret += ft_putchar_fd_2('0' - n % 10, fd);
	else
		ret += ft_putchar_fd_2('0' + n % 10, fd);
	return (ret);
}
