# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   get_normal_vector.c                                :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: odessein <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 16:38:34 by odessein          #+#    #+#              #
/*   Updated: 2023/01/13 17:58:07 by odessein         ###   ########.fr       */
#                                                                              #
# **************************************************************************** #
#include "window.h"

t_vect	get_normal_vect_cy(t_disp_point intersec, t_objects *objs)
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
}

t_vect
t_vect	get_normal_vect_sp(t_disp_point intersec, t_objects *objs)
{
	t_vect	normal_sp;

	normal_sp = create_vector(objs->sp[intersec->obj_id].position, intersec.intersec_point);
	return (normal_sp);
}
