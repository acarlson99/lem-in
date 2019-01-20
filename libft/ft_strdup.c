/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 20:36:47 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/19 20:02:28 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*ptr;

	NULL_CHECK(!(str = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1)));
	ptr = str;
	while (*s1)
		*str++ = *s1++;
	*str = '\0';
	return (ptr);
}
