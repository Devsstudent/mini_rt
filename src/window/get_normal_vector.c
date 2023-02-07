/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:31:12 by odessein          #+#    #+#             */
/*   Updated: 2023/02/06 23:02:17 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

t_vect	get_normal_vect_cy(t_disp_point intersec, t_objects *objs)
{
	t_vect		normal_cy;
	float		t;
	float		a;
	float		b;
	float		c;

	a = objs->cy[intersec.obj_id].vec_direction[0];
	b = objs->cy[intersec.obj_id].vec_direction[1];
	c = objs->cy[intersec.obj_id].vec_direction[2];
	if (a * a + b * b + c * c == 0)
		free_exit(objs);
	t = (a * (-objs->cy[intersec.obj_id].position.x + intersec.intersec_point.x)
			+ b * (-objs->cy[intersec.obj_id].position.y
				+ intersec.intersec_point.y)
			+ c * (-objs->cy[intersec.obj_id].position.z
				+ intersec.intersec_point.z)) / (a * a + b * b + c * c);
	normal_cy[0] = intersec.intersec_point.x - (a * t
			+ objs->cy[intersec.obj_id].position.x);
	normal_cy[1] = intersec.intersec_point.y - (b * t
			+ objs->cy[intersec.obj_id].position.y);
	normal_cy[2] = intersec.intersec_point.z - (c * t
			+ objs->cy[intersec.obj_id].position.z);
	return (normal_cy);
}

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
