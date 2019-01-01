/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 22:37:25 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/28 17:07:17 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		end;
	int		start;

	start = 0;
	NULL_CHECK(!(s));
	end = ft_strlen(s) - 1;
	while (ISWHITE(s[start]))
		start++;
	while (ISWHITE(s[end]) && end > start)
		end--;
	return (ft_strsub(s, start, end - start + 1));
}
