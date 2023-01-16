/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:21:28 by odessein          #+#    #+#             */
/*   Updated: 2023/01/16 14:58:04 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

float	get_specular(t_vect light_vec, t_disp_point intersec, t_objects *objs)
{
	int		shy;
	float	ks;
	t_vect	view_line;
	t_vect	normal;
	t_vect	reflected;

	ft_memset(&normal, 0, sizeof(normal));
	if (intersec.type == SP)
		normal = normalize_vector(get_normal_vect_sp(intersec, objs));
	else if (intersec.type == PL)
		normal = normalize_vector(get_normal_vect_pl(intersec, objs));
	else if (intersec.type == CY)
		normal = normalize_vector(get_normal_vect_cy(intersec, objs));
	else if (intersec.type == DI)
		normal = normalize_vector(get_normal_vect_di(intersec, objs));
	else
		return (1);
	//Same for the specular reflection of object we can change between object to personalize more 
	ks = 0.6;
	shy = 15;
	reflected = normalize_vector(2 * (scalar_product(normal,
					normalize_vector(light_vec)) * normal)
			- normalize_vector(light_vec));
	view_line = normalize_vector(create_vector(intersec.intersec_point,
				objs->cam->position));
	return (ks * pow(fmax(scalar_product(view_line, reflected), 0), shy));
}

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
	t = (a * (objs->cy[intersec.obj_id].position.x - intersec.intersec_point.x)
			+ b * (objs->cy[intersec.obj_id].position.y
				- intersec.intersec_point.y)
			+ c * (objs->cy[intersec.obj_id].position.z
				- intersec.intersec_point.z)) / (a * a + b * b + c * c);
	normal_cy[0] = intersec.intersec_point.x - a * t
		+ objs->cy[intersec.obj_id].position.x;
	normal_cy[1] = intersec.intersec_point.y - b * t
		+ objs->cy[intersec.obj_id].position.y;
	normal_cy[2] = intersec.intersec_point.z - c * t
		+ objs->cy[intersec.obj_id].position.z;
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
