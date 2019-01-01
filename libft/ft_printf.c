/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:24:40 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/23 14:31:12 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

int		g_printf_fd = 1;

int		ft_vdprintf(int fd, const char *format, va_list args_list)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	g_printf_fd = fd;
	while (format[i])
	{
		if (format[i] == '%')
			i += pf_dispatch_func(&(format[i + 1]), &count, args_list);
		else if (format[i] == '{')
			i += pf_find_colors(&(format[i + 1]), &count);
		else
			count += ft_putchar_fd_2(format[i], fd);
		i++;
	}
	va_end(args_list);
	return (count);
}

int		ft_printf(char *fmt, ...)
{
	va_list args;
	int		n;

	va_start(args, fmt);
	n = ft_vdprintf(1, fmt, args);
	va_end(args);
	return (n);
}

int		ft_dprintf(int fd, char *fmt, ...)
{
	va_list args;
	int		n;

	va_start(args, fmt);
	n = ft_vdprintf(fd, fmt, args);
	va_end(args);
	return (n);
}
