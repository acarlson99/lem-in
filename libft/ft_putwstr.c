/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:08:34 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/13 22:59:50 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putwstr_fd(wchar_t *ws, int fd)
{
	size_t len;
	size_t tmp;
	size_t ret;

	len = 0;
	ret = ft_wstrlen(ws);
	while (*ws != L'\0')
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
