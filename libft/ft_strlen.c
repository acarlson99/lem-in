/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 16:58:40 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/02 17:29:38 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#if FT_LONG_BIT == 32
# define STRLEN_MASK01 0x01010101
# define STRLEN_MASK80 0x80808080
# define STRLEN_MAX_CHECK 4
#elif FT_LONG_BIT == 64
# define STRLEN_MASK01 0x0101010101010101UL
# define STRLEN_MASK80 0x8080808080808080UL
# define STRLEN_MAX_CHECK 8
#endif

#define LONGPTR_MASK (sizeof(long) - 1)

size_t		ft_strlen(const char *str)
{
	const char				*p;
	const unsigned long		*lp;
	int						i;

	p = str;
	while ((uintptr_t)p & LONGPTR_MASK)
	{
		if (!(*p))
			return (p - str);
		p++;
	}
	lp = (const unsigned long *)p;
	while (1)
	{
		if ((*lp - STRLEN_MASK01) & STRLEN_MASK80)
		{
			p = (const char *)lp;
			i = -1;
			while (++i < STRLEN_MAX_CHECK)
				if (!p[i])
					return (p - str + i);
		}
		lp++;
	}
	return (0);
}
