/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:11:34 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/28 16:45:44 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns 1 if c is in str.  0 if it is not.  Does not return 1 for \0
*/

int		ft_isin(char c, const char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (*str == c);
}
