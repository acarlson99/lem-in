/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:27:25 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 14:28:12 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int					pf_print_percent(t_pf_info info, va_list args_list)
{
	int		padding;
	int		count;

	(void)args_list;
	info.len = 1;
	count = 0;
	padding = info.min_field_width;
	if (IS_NEG_FIELD(info.options))
		count += ft_putchar_fd_2('%', g_printf_fd);
	while (padding-- > info.len)
		count += ft_putchar_fd_2(IS_ZERO(info.options) ? '0' : ' ', PF_FD);
	if (!(IS_NEG_FIELD(info.options)))
		count += ft_putchar_fd_2('%', g_printf_fd);
	return (count);
}
