/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putrstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:36:05 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/16 16:07:00 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putrstr_fd(char *s, int fd)
{
	int i;
	int j;

	i = ft_strlen(s);
	j = i;
	while (i >= 0)
	{
		ft_putchar_fd(s[i], fd);
		i--;
	}
	return (j);
}
