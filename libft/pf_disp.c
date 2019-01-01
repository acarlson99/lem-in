/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_disp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:24:52 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 14:24:36 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static const t_fun_ptr g_get_function[] =
{
	['s'] = pf_print_string,
	['S'] = pf_print_string,
	['p'] = pf_print_pointer,
	['d'] = pf_print_int,
	['D'] = pf_print_int,
	['i'] = pf_print_int,
	['o'] = pf_print_oct,
	['O'] = pf_print_oct,
	['u'] = pf_print_unsigned,
	['U'] = pf_print_unsigned,
	['x'] = pf_print_hex,
	['X'] = pf_print_hex,
	['c'] = pf_print_char,
	['C'] = pf_print_char,
	['b'] = pf_print_bin,
	['%'] = pf_print_percent
};

int		pf_dispatch_func(const char *fmt, int *count, va_list args_list)
{
	t_pf_info	info;
	int			n;
	char		c;

	n = ft_strcspn(fmt, CONVERSIONS);
	c = fmt[n];
	info.options = pf_find_options(c, fmt);
	info.mod = pf_find_modifier(c, fmt, n);
	RET_IF(info.options == -1 || info.mod == -1, ft_strspn(fmt, RECOGNIZED));
	info.str = ft_strndup(fmt, n + 1);
	info.min_field_width = pf_get_min_field(info.str);
	info.prec_spec = ft_isin('.', info.str);
	info.precision = info.prec_spec ? pf_get_precision(info) : 0;
	if (info.prec_spec && c != '%')
	{
		info.options |= ZERO;
		info.options ^= ZERO;
	}
	*count = *count + g_get_function[(int)c](info, args_list);
	free(info.str);
	return (n + 1);
}
