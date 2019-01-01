/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 18:54:41 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/20 12:40:06 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(const char *s)
{
	size_t	s_len;
	char	*new;
	char	*ptr;

	s_len = ft_strlen(s);
	NULL_CHECK(!(new = (char *)malloc((s_len + 1) * sizeof(char))));
	ptr = new;
	while (*s)
		s++;
	s--;
	while (*s)
		*ptr++ = *s--;
	*ptr = '\0';
	return (new);
}
