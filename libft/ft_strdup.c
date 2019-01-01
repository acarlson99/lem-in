/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 20:36:47 by acarlson          #+#    #+#             */
/*   Updated: 2018/09/23 18:29:28 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*ptr;
	int		i;

	NULL_CHECK(!(str = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1)));
	ptr = str;
	i = 0;
	while (*s1)
		*str++ = *s1++;
	*str = '\0';
	return (ptr);
}
