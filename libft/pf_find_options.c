/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_find_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:26:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 13:26:52 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int			add_option(int n, char c, const char *str)
{
	if (*str == '#' && !(ft_isin(c, "puUdDic")))
		n |= ALT;
	else if (*str == '0' && !(IS_NEG_FIELD(n)) && !(ft_isin(c, "p"))\
				&& !(ISDIGIT(*(str - 1))) && *(str - 1) != '.')
		n |= ZERO;
	else if (*str == '-')
	{
		n |= NEG_FIELD;
		if (n & ZERO)
			n ^= ZERO;
	}
	else if (*str == ' ' && !(IS_SIGNED(n)) && !(ft_isin(c, "pxXuUcb")))
		n |= SPACE;
	else if (*str == '+' && !(ft_isin(c, "pxXuUcb")))
	{
		if (IS_SPACE(n))
			n ^= SPACE;
		n |= SIGNED;
	}
	return (n);
}

int					pf_find_options(char c, const char *str)
{
	int		n;

	n = 0;
	while (*str != c)
	{
		if (ft_isin(*str, "#0- +"))
			n = add_option(n, c, str);
		else if (!(ft_isin(*str, RECOGNIZED)))
			return ((ft_isin(*str, CONVS) || ft_isin(*str, MODS)) ? n : -1);
		str++;
	}
	return (n);
}
