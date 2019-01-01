/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:52:54 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/09 12:03:53 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putcstr_fd(char *s, int c, int fd)
{
	size_t		len;

	len = 0;
	RET_IF(!(s), 0);
	while (s[len] && s[len] != c)
		len++;
	write(fd, s, len);
	return (len);
}
