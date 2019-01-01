/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 18:15:40 by acarlson          #+#    #+#             */
/*   Updated: 2018/09/24 19:35:31 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char *str;
	char *ptr;

	NULL_CHECK(!(str = (char *)malloc((n + 1) * sizeof(char))));
	ptr = str;
	while (n)
	{
		*str++ = *s1++;
		n--;
	}
	*str = '\0';
	return (ptr);
}
