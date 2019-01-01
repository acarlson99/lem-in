/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_ttoabase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:47:52 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/09 13:14:28 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_size_ttoabase(size_t n, int base)
{
	char	*new;
	size_t	i;

	i = ft_unumlen(n, base);
	NULL_CHECK(!(new = (char *)malloc((i + 1) * sizeof(char))));
	new[i] = '\0';
	if (n == 0)
		new[--i] = '0';
	while (n != 0)
	{
		new[--i] = (n % base < 10) ? n % base + '0' : n % base + 'a' - 10;
		n /= base;
	}
	return (new);
}
