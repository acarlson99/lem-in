/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 14:03:45 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/08 20:38:55 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

/*
** START == 69 == 'E'
** END == -92
** R(a): macro for typecasting t_list->content from void* to t_room*
** adjacency list struct as array of linked lists
*/

# define START		((char)69)
# define END		((char)420)
# define R(a)		((t_room*)a->content)

# define MALLOC_ERR	(1)
# define ROOM_ERR	(2)
# define START_ERR	(4)
# define END_ERR	(8)
# define CONN_ERR	(16)
# define PARS_ERR	(32)
# define READ_ERR	(64)

typedef struct s_room	t_room;
typedef struct s_lem	t_lem;
typedef struct s_lst	t_lst;

/*
** sizeof(t_list) = 40 bytes
*/

struct		s_lst
{
	t_room		*r;
	t_lst		*next;
};

/*
** sizeof(t_room) = 32 bytes
*/

struct		s_room
{
	char		full;
	char		visited;
	char		start_end;
	int			x;
	int			y;
	char		*name;
	t_list		*conns;
};

/*
** sizeof(t_lem) = 32 bytes
*/

struct		s_lem
{
	unsigned	num_rooms;
	unsigned	num_ants;
	t_list		*lines;
	t_list		*rooms;
	t_room		*start;
	t_room		*end;
};

t_room		*make_room(char *name, int x, int y, char start_end);
void		free_room(t_room **room);
void		init_lem(t_lem **info);
void		add_to_struct(t_lem *info);
void		parse_input(t_lem *info);
void		validate_conn(char *line);
int			validate_room(char *line);
void		panic(int code);
void		free_str_tab(char ***tab);
void		print_input(t_lem *info);
void		check_struct(t_lem *info);
t_list		*ft_lstnew_nocpy(void *content, size_t content_size);
void		print_rooms(t_lem *info);
void		print_conns(t_lem *info);
unsigned	ft_lstlen(t_list *l);

#endif
