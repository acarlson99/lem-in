/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssize_ttoabase.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:59:02 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/11 14:59:24 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ssize_ttoabase(ssize_t n, int base)
{
	char		*new;
	ssize_t		is_neg;
	ssize_t		i;

	i = ft_snumlen(n, base);
	NULL_CHECK(!(new = (char *)malloc((i + 1) * sizeof(char))));
	new[i] = '\0';
	is_neg = 0;
	if (n == 0)
		new[--i] = '0';
	else if (n < 0)
	{
		new[--i] = -(n % base) < 10 ?\
-(n % base) + '0' : -(n % base) + 'a' - 10;
		n /= base;
		n = -n;
		is_neg = 1;
	}
	while (n != 0)
	{
		new[--i] = (n % base < 10) ? n % base + '0' : n % base + 'a' - 10;
		n /= base;
	}
	is_neg ? new[--i] = '-' : 0;
	return (new);
}
