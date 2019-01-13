/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 14:03:45 by acarlson          #+#    #+#             */
/*   Updated: 2019/01/12 19:45:56 by acarlson         ###   ########.fr       */
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
# define NOPATH_ERR	(128)
# define ANTNUM_ERR	(256)

typedef struct s_room	t_room;
typedef struct s_lem	t_lem;
typedef struct s_ant	t_ant;
typedef struct s_antq	t_antq;

struct		s_antq
{
	t_ant		*head;
	t_ant		*tail;
};

struct		s_ant
{
	int				num;
	t_list			*room;
	t_ant			*next;
};

struct		s_room
{
	char		full;
	char		start_end;
	unsigned	visited;
	int			x;
	int			y;
	char		*name;
};

struct		s_lem
{
	size_t		num_rooms;
	unsigned	num_ants;
	t_list		*lines;
	t_room		**rooms;
	t_room		*start;
	t_room		*end;
	int			**conns;
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
void		reset_visited(t_room *room);
void		solve(t_lem *info);

void		create_rooms(t_lem *info);
void		create_conns(t_lem *info, t_list *ptr);
int			is_start_end(char *line);
void		enqueue_num(t_queue *q, size_t n);
size_t		dequeue_num(t_queue *q);
int			**malloc_conns(size_t graph_size);
int			is_path(int **graph, int *parent, size_t size);

void		print_rooms(t_room **rooms, size_t size);	// TODO: remove
void		print_conns(int **graph, size_t size);	// TODO: remove

#endif
