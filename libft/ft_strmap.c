/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:41:14 by acarlson          #+#    #+#             */
/*   Updated: 2018/09/17 14:55:00 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*cpy;
	int		i;

	if (s && (cpy = (char *)malloc((ft_strlen(s) + 1) * sizeof(char))))
	{
		i = 0;
		while (s[i])
		{
			cpy[i] = f(s[i]);
			i++;
		}
		cpy[i] = '\0';
	}
	else
		cpy = NULL;
	return (cpy);
}
