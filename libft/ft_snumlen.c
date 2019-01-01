/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snumlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:33:22 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/09 13:33:26 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns number of characters in some number n in some base
*/

#include "libft.h"

size_t	ft_snumlen(ssize_t n, int base)
{
	size_t count;

	count = 0;
	if (n < 0)
		count++;
	else if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n /= base;
	}
	return (count);
}
