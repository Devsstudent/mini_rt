/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:23:59 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 13:24:10 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

void	cones_color(t_vect dist, t_rgb *color, t_rgb white, t_rgb black, t_disp_point disp_p, t_objects *objs)
{
	float	y, z;
	t_vect	len;
	t_vect	buff;
	float	teta;
	t_xyz	b;

	z = scalar_product(dist, -objs->co[disp_p.obj_id].vec_depth);
	y = scalar_product(dist, -objs->co[disp_p.obj_id].vec_height);
	buff = y * -objs->co[disp_p.obj_id].vec_height;
	b.x = buff[0] + objs->co[disp_p.obj_id].position.x;
	b.y = buff[1] + objs->co[disp_p.obj_id].position.y;
	b.z = buff[2] + objs->co[disp_p.obj_id].position.z;
	len = (create_vector(b, disp_p.intersec_point));
	teta = acos(scalar_product(len, objs->co[disp_p.obj_id].vec_width) / norm_of_vector(len)) * 180 / M_PI;
	if (z < 0)
		teta = 360 - teta;
	if ((int) (teta / 10) % 2 == 0)
	{
		if ((int) norm_of_vector(dist) % 2 == 0)
			*color = black;
		else
			*color = white;
	}
	else
	{
		if ((int) norm_of_vector(dist) % 2 == 0)
			*color = white;
		else
			*color = black;
	}
}
