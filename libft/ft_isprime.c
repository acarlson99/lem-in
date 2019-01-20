/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 18:01:38 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/19 20:03:16 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isprime(size_t n)
{
	/* int		upper_bound; */
	size_t	i;

	/* upper_bound = ft_ceil(ft_sqrt((double)n)); */
	if (n <= 1)
		return (0);
	else if (n % 2 == 0 && n > 2)
		return (0);
	i = 3;
	while (i < n / 2)
	{
		if (n % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}
