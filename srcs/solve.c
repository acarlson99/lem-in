/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/02/11 14:53:32 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define M_ERR MALLOC_ERR

#ifdef U
# undef U
#endif
#ifdef VV
# undef VV
#endif
#ifdef IDX
# undef IDX
#endif
#ifdef I
# undef I
#endif
#ifdef MF
# undef MF
#endif
#ifdef PF
# undef PF
#endif
#ifdef FL
# undef FL
#endif
#ifdef P0
# undef P0
#endif
#ifdef P1
# undef P1
#endif
#ifdef P2
# undef P2
#endif
#define U (it.u)
#define VV (it.vv)
#define IDX (it.idx)
#define I (it.i)
#define MF (f.mf)
#define PF (f.pf)
#define FL (f.fg)
#define P0 (ptr.p0)
#define P1 (ptr.p1)
#define P2 (ptr.p2)
#define RMPNM (rooms[parent[VV]]->name)
#define RMLNM (rooms[size - 1]->name)
#define RMFNM (rooms[0]->name)
#define LORCND ft_strequ(P1->content,P2->content)
#define LORDOA ft_lstdel(&list[I],free_);list[I]=list[--IDX];
#define LORDOB list[IDX]=0;FL=1;break;
#define LORDO LORDOA;LORDOB;
#define LORB if(LORCND){LORDO}P1=P1->next;
#define SMOL while(P1&&P1->next){LORB;}
#define LOPL I=-1;while(++I<IDX-1){P1=list[I];SMOL;}if(FL)break;P2=P2->next;
#define LADDCND ft_strcmp(RMPNM,RMFNM)
#define LADD1 if(LADDCND)LADDP0(RMPNM);
#define FLDO0 U=parent[VV];LADD1;PF=MIN(PF,rgraph[U][VV]);VV=parent[VV];
#define LADDP0(LDX) (ft_lstadd(&P0,ft_lstnew(LDX,ft_strlen(LDX)+1)))
#define LADD0 ft_lstadd(&P0, ft_lstnew(RMLNM, ft_strlen(RMLNM) + 1));
#define FLPVA list[IDX++]=P0;P2=P0;FL=0;
#define FLOOP LADDP0(RMLNM);PF=FT_INT_MAX;VV=T;while(VV!=S){FLDO0}VV=T;FLPVA;
#define FLDO1 U=parent[VV];rgraph[U][VV]-=PF;rgraph[VV][U]+=PF;VV=parent[VV];

int			fordfulkn(t_room **rooms, int **rgraph, size_t size, t_list **list)
{
	t_iter		it;
	int			*parent;
	t_flag		f;
	t_lont		ptr;

	IDX = 0;
	MF = 0;
	DO_IF(!(parent = malloc(sizeof(int) * size)), panic(MALLOC_ERR));
	while (is_path(rgraph, parent, size))
	{
		FLOOP;
		while (P2 && P2->next)
		{
			LOPL;
		}
		P0 = NULL;
		while (VV != S)
		{
			FLDO1;
		}
		MF += PF;
	}
	free(parent);
	return (MF);
}

/*
** Make list of shortest augmenting paths
** This would be a t_list **ptr
** Null terminating string of t_list *ptrs
** Make list of ants
** Send ants down paths
**
** for n in paths:
**     send ant down path
** for a in ants:
**     move a closer to end
*/

int			move_ants(t_antq *all_ants)
{
	t_ant		*ant;
	char		a;

	ant = all_ants->head;
	a = 0;
	while (ant)
	{
		if (ant->room)
		{
			ft_printf("%sL%d-%s", (a ? " " : ""), ant->num, ant->room->content);
			ant->room = ant->room->next;
			a = 1;
		}
		ant = ant->next;
	}
	return (a);
}

#define CONT_IF(n) if(n)continue;

/*
** Holy parameters
** TODO: make this factor in multiple viable paths of multiple lengths.
** Works when only comparing two paths.
** Breaks on more than 2 paths
*/

#define UPLST (up->list)
#define UPNMP (*up->nump)
#define UPPLS (*up->plensum)
#define UPLNS (up->lens)
#define UPVAR (up->valid_arr)
#define UPALF (up->ants_left)
#define BIGCD ((UPPLS - UPLNS[i]) / (UPNMP - 1) + UPALF / (UPNMP - 1))

void		update_array(t_upar *up)
{
	size_t i;

	i = -1;
	while (UPLST[++i])
	{
		if (UPNMP == 1)
			return ;
		else if (UPVAR[i] && UPLNS[i] >= BIGCD)
		{
			UPPLS = UPPLS - UPLNS[i];
			UPLNS[i] = -1;
			UPNMP = UPNMP - 1;
			UPVAR[i] = 0;
			return (update_array(up));
		}
	}
}

