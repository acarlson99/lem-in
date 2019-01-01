/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 17:52:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/18 17:53:41 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_exit(char *message, char *color, int code)
{
	ft_putstr_fd(color, 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(NC, 2);
	exit(code);
}
