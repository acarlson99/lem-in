/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 20:12:44 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 20:18:55 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrealloc(char *str, size_t len)
{
	char	*tmp;

	NULL_CHECK(!(tmp = ft_strnew(len)));
	tmp = ft_strcat(tmp, str);
	str = tmp;
	free(tmp);
	return (str);
}
