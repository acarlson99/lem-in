/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:21:17 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/09 13:14:07 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*new;
	int		is_neg;
	size_t	i;

	i = ft_snumlen(n, 10);
	NULL_CHECK(!(new = (char *)malloc((i + 1) * sizeof(char))));
	new[i] = '\0';
	is_neg = 0;
	if (n == 0)
		new[--i] = '0';
	else if (n < 0)
	{
		new[--i] = -(n % 10) + '0';
		n /= 10;
		n = -n;
		is_neg = 1;
	}
	while (n != 0)
	{
		new[--i] = n % 10 + '0';
		n /= 10;
	}
	if (is_neg)
		new[--i] = '-';
	return (new);
}
