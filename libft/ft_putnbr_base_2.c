/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:21:49 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/05 17:25:18 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_base_2(int n, int base)
{
	int		ret;
	char	*str;

	ret = 0;
	str = ft_itoabase(n, base);
	ret = ft_putstr_fd_2(str, 1);
	free(str);
	return (ret);
}
