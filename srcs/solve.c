/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:40:56 by acarlson          #+#    #+#             */
/*   Updated: 2019/04/10 16:52:51 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define M_ERR MALLOC_ERR
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

#define ALST al->slv_list
#define ALMIN al->slv_len_min
#define ALMAX al->len_max
#define FS00 ("%sLongest absolute path: %zu%s\n")
#define FS01 ("%sLongest path taken: len(%zu) name(%s)%s\n")
#define FS02 ("%sLen_min: %zu%s\n")
#define FS03 ("%sNumber of paths: %zu%s\n")
#define FS04 ("%sTotal moves: %zu%s\n")
#define NEWDBGP00 ft_dprintf(2,FS00,FG(GRN),al->abs_max,FG(DFT));
#define NEWDBGP01 NEWDBGP00; ft_dprintf(2,FS01,FG(GRN),ALMAX,al->lpn,FG(DFT));
#define NEWDBGP02 NEWDBGP01; ft_dprintf(2,FS02,FG(GRN),ALMIN,FG(DFT));
#define NEWDBGP03 NEWDBGP02; al->i=-1;while(ALST[++al->i]);
#define NEWDBGP04 NEWDBGP03; ft_dprintf(2,FS03,FG(GRN),al->i,FG(DFT));
#define NEWDBGP05 NEWDBGP04; ft_dprintf(2,FS04,FG(GRN),al->moves,FG(DFT));
#define NEWDBGPRNT NEWDBGP05;
#define ALI00 al->num_paths=al->idx;
#define ALI01 ALI00; al->lens=al->slv_lens;al->total_paths = al->num_paths;
#define ALI02 ALI01; al->n=1;al->len_max=0;al->abs_max=0;al->flag=0;al->j=-1;
#define ALI03 ALI02; al->valid_arr=ft_memalloc(sizeof(int)*al->num_paths+1);
#define ALI04 ALI03; while(++al->j<al->num_paths){al->valid_arr[al->j]=1;}
#define ALI05 ALI04; al->path_len_sum=al->slv_path_len_sum;
#define ANTLINIT ALI05;
#define ALUPI00 up.list=ALST;up.lens=al->lens;up.valid_arr=al->valid_arr;
#define ALUPI01 ALUPI00; up.ants_left=info->num_ants-al->n+1;up.lmin=ALMIN;
#define ALUPI02 ALUPI01; up.totalp=al->total_paths;up.nump=&al->num_paths;
#define ALUPI03 ALUPI02; up.plensum=&al->path_len_sum;update_array(&up);
#define ALUPI04 ALUPI03; al->len_tmp=ft_lstlen(ALST[al->i]);
#define ALUPI05 ALUPI04; al->tpn=ALST[al->i]->content;
#define ALUPI06 ALUPI05; if(al->len_tmp>al->abs_max){al->abs_max=al->len_tmp;}
#define ALUPI07 ALUPI06; CONT_IF(!al->valid_arr[al->i]&&++al->i);
#define ALUPARR ALUPI07;
#define ALMCHK00 al->len_max=al->len_tmp;al->lpn=al->tpn;
#define ALMCHK01 if(ALMAX<al->len_tmp){ALMCHK00;}
#define ALMCHK02 ALMCHK01;add_ant(al->all_ants,ALST[al->i],al->n);al->n++;
#define ALMAXCHK ALMCHK02;

void		ant_loop(t_alvs *al, t_lem *info)
{
	t_upar		up;

	ANTLINIT;
	while (1)
	{
		al->i = 0;
		while (ALST[al->i] && !al->flag && al->n <= info->num_ants)
		{
			ALUPARR;
			if (al->n <= info->num_ants)
			{
				ALMAXCHK;
			}
			else
				al->flag = 1;
			al->i++;
		}
		if (!move_ants(al->all_ants))
		{
			NEWDBGPRNT;
			exit(0);
		}
		al->moves++;
		ft_putchar('\n');
	}
}

#define ALBI00 albo.slv_list=info->l2;albo.all_ants=info->all_ants;
#define ALBI01 ALBI00; albo.slv_len_min=FT_SIZE_T_MAX;albo.idx=0;
#define ALBI02 ALBI01; albo.path_len_sum=0;
#define ALBINIT ALBI02;

void		solve(t_lem *info)
{
	int			max_flow;
	t_alvs		albo;

	info->rgraph = copy_graph(info->conns, info->num_rooms);
	info->list = ft_memalloc(sizeof(t_list *) * info->num_rooms);
	max_flow = fordfulkn(info->rooms, info->rgraph, info->num_rooms,
		info->list);
	ft_dprintf(2, "%sMax flow: %d%s\n", FG(GRN), max_flow, FG(DFT));
	if (!(info->all_ants = (t_antq *)ft_memalloc(sizeof(t_antq))))
		panic(MALLOC_ERR);
	info->l2 = find_path(info->conns, info->rgraph, info->num_rooms,
		info->rooms);
	ALBINIT;
	albo.slv_lens = ft_memalloc(sizeof(size_t) * info->num_rooms);
	while (albo.slv_list[albo.idx])
	{
		albo.slv_len_tmp = ft_lstlen(albo.slv_list[albo.idx]);
		albo.slv_lens[albo.idx] = albo.slv_len_tmp;
		albo.slv_path_len_sum += albo.slv_len_tmp;
		if (albo.slv_len_tmp < albo.slv_len_min)
			albo.slv_len_min = albo.slv_len_tmp;
		albo.idx++;
	}
	albo.moves = 0;
	ant_loop(&albo, info);
}

#undef M_ERR
#undef U
#undef VV
#undef IDX
#undef I
#undef MF
#undef PF
#undef FL
#undef P0
#undef P1
#undef P2
#undef RMPNM
#undef RMLNM
#undef RMFNM
#undef LORCND
#undef LORDOA
#undef LORDOB
#undef LORDO
#undef LORB
#undef SMOL
#undef LOPL
#undef LADDCND
#undef LADD1
#undef FLDO0
#undef LADDP0
#undef LADD0
#undef FLPVA
#undef FLOOP
#undef FLDO1
#undef CONT_IF
#undef UPLST
#undef UPNMP
#undef UPPLS
#undef UPLNS
#undef UPVAR
#undef UPALF
#undef BIGCD
#undef ALST
#undef ALMIN
#undef ALMAX
#undef FS00
#undef FS01
#undef FS02
#undef FS03
#undef FS04
#undef NEWDBGP00
#undef NEWDBGP01
#undef NEWDBGP02
#undef NEWDBGP03
#undef NEWDBGP04
#undef NEWDBGP05
#undef NEWDBGPRNT
#undef ALI00
#undef ALI01
#undef ALI02
#undef ALI03
#undef ALI04
#undef ALI05
#undef ANTLINIT
#undef ALUPI00
#undef ALUPI01
#undef ALUPI02
#undef ALUPI03
#undef ALUPI04
#undef ALUPI05
#undef ALUPI06
#undef ALUPI07
#undef ALUPARR
#undef ALMCHK00
#undef ALMCHK01
#undef ALMCHK02
#undef ALMAXCHK
#undef ALBI00
#undef ALBI01
#undef ALBI02
#undef ALBINIT
