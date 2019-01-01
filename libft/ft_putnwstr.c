/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 23:12:55 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/13 23:21:31 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnwstr_fd(wchar_t *ws, size_t n, int fd)
{
	size_t len;
	size_t tmp;
	size_t ret;

	if (!(ws))
		return (ft_putnstr_fd("(null)", n, fd));
	len = 0;
	ret = ft_wstrlen(ws);
	while (*ws != L'\0' && n--)
	{
		ft_putwchar_fd(*ws, fd);
		tmp = ft_wcharlen(*ws);
		len += tmp;
		ws++;
		if (tmp == 0)
			return (ret);
		if (len >= ret)
			return (ret);
	}
	return (ret);
}
