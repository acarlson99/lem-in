/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atosize_tbase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:32:45 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/09 13:32:51 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_atosize_tbase(const char *str, int base)
{
	size_t	n;
	size_t	sign;

	n = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= (MIN('0' + base - 1, '9')))
			n = n * base + *str - '0';
		else if (*str >= 'a' && *str <= ('a' + base - 11))
			n = n * base + *str - 'a' + 10;
		else
			break ;
		str++;
	}
	return (n * sign);
}
