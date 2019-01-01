/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:21:38 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/05 17:21:40 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putendl_fd_2(char const *s, int fd)
{
	int		ret;

	ret = 0;
	if (s)
	{
		ret += ft_putstr_fd_2(s, fd);
		ret += ft_putchar_fd_2('\n', fd);
	}
	return (ret);
}
