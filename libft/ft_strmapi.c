/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 12:51:38 by acarlson          #+#    #+#             */
/*   Updated: 2018/09/17 14:57:47 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*cpy;
	int		i;

	if (s && (cpy = malloc((ft_strlen(s) + 1) * sizeof(char))))
	{
		i = 0;
		while (s[i])
		{
			cpy[i] = f(i, s[i]);
			i++;
		}
		cpy[i] = '\0';
	}
	else
		cpy = NULL;
	return (cpy);
}
