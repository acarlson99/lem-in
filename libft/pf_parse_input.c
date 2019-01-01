/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:26:56 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/15 14:28:13 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** Dude... I know
** It finds the first '.'
** and the first digit character
** and checks to see if the number comes after the '.'
** if it does then we know it is precision
** otherwise it is the min field width
** Then if the first digit character is a '0' it moves on
** It then checks the rest of the string for another precision
*/

int					pf_get_min_field(char *str)
{
	int		n;
	char	*s2;

	RET_IF(*str == '\0', 0);
	s2 = &(str[ft_strcspn(str, ".")]);
	str = &(str[ft_strcspn(str, "0123456789")]);
	RET_IF(s2 < str, 0);
	if (*str == '0')
		return (pf_get_min_field(str + 1));
	n = ft_strspn(str, "0123456789");
	s2 = &(str[n]);
	RET_IF(s2[0] == '.', ft_atoi(str));
	RET_IF(str[n] == '\0', 0);
	n = pf_get_min_field(&(str[n + 1]));
	return (n ? n : ft_atoi(str));
}

int					pf_get_precision(t_pf_info info)
{
	size_t		n;

	n = ft_strcspn(info.str, ".");
	RET_IF(info.str[n] != '.', 0);
	return (ft_atoi(&(info.str[n + 1])));
}

static int			add_mod(char c, const char *str, int n, int mod)
{
	(void)c;
	if (str[n] == 'l')
	{
		if (IS_LONG(mod))
			return (PRINTF_LONGLONG);
		else if (mod == 0)
			return (PRINTF_LONG);
		else
			return (-1);
	}
	else if (str[n] == 'h')
	{
		if (IS_SHORT(mod))
			return (PRINTF_CHAR);
		else if (mod == 0)
			return (PRINTF_SHORT);
		else
			return (-1);
	}
	RET_IF(mod, -1);
	if (str[n] == 'j')
		return (PRINTF_INTMAX_T);
	else if (str[n] == 'z')
		return (PRINTF_SIZE_T);
	return (-1);
}

int					pf_find_modifier(char c, const char *str, int n)
{
	int		mod;

	mod = 0;
	while (n >= 0)
	{
		if (ft_isin(str[n], MODIFIERS))
			mod = add_mod(c, str, n, mod);
		n--;
	}
	return (mod);
}
