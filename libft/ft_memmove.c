/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 16:07:46 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/24 15:37:48 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dptr;
	unsigned char	*sptr;

	dptr = (unsigned char *)dst;
	sptr = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (dst < src)
		while (len--)
			*dptr++ = *sptr++;
	else
	{
		while (len--)
			*(dptr + len) = *(sptr + len);
	}
	return (dst);
}
