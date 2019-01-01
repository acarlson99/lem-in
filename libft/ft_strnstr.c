/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:37:01 by acarlson          #+#    #+#             */
/*   Updated: 2018/09/16 16:06:56 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay_copy;
	int		i;
	int		j;
	int		i2;
	size_t	len_cpy;

	hay_copy = (char *)haystack;
	len++;
	i = -1;
	if (needle[0] == '\0')
		return (hay_copy);
	while (hay_copy[++i] && len--)
	{
		j = 0;
		i2 = i;
		len_cpy = len;
		while (needle[j] && hay_copy[i2] == needle[j] && len_cpy--)
		{
			j++;
			i2++;
			if (needle[j] == '\0')
				return (hay_copy + i);
		}
	}
	return (NULL);
}
