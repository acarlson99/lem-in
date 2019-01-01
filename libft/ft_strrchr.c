/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 20:13:04 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/28 16:40:53 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *s_cpy;
	char *cptr;

	s_cpy = (char *)s;
	cptr = NULL;
	while (*s_cpy)
	{
		if (*s_cpy == c)
			cptr = s_cpy;
		s_cpy++;
	}
	if (*s_cpy == c)
		return (s_cpy);
	return (cptr);
}
