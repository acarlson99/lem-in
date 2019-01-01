/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:27:00 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 14:27:41 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int			pf_print_bin_meat(t_pf_info info, char *str, int n)
{
	int		count;

	count = 0;
	if (IS_ALT(info.options) && n != 0)
		MFW -= 2;
	if ((IS_NEG_FIELD(info.options) || IS_ZERO(info.options))\
		&& IS_ALT(info.options) && n != 0)
		count += ft_putstr_fd_2("0b", g_printf_fd);
	if (IS_NEG_FIELD(info.options))
		if (!(info.prec_spec) || PREC != 0 || n != 0)
			count += pf_print_int_precision(info, str, 0);
	count += pf_print_min_field_width(info, 0);
	if ((!(IS_NEG_FIELD(info.options) || IS_ZERO(info.options)))\
		&& IS_ALT(info.options) && n != 0)
		count += ft_putstr_fd_2("0b", g_printf_fd);
	if (!(IS_NEG_FIELD(info.options)))
		if (!(info.prec_spec) || PREC != 0 || n != 0)
			count += pf_print_int_precision(info, str, 0);
	return (count);
}

int					pf_print_bin(t_pf_info info, va_list args_list)
{
	char	*str;
	int		count;
	size_t	n;

	n = pf_extract_va_arg_unsigned(info, args_list);
	str = ft_size_ttoabase(n, 2);
	count = 0;
	if (info.prec_spec && PREC == 0 && n == 0)
		info.len = 0;
	else
		info.len = ft_unumlen(n, 2);
	count += pf_print_bin_meat(info, str, n);
	free(str);
	return (count);
}
