/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:49:46 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/07 14:38:57 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strspn(const char *s, const char *charset)
{
	size_t		n;

	n = 0;
	while (s[n] && ft_isin(s[n], charset))
		n++;
	return (n);
}
