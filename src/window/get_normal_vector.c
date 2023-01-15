/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:21:28 by odessein          #+#    #+#             */
/*   Updated: 2023/01/15 21:23:34 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

float	get_specular(t_vect light_vec, t_disp_point intersec, t_objects *objs)
{
	int		shy = 15;
	float	ks;
	t_vect	normed_view_line;
	t_vect	normed_normal;
	t_vect	normed_reflected;
	float	res;

	ft_memset(&normed_normal, 0, sizeof(normed_normal));
	if (intersec.type == SP)
	{
		ks = 1;
		normed_normal = normalize_vector(get_normal_vect_sp(intersec, objs));
	}
	else if (intersec.type == PL)
	{
		ks = 1;
		normed_normal = normalize_vector(get_normal_vect_pl(intersec, objs));
	}
	else if (intersec.type == CY)
	{
		ks = 1;
		normed_normal = normalize_vector(get_normal_vect_cy(intersec, objs));
	}
	else if (intersec.type == DI)
	{
		ks = 1;
		normed_normal = normalize_vector(get_normal_vect_di(intersec, objs));
	}
	else
		return (1);
	ks = 0.3;
	normed_reflected = normalize_vector(2 * (scalar_product(normed_normal, normalize_vector(light_vec)) * normed_normal) - normalize_vector(light_vec));
	
	normed_view_line = normalize_vector(create_vector(intersec.intersec_point, objs->cam->position));
	res = ks * pow(fmax(scalar_product(normed_view_line, normed_reflected), 0), shy);
	return (res);
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

	//Check 0
	t = (a * (objs->cy[intersec.obj_id].position.x- intersec.intersec_point.x) + b * (objs->cy[intersec.obj_id].position.y- intersec.intersec_point.y) + c * (objs->cy[intersec.obj_id].position.z - intersec.intersec_point.z)) / (a * a + b * b + c * c);
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
