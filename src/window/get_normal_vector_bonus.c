/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:21:28 by odessein          #+#    #+#             */
/*   Updated: 2023/02/06 23:02:35 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static void	fill_var_co(t_objects *objs, t_disp_point intersec,
			t_var_normal_co *var)
{
	var->xc = objs->co[intersec.obj_id].position.x;
	var->yc = objs->co[intersec.obj_id].position.y;
	var->zc = objs->co[intersec.obj_id].position.z;
	var->xp = intersec.intersec_point.x;
	var->yp = intersec.intersec_point.y;
	var->zp = intersec.intersec_point.z;
}

t_vect	get_normal_vect_co(t_disp_point intersec, t_objects *objs)
{
	t_vect			normal_co;
	t_var_normal_co	var;
	t_var_normal	_var;

	_var.a = objs->co[intersec.obj_id].vec_dir[0];
	_var.b = objs->co[intersec.obj_id].vec_dir[1];
	_var.c = objs->co[intersec.obj_id].vec_dir[2];
	fill_var_co(objs, intersec, &var);
	normal_co[0] = _var.a;
	normal_co[1] = _var.b;
	normal_co[2] = _var.c;
	if ((var.xc - var.xp) * _var.a + (var.yc - var.yp) * _var.b
		+ (var.zc - var.zp) * _var.c == 0)
		return (normal_co);
	_var.t = (-var.xp * var.xp + var.xc * var.xp - var.yp * var.yp + var.yc
			* var.yp - var.zp * var.zp + var.zp * var.zc - var.xc * (var.xc
				- var.xp) - var.yc * (var.yc - var.yp) - var.zc * (var.zc
				- var.zp)) / (_var.a * (var.xc - var.xp) + _var.b * (var.yc
				- var.yp) + _var.c * (var.zc - var.zp));
	normal_co[0] = intersec.intersec_point.x - (_var.a * _var.t + var.xc);
	normal_co[1] = intersec.intersec_point.y - (_var.b * _var.t + var.yc);
	normal_co[2] = intersec.intersec_point.z - (_var.c * _var.t + var.zc);
	return (normal_co);
}
