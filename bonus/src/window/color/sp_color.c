/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:20:13 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 15:31:18 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static void	sp_checkerboard(t_disp_point disp_p, t_rgb *color, t_objects *objs)
{
	float	x, z;
	t_vect	ve;
	float	cos_teta;
	float	cos_phi;
	t_sphere	sp;
	t_vect		dist;

	dist = create_vector(objs->sp[disp_p.obj_id].position, disp_p.intersec_point);
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
			*color = rgb_fill(255, 255, 255);
		else
			*color = rgb_fill(0, 0, 0);
	}
	else
	{
		if ((int)phi / 30 % 2)
			*color = rgb_fill(0, 0, 0);
		else
			*color = rgb_fill(255, 255, 255);
	}
}

static void	sp_texture(t_rgb *color, t_objects *objs,  t_disp_point disp_p)
{
	float	x, z;
	t_vect	ve;
	float	cos_teta;
	float	cos_phi;
	t_sphere	sp;
	t_vect		dist;

	dist = create_vector(objs->sp[disp_p.obj_id].position, disp_p.intersec_point);
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
	x = teta * sp.tex.width / 360;
	z = phi * sp.tex.height / 180;
	*color = get_texture_color(x, z, sp.tex);
}

void	sphere_color(t_disp_point disp_p, t_rgb *color, t_objects *objs)
{
	if (disp_p.tex.tex == DAM)
		sp_checkerboard(disp_p, color, objs);
	else if (disp_p.tex.tex == TEX)
		sp_texture(color, objs, disp_p);
	else
		*color = disp_p.color;
}

