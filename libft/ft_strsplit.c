/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 15:02:11 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/02 17:09:26 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_strsplit(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	words;

	NULL_CHECK(!(s));
	i = -1;
	k = 0;
	words = ft_wordnum(s, c);
	NULL_CHECK(!(new = (char **)malloc((words + 1) * sizeof(*new))));
	while (++i < words)
	{
		j = 0;
		if (!(new[i] = ft_strnew(ft_wordlen(s + k, c) + 1)))
			new[i] = NULL;
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k])
			new[i][j++] = s[k++];
		new[i][j] = '\0';
	}
	new[i] = 0;
	return (new);
}
