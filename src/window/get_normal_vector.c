/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:21:28 by odessein          #+#    #+#             */
/*   Updated: 2023/01/15 22:18:04 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

/*
float	get_specular(t_vect light_vec, t_disp_point intersec, t_objects *objs,
			int i)
{
	float	specular;
	float	
	t_vect	normal;
	t_vect	reflected;
	t_vect	view_line;

	ft_memset(&normal, 0, sizeof(normal));
	if (intersec.type == SP)
		normal = get_normal_vect_sp(intersec, objs);
	else if (intersec.type == PL)
		normal = get_normal_vect_pl(intersec, objs);
	else if (intersec.type == CY)
		normal = get_normal_vect_cy(intersec, objs);
	else if (intersec.type == DI)
		normal = get_normal_vect_di(intersec, objs);
	reflected = -light_vec - 2 * (normal * (-light_vec)) * normal;
	view_line = create_vector(intersec.intersec_point, objs->c->position);
	return (objs->li[i].intensity * (view_line * reflected));
//	specular : //light intensity * (view_line * reflected)
}
*/

t_vect	get_normal_vect_cy(t_disp_point intersec, t_objects *objs)
{
	t_vect		normal_cy;
	t_xyz		xm;
	t_xyz		x0;
	t_equation	res;
	float		t;
	float		a;
	float		b;
	float		c;
	float		delta;

	xm.x = intersec.intersec_point.x;
	xm.y = intersec.intersec_point.y;
	xm.z = intersec.intersec_point.z;
	x0.x = objs->cy[intersec.obj_id].position.x;
	x0.y = objs->cy[intersec.obj_id].position.y;
	x0.z = objs->cy[intersec.obj_id].position.z;
	a = objs->cy[intersec.obj_id].vec_direction[0];
	b = objs->cy[intersec.obj_id].vec_direction[1];
	c = objs->cy[intersec.obj_id].vec_direction[2];
	res.x_pow_two = objs->cy[intersec.obj_id].abc_2[0]
		+ objs->cy[intersec.obj_id].abc_2[1]
		+ objs->cy[intersec.obj_id].abc_2[2];
	res.x_pow_one = 2 * a * (-xm.x + x0.x) + 2 * b * (-xm.y + x0.y) + 2 * c * (-xm.z + x0.z);
	res.c = - xm.x * xm.x - xm.y * xm.y - xm.z * xm.z - x0.x * x0.x - x0.y * x0.y - x0.z * x0.z + 2 * xm.x * x0.x + 2 * xm.y * x0.y + 2 * xm.z * x0.z +
		objs->cy[intersec.obj_id].radius_2;
	delta = res.x_pow_one * res.x_pow_one - 4 * res.x_pow_two * res.c;
	//Check 0
	
	t = (a * (intersec.intersec_point.x - objs->cy[intersec.obj_id].position.x) + b * (intersec.intersec_point.y - objs->cy[intersec.obj_id].position.y) + c * (intersec.intersec_point.z - objs->cy[intersec.obj_id].position.z)) / (a * a + b * b + c * c);
	t = 
	normal_cy[0] = intersec.intersec_point.x - a * t + objs->cy[intersec.obj_id].position.x;
	normal_cy[1] = intersec.intersec_point.y - b * t + objs->cy[intersec.obj_id].position.y;
	normal_cy[2] = intersec.intersec_point.z - c * t + objs->cy[intersec.obj_id].position.z;
	return (normal_cy);
}

t_vect	get_normal_vect_di(t_disp_point intersec, t_objects *objs)
{
	t_vect	normal_di;

	normal_di = objs->cy[intersec.obj_id].vec_direction;
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
