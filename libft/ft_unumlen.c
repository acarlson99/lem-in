/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unumlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:33:11 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/12 17:02:43 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns number of digits in some number n in some base
*/

size_t		ft_unumlen(size_t n, int base)
{
	size_t		count;

	count = 0;
	RET_IF(n == 0, 1);
	while (n != 0)
	{
		count++;
		n /= base;
	}
	return (count);
}
