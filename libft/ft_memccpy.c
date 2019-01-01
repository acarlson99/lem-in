/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:12:21 by acarlson          #+#    #+#             */
/*   Updated: 2018/09/16 16:05:38 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dptr;
	unsigned char	*sptr;

	i = -1;
	dptr = (unsigned char *)dst;
	sptr = (unsigned char *)src;
	while (++i < n)
	{
		dptr[i] = sptr[i];
		if (dptr[i] == (unsigned char)c)
			return (dst + i + 1);
	}
	return (NULL);
}
