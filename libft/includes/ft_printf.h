/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:41:41 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/23 14:33:21 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define RECOGNIZED "sSpdDioOuUxXcCb%hljzL0123456789.#- +"
# define CONVERSIONS "sSpdDioOuUxXcCb%"
# define CONVS CONVERSIONS
# define MODIFIERS "hljz"
# define MODS MODIFIERS

# define PF_FD g_printf_fd

# include <stdarg.h>
# include "libft.h"

# define MFW info.min_field_width
# define PREC info.precision

# define ALT 1
# define ZERO 2
# define NEG_FIELD 4
# define SPACE 8
# define SIGNED 16

# define PRINTF_CHAR 1
# define PRINTF_SHORT 2
# define PRINTF_LONG 4
# define PRINTF_LONGLONG 8
# define PRINTF_INTMAX_T 16
# define PRINTF_SIZE_T 32

# define IS_ALT(n) ((ALT & n) > 0)
# define IS_ZERO(n) ((ZERO & n) > 0)
# define IS_NEG_FIELD(n) ((NEG_FIELD & n) > 0)
# define IS_SPACE(n) ((SPACE & n) > 0)
# define IS_SIGNED(n) ((SIGNED & n) > 0)

# define IS_CHAR(n) ((PRINTF_CHAR & n) > 0)
# define IS_SHORT(n) ((PRINTF_SHORT & n) > 0)
# define IS_LONG(n) ((PRINTF_LONG & n) > 0)
# define IS_LONGLONG(n) ((PRINTF_LONGLONG & n) > 0)
# define IS_INTMAX_T(n) ((PRINTF_INTMAX_T & n) > 0)
# define IS_SIZE_T(n) ((PRINTF_SIZE_T & n) > 0)

extern int			g_printf_fd;

/*
** str: the snippet of the string we want to format
** options: #0 -+
** mod: lllhhhjz
** min_field_width: %4d
** precision: %.4d
** prec_spec: whether or not precision has been specified
** len: number of characters to be printed
*/

typedef struct		s_pf_info
{
	char		*str;
	int			options;
	int			mod;
	int			min_field_width;
	int			precision;
	int			prec_spec;
	int			len;
	size_t		len_str;
}					t_pf_info;

int					ft_printf(char *fmt, ...);
int					ft_dprintf(int fd, char *fmt, ...);
int					ft_vdprintf(int fd, const char *format, va_list args_list);

int					pf_dispatch_func(const char *str,\
									int *count, va_list args_list);

int					pf_find_colors(const char *str, int *count);

int					pf_get_min_field(char *str);
size_t				pf_extract_va_arg_signed(t_pf_info info, va_list args_list);
size_t				pf_extract_va_arg_unsigned(t_pf_info info,\
													va_list args_list);

int					pf_find_modifier(char c, const char *str, int n);
int					pf_find_options(char c, const char *str);
int					pf_get_precision(t_pf_info info);
int					pf_get_min_field(char *str);

int					pf_print_min_field_width(t_pf_info info, int is_neg);
int					pf_print_zeroes(t_pf_info info);
int					pf_print_int_precision(t_pf_info info, char *str,\
												int is_neg);

int					pf_print_string(t_pf_info info, va_list args_list);
int					pf_print_pointer(t_pf_info info, va_list args_list);
int					pf_print_int(t_pf_info info, va_list args_list);
int					pf_print_oct(t_pf_info info, va_list args_list);
int					pf_print_unsigned(t_pf_info info, va_list args_list);
int					pf_print_hex(t_pf_info info, va_list args_list);
int					pf_print_char(t_pf_info info, va_list args_list);
int					pf_print_bin(t_pf_info info, va_list args_list);
int					pf_print_percent(t_pf_info info, va_list args_list);

typedef int			(*t_fun_ptr)();

#endif
