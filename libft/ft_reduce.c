/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reduce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:12:05 by acarlson          #+#    #+#             */
/*   Updated: 2018/10/22 16:46:04 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Trying to recreate python's reduce function without lambdas monkaS
** Sets start as first value of arr and sets start to f(start, arr[i])
** for every element of arr
*/

int		ft_reduce(int *arr, size_t size, int (*f)(int a, int b))
{
	int		start;
	size_t	i;

	RET_IF(size <= 0, 0);
	start = arr[0];
	i = 1;
	while (i < size)
	{
		start = f(start, arr[i]);
		i++;
	}
	return (start);
}