#define FS01 ("%slen_max: longest path taken %zu name %s%s\n")
#define FS02 ("%slen_min %zu%s\n")
#define FS03 ("%sNumber of paths: %zu%s\n")
#define FS04 ("%sTotal moves: %zu%s\n")
#define DBGP00 ft_dprintf(2,"%slongest path %zu%s\n",FG(GRN),abs_max,FG(DFT));
#define DBGP01 DBGP00; ft_dprintf(2,FS01,FG(GRN),len_max,lpn,FG(DFT));
#define DBGP02 DBGP01; ft_dprintf(2,FS02,FG(GRN),len_min,FG(DFT));
#define DBGP03 DBGP02; i=-1;while(list[++i]);
#define DBGP04 DBGP03; ft_dprintf(2,FS03,FG(GRN),i,FG(DFT));
#define DBGP05 DBGP04; ft_dprintf(2,FS04,FG(GRN),g_moves,FG(DFT));
#define DBGPRNT DBGP05;

size_t		g_moves;

void		ant_loop(t_lem *info, t_list **list, t_antq *all_ants, size_t len_min, size_t num_paths, size_t path_len_sum, size_t *lens)
{
	size_t		i;
	size_t		len_tmp;
	size_t		n;
	t_alvs		al;
	size_t		len_max = 0;
	size_t		abs_max = 0;
	size_t		total_paths = num_paths;
	int			flag = 0;
	unsigned	j = 0;
	char		*tmp_path_name = NULL;
	char		*lpn = NULL;
	int			*valid_arr = ft_memalloc(sizeof(int) * num_paths + 1);
	t_upar		up;
	for (j = 0; j < num_paths; j++)
		valid_arr[j] = 1;

	n = 1;
	while (1)
	{
		i = 0;
		while (list[i] && !flag && n <= info->num_ants)
		{
			up.list = list;
			up.lens = lens;
			up.valid_arr = valid_arr;
			up.ants_left = info->num_ants - n + 1;
			up.totalp = total_paths;
			up.nump = &num_paths;
			up.plensum = &path_len_sum;
			up.lmin = len_min;
			update_array(&up);
			len_tmp = ft_lstlen(list[i]);
			tmp_path_name = list[i]->content;
			if (len_tmp > abs_max)
				abs_max = len_tmp;
			CONT_IF(!valid_arr[i] && ++i);	// FIXME: This line is broken. Exemplified by map_06. So we have to figure out whether it would be better for the ant to go down the suggested path or a different path
			if (n <= info->num_ants)
			{
				if (len_max < len_tmp)
				{
					len_max = len_tmp;
					lpn = tmp_path_name;
				}
				add_ant(all_ants, list[i], n);
				n++;
			}
			else
				flag = 1;
			i++;
		}
		if (!move_ants(all_ants))
		{
			DBGPRNT;
			exit(0);
		}
		g_moves++;
		ft_putchar('\n');
	}
}

/*
** The max flow for test_01 is 3, but that doesn't count the number of ants	\
** per room.  Only ants per edge.  Counting rooms as full gives a max flow of 2
*/

void		solve(t_lem *info)
{
	size_t		i[3];

	info->rgraph = copy_graph(info->conns, info->num_rooms);
	info->list = ft_memalloc(sizeof(t_list *) * info->num_rooms);
	ft_dprintf(2, "%smax flow = %d%s\n",FG(GRN),fordfulkn(info->rooms, info->rgraph, info->num_rooms, info->list),FG(DFT)); // TODO: make a better function to find all paths to take
	if (!(info->all_ants = (t_antq *)ft_memalloc(sizeof(t_antq))))
		panic(MALLOC_ERR);
	i[2] = FT_SIZE_T_MAX;
	info->l2 = find_path(info->conns, info->rgraph, info->num_rooms, info->rooms);
	i[0] = 0;

	size_t path_len_sum = 0;
	size_t *lens = ft_memalloc(sizeof(size_t) * info->num_rooms);

	while (info->l2[i[0]])
	{
		i[1] = ft_lstlen(info->l2[i[0]]);
		lens[i[0]] = i[1];
		path_len_sum += i[1];
		if (i[1] < i[2])
			i[2] = i[1];
		i[0]++;
	}
	g_moves = 0;
	ant_loop(info, info->l2, info->all_ants, i[2], i[0], path_len_sum, lens);
}
