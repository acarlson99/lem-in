/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 14:03:45 by acarlson          #+#    #+#             */
/*   Updated: 2019/02/11 19:05:58 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

/*
** START == 69 == 'E'
** END == -92
*/

# define START		((char)69)
# define END		((char)420)
# define S			(0)
# define T			(size - 1)

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
typedef struct s_line	t_line;

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

struct		s_line
{
	char			*line;
	struct s_line	*next;
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
	unsigned	num_ants;
	int			flag;
	size_t		num_rooms;
	size_t		nr;
	size_t		i;
	size_t		j;
	size_t		k;
	size_t		u;
	size_t		v;
	size_t		x;
	size_t		y;
	t_antq		*all_ants;
	t_list		*p1;
	t_list		*p2;
	t_line		*lines;
	t_room		*start;
	t_room		*end;
	t_room		**rooms;
	int			**conns;
	int			**rgraph;
	t_list		**list;
	t_list		**l1;
	t_list		**l2;
};

/*
** Struct
*/

t_room		*make_room(char *name, int x, int y, char start_end);
void		free_room(t_room **room);
void		init_lem(t_lem **info);
void		check_struct(t_lem *info);
int			**malloc_conns(size_t graph_size);
void		create_rooms(t_lem *info);
void		create_conns(t_lem *info, t_line *ptr, int mode);
void		add_ant(t_antq *a, t_list *start, int n);
void		enqueue_num(t_queue *q, size_t n);
size_t		dequeue_num(t_queue *q);

/*
** Input && validation
*/

void		print_input(unsigned num_ants, t_line *ptr);
void		validate_conn(char *line);
int			validate_room(char *line);
void		parse_input(t_lem *info);
int			is_start_end(char *line);
void		add_line(t_line **list, char *line);
size_t		ft_lstlen(t_list *ptr);

/*
** Solve
**t_list		**find_path(t_lem *info);
*/

int			is_path(int **graph, int *parent, size_t size);
t_list		**find_path(int **conns, int **rgraph, size_t size, t_room **rooms);
void		solve(t_lem *info);

/*
** Other
*/

void		panic(int code);
t_list		*ft_lstnew_nocpy(void *content, size_t content_size);
void		free_str_tab(char ***tab);
void		free_(void *ptr, size_t size);

/*
**void		print_rooms(t_room **rooms, size_t size);	// TODO: remove
**void		print_conns(int **graph, size_t size);	// TODO: remove
**void		print_list(t_list *l);	// TODO: remove
*/

#endif
