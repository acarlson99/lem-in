/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: callen <callen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:53:25 by callen            #+#    #+#             */
/*   Updated: 2019/02/11 19:25:33 by callen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Uses original graph and residual graph and finds which paths were taken
*/

#define M (it.m)
#define I (it.i)
#define J (it.j)
#define V (it.v)
#define X (it.x)
#define Y (it.y)
#define RNM rooms[V]->name
#define LSTADD ft_lstadd_tail(&l[J],ft_lstnew(RNM,ft_strlen(RNM)+1));
#define RGRP {rgraph[I][V]=1;rgraph[V][I]=1;V=I;break;}
#define BEP LSTADD;J++;p2=l[J-1];flag=0;
#define CND !rgraph[V][I] && rgraph[I][V]
#define HEC if(V!=S)LSTADD;I=-1;while(++I<size)DO_ALL(CND,RGRP);
#define LON flag=1;ft_lstdel(&l[M],free_);l[M]=l[J-1];l[--J]=0;
#define NOL flag=1;ft_lstdel(&l[J-1],free_);l[--J]=0;
#define IFLEN if(ft_lstlen(p1)>ft_lstlen(p2)){LON;}else{NOL;}
#define CNTNTCMP (ft_strcmp(p1->content,p2->content))
#define CNTNT if(!CNTNTCMP){IFLEN}if(flag)break;p1=p1->next;
#define L0OP p1=l[M];while(p1&&p1->next){CNTNT;}if(flag)break;
#define L00PS M=-1;while(++M<J-1){L0OP}if(flag)break;p2=p2->next;
#define LO0P V=S;while(V!=T){HEC;}BEP;
#define DECLARE_MY_LAD J=0;Y=-1;

t_list		**find_path(int **conns, int **rgraph, size_t size, t_room **rooms)
{
	t_iter		it;
	t_list		**l;
	t_list		*p1;
	t_list		*p2;
	int			flag;

	DO_IF((!(l = ft_memalloc(size * sizeof(t_list *)))), panic(MALLOC_ERR));
	DECLARE_MY_LAD;
	while (++Y < size)
	{
		X = -1;
		while (++X < size)
		{
			if (conns[Y][X] && !rgraph[Y][X])
			{
				LO0P;
				while (p2 && p2->next)
				{
					L00PS;
				}
			}
		}
	}
	l[J] = NULL;
	return (l);
}

/*
** I'm sorry.
*/

#undef M
#undef I
#undef J
#undef V
#undef X
#undef Y
#undef RNM
#undef LSTADD
#undef RGRP
#undef BEP
#undef CND
#undef HEC
#undef LON
#undef NOL
#undef IFLEN
#undef CNTNTCMP
#undef CNTNT
#undef L0OP
#undef L00PS
#undef LO0P
#undef DECLARE_MY_LAD
