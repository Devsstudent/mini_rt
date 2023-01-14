/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:21:28 by odessein          #+#    #+#             */
/*   Updated: 2023/01/14 22:55:48 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

/*t_vect	get_normal_vect_cy(t_disp_point intersec, t_objects *objs)
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


t_vect	get_normal_vect_cy(t_disp_point intersec, t_objects *objs)
>>>>>>> a4cff9912e690bd7badeb77fd5ac3ac62e19d519
{
	t_vect		normal_cy;
	float		t;
	int			a;
	int			b;
	int			c;

	a = objs->cy[intersec.obj_id].vec_direction[0];
	b = objs->cy[intersec.obj_id].vec_direction[1];
	c = objs->cy[intersec.obj_id].vec_direction[2];
	//Check 0
	t = (a * (objs->cy[intersec.obj_id].position.x- intersec.intersec_point.x) + b * (objs->cy[intersec.obj_id].position.y- intersec.intersec_point.y) + c * (objs->cy[intersec.obj_id].position.z - intersec.intersec_point.z)x) / (pow(a, 2) + pow(b, 2) + pow(c , 2));
	normal_cy[0] = a * t + objs->cy[intersec.obj_id].x;
	normal_cy[1] = b * t + objs->cy[intersec.obj_id].y;
	normal_cy[2] = c * t + objs->cy[intersec.obj_id].z;
	return (normal_cy);
}*/

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
