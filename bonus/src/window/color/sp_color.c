/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:20:13 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 13:20:57 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

void	sphere_color(t_vect dist, t_disp_point disp_p, t_rgb white, t_rgb black, t_rgb *color, t_objects *objs)
{
	float	x, z;
	t_vect	ve;
	float	cos_teta;
	float	cos_phi;
	t_sphere	sp;

	sp = objs->sp[disp_p.obj_id];
	x = scalar_product(dist, sp.vec_width);
	z = scalar_product(dist, sp.vec_depth);
	ve = x * sp.vec_width + z * sp.vec_depth;
	cos_teta = scalar_product(ve, sp.vec_width) / ((norm_of_vector(ve)));
	float	teta = acos(cos_teta) * 180 / M_PI;
	if (z < 0)
		teta = 360 - teta;
	cos_phi = scalar_product(dist, sp.vec_height) / norm_of_vector(dist);
	float	phi = acos(cos_phi) * 180 / M_PI;
	if (((int)teta / 30) % 2)
	{
		if ((int)phi / 30 % 2)
			*color = white;
		else
			*color = black;
	}
	else
	{
		if ((int)phi / 30 % 2)
			*color = black;
		else
			*color = white;
	}
}


