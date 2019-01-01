/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:27:29 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 14:28:12 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int					pf_print_pointer(t_pf_info info, va_list args_list)
{
	int			count;
	char		*str;
	ssize_t		n;

	count = 0;
	info.mod = PRINTF_LONGLONG;
	n = pf_extract_va_arg_unsigned(info, args_list);
	str = ft_ssize_ttoabase(n, 16);
	info.len = ft_snumlen(n, 16) + 2;
	if (info.prec_spec && n == 0)
		MFW++;
	if (IS_NEG_FIELD(info.options))
		count += ft_putstr_fd_2("0x", g_printf_fd);
	if (IS_NEG_FIELD(info.options) && (!(info.prec_spec)\
									|| PREC != 0 || n != 0))
		count += pf_print_int_precision(info, str, 0);
	count += pf_print_min_field_width(info, 0);
	if (!(IS_NEG_FIELD(info.options)))
		count += ft_putstr_fd_2("0x", g_printf_fd);
	if (!(IS_NEG_FIELD(info.options)) && (!(info.prec_spec)\
									|| PREC != 0 || n != 0))
		count += pf_print_int_precision(info, str, 0);
	free(str);
	return (count);
}
