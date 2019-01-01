/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:44:36 by acarlson          #+#    #+#             */
/*   Updated: 2018/09/25 18:53:19 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoibase(const char *str, int base)
{
	int	n;
	int	sign;

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
