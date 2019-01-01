/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:58:06 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/05 17:03:02 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strcspn(const char *s, const char *charset)
{
	size_t		n;

	n = 0;
	while (!(ft_isin(s[n], charset)))
		n++;
	return (n);
}
