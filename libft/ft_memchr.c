/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 19:07:47 by acarlson          #+#    #+#             */
/*   Updated: 2018/09/27 21:12:30 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	const char	*sptr;
	size_t		i;

	sptr = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (*(sptr + i) == (char)c)
			return ((void *)sptr + i);
		i++;
	}
	return (NULL);
}
