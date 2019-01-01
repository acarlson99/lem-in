/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:39:09 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/23 11:46:37 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(unsigned long n, int sign)
{
	if (sign == 1 && n >= (unsigned long)FT_LONG_MAX)
		return (-1);
	else if (sign == -1 && n >= (unsigned long)FT_LONG_MIN)
		return (0);
	else
		return (n * sign);
}

int			ft_atoi(const char *str)
{
	unsigned long	n;
	int				sign;

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
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		str++;
	}
	return (check(n, sign));
}
