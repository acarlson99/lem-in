/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_str_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:27:34 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 14:28:12 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int					pf_print_wide_char(t_pf_info info, wchar_t wc)
{
	int		count;
	int		padding;

	count = 0;
	info.len = ft_wcharlen(wc);
	padding = info.min_field_width;
	if (IS_NEG_FIELD(info.options))
		count += ft_putwchar_fd(wc, g_printf_fd);
	while (padding-- > info.len)
		count += ft_putwchar_fd(IS_ZERO(info.options) ? '0' : ' ', PF_FD);
	if (!(IS_NEG_FIELD(info.options)))
		count += ft_putwchar_fd(wc, PF_FD);
	return (count);
}

int					pf_print_skinny_char(t_pf_info info, int c)
{
	int		count;
	int		padding;

	count = 0;
	info.len = 1;
	padding = info.min_field_width;
	if (IS_NEG_FIELD(info.options))
		count += ft_putchar_fd_2(c, g_printf_fd);
	while (padding-- > info.len)
		count += ft_putchar_fd_2(IS_ZERO(info.options) ? '0' : ' ', PF_FD);
	if (!(IS_NEG_FIELD(info.options)))
		count += ft_putchar_fd_2(c, PF_FD);
	return (count);
}

int					pf_print_char(t_pf_info info, va_list args_list)
{
	if (IS_LONG(info.mod) || ft_isin('C', info.str))
		return (pf_print_wide_char(info, va_arg(args_list, wchar_t)));
	else
		return (pf_print_skinny_char(info, va_arg(args_list, int)));
}

int					pf_print_wchar_str(t_pf_info info, va_list args_list)
{
	wchar_t	*str;
	int		count;
	size_t	padding;

	count = 0;
	str = va_arg(args_list, wchar_t *);
	if (str == NULL)
		return (write(PF_FD, "(null)", 6));
	count = 0;
	info.len_str = str ? ft_wstrlen(str) : 6;
	if (info.prec_spec && (size_t)PREC < info.len_str)
		info.len_str = (size_t)PREC;
	padding = MFW;
	if (IS_NEG_FIELD(info.options))
		count += ft_putnwstr_fd(str, info.prec_spec\
								? info.precision : info.len_str, g_printf_fd);
	while (padding-- > info.len_str)
		count += ft_putchar_fd_2(IS_ZERO(info.options) ? '0' : ' ', PF_FD);
	if (!(IS_NEG_FIELD(info.options)))
		count += ft_putnwstr_fd(str, info.prec_spec\
								? info.precision : info.len_str, g_printf_fd);
	return (count);
}

int					pf_print_string(t_pf_info info, va_list args_list)
{
	char	*str;
	int		count;
	size_t	padding;

	if (IS_LONG(info.mod) || ft_isin('S', info.str))
		return (pf_print_wchar_str(info, args_list));
	str = va_arg(args_list, char *);
	if (str == NULL)
		str = "(null)";
	count = 0;
	info.len_str = ft_strlen(str);
	if (info.prec_spec && (size_t)PREC < info.len_str)
		info.len_str = (size_t)PREC;
	padding = MFW;
	if (IS_NEG_FIELD(info.options))
		count += ft_putnstr_fd(str, info.prec_spec\
								? info.precision : info.len_str, g_printf_fd);
	while (padding-- > info.len_str)
		count += ft_putchar_fd_2(IS_ZERO(info.options) ? '0' : ' ', PF_FD);
	if (!(IS_NEG_FIELD(info.options)))
		count += ft_putnstr_fd(str, info.prec_spec\
								? info.precision : info.len_str, g_printf_fd);
	return (count);
}
