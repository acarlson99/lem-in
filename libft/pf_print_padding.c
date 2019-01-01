/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:27:20 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 14:26:07 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** Weird signed vs unsigned errors for p x
*/

size_t			pf_extract_va_arg_signed(t_pf_info info, va_list args_list)
{
	if (IS_CHAR(info.mod))
		return ((char)va_arg(args_list, int));
	else if (IS_SHORT(info.mod))
		return ((short)va_arg(args_list, int));
	else if (IS_LONG(info.mod))
		return ((long)va_arg(args_list, long));
	else if (IS_LONGLONG(info.mod))
		return ((long long)va_arg(args_list, long long));
	else if (IS_INTMAX_T(info.mod))
		return ((intmax_t)va_arg(args_list, intmax_t));
	else if (IS_SIZE_T(info.mod))
		return ((size_t)va_arg(args_list, size_t));
	else
		return ((int)va_arg(args_list, int));
}

size_t			pf_extract_va_arg_unsigned(t_pf_info info, va_list args_list)
{
	if (IS_CHAR(info.mod))
		return (va_arg(args_list, unsigned int) & FT_UCHAR_MAX);
	else if (IS_SHORT(info.mod))
		return (va_arg(args_list, unsigned int) & FT_USHRT_MAX);
	else if (IS_LONG(info.mod))
		return (va_arg(args_list, unsigned long) & FT_ULONG_MAX);
	else if (IS_LONGLONG(info.mod))
		return (va_arg(args_list, unsigned long long) & FT_ULLONG_MAX);
	else if (IS_INTMAX_T(info.mod))
		return (va_arg(args_list, intmax_t) & FT_UINTMAX_MAX);
	else if (IS_SIZE_T(info.mod))
		return (va_arg(args_list, size_t) & FT_SIZE_T_MAX);
	else
		return ((unsigned int)va_arg(args_list, unsigned int));
}

/*
** Prints spaces/zeroes
*/

int				pf_print_min_field_width(t_pf_info info, int is_neg)
{
	int		count;
	int		padding;

	padding = MAX(info.min_field_width - (MAX(info.precision, info.len)), 0);
	count = 0;
	if ((is_neg || IS_SIGNED(info.options)) && IS_ZERO(info.options))
		count += ft_putchar_fd_2(is_neg ? '-' : '+', g_printf_fd);
	while (padding--)
		count += ft_putchar_fd_2(IS_ZERO(info.options)\
								&& !(info.prec_spec) ? '0' : ' ', g_printf_fd);
	return (count);
}

/*
** Prints necessary zeroes
*/

int				pf_print_zeroes(t_pf_info info)
{
	int		count;
	int		n;

	count = 0;
	n = info.precision;
	while (n-- > info.len)
		count += ft_putchar_fd_2('0', g_printf_fd);
	return (count);
}

/*
** Prints zeroes and sign for precision
*/

int				pf_print_int_precision(t_pf_info info, char *str, int is_neg)
{
	int count;

	count = 0;
	if (IS_SIGNED(info.options) && !(IS_ZERO(info.options)))
		count += ft_putchar_fd_2(is_neg ? '-' : '+', g_printf_fd);
	else
		count += is_neg && !(IS_ZERO(info.options))\
			&& ft_putchar_fd_2('-', g_printf_fd);
	count += pf_print_zeroes(info);
	count += ft_putstr_fd_2(str + is_neg, g_printf_fd);
	return (count);
}
