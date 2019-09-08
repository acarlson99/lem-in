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
typedef struct s_flag	t_flag;
typedef struct s_iter	t_iter;
typedef struct s_listaroni	t_lont;
typedef struct s_update_array_args	t_upar;
typedef struct s_ant_loop_vars	t_alvs;
struct		s_ant_loop_vars
{
	t_list		**slv_list;
	t_list		*slv_all_ants;
	size_t		*slv_lens;
	size_t		idx;
	size_t		slv_len_tmp;
	size_t		slv_len_min;
	size_t		slv_path_len_sum;
	size_t		moves;
	t_lem		*info;
	t_list		**list;
	t_antq		*all_ants;
	size_t		len_min;
	size_t		num_paths;
	size_t		path_len_sum;
	size_t		*lens;
	size_t		i;
	size_t		len_tmp;
	size_t		n;
	size_t		len_max;
	size_t		abs_max;
	size_t		total_paths;
	char		*tpn;
	char		*lpn;
	int			*valid_arr;
	int			flag;
	unsigned	j;
};
struct		s_update_array_args
{
	t_list		**list;
	size_t		*lens;
	int			*valid_arr;
	size_t		*nump;
	size_t		*plensum;
	size_t		totalp;
	size_t		np;
	size_t		lmin;
	unsigned	ants_left;
};
struct		s_listaroni
{
	t_list	*p0;
	t_list	*p1;
	t_list	*p2;
};
struct		s_iter
{
	size_t		x;
	size_t		y;
	size_t		v;
	size_t		i;
	size_t		j;
	size_t		m;
	size_t		idx;
	size_t		u;
	size_t		vv;
};

struct		s_flag
{
	int		mf;
	int		pf;
	int		fg;
};
struct		s_antq
{
	t_ant		*head;
	t_ant		*tail;
};

struct		s_ant
{
	t_list			*room;
	t_ant			*next;
	int				num;
};

struct		s_line
{
	char			*line;
	struct s_line	*next;
};

struct		s_room
{
	char		*name;
	unsigned	visited;
	int			x;
	int			y;
	char		full;
	char		start_end;
};

struct		s_lem
{
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
	size_t		num_rooms;
	size_t		nr;
	size_t		i;
	size_t		j;
	size_t		k;
	size_t		u;
	size_t		v;
	size_t		x;
	size_t		y;
	unsigned	num_ants;
	int			flag;

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

t_list		**find_path(int **conns, int **rgraph, size_t size, t_room **rooms);
void		solve(t_lem *info);

/*
** Solve_utils
*/

int			is_path(int **graph, int *parent, size_t size);
void		path_helper(t_queue *q, int vu[2], int *parent, int *visited);
int			**copy_graph(int **graph, size_t size);

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
