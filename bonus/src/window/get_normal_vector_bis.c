/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:31:12 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 21:32:08 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

t_vect	get_normal_vect_di(t_disp_point intersec, t_objects *objs, bool cy)
{
	t_vect	normal_di;

	if (cy)
		normal_di = objs->cy[intersec.obj_id].vec_direction;
	else
		normal_di = objs->co[intersec.obj_id].vec_dir;
	return (normal_di);
}

t_vect	get_normal_vect_sp(t_disp_point intersec, t_objects *objs)
{
	t_vect	normal_sp;

	normal_sp = create_vector(objs->sp[intersec.obj_id].position,
			intersec.intersec_point);
	return (normal_sp);
}

t_vect	get_normal_vect_pl(t_disp_point intersec, t_objects *objs)
{
	return (objs->pl[intersec.obj_id].vec_direction);
}
