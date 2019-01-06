/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 19:55:50 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/05 19:55:54 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		panic(int code)
{
	if (code == MALLOC_ERR)
		ft_printf("Malloc error\n");
	else if (code == ROOM_ERR)
		ft_printf("Room error\n");
	else if (code == START_ERR)
		ft_printf("Start error\n");
	else if (code == END_ERR)
		ft_printf("End error\n");
	else if (code == CONN_ERR)
		ft_printf("Connection error\n");
	else if (code == PARS_ERR)
		ft_printf("File read error\n");
	else if (code == READ_ERR)
		ft_printf("Read error\n");
	exit(1);
}

int			main(void)
{
	t_lem		*info;

	init_lem(&info);
	parse_input(info);
	ft_printf("%d\n", info->num_ants);
	exit(0);
}
