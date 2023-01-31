/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:20:13 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 21:30:40 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static void	fill_color(t_rgb *color, float teta, float phi)
{
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

static void	sp_checkerboard(t_disp_point disp_p, t_rgb *color, t_sphere sp)
{
	float	z;
	t_vect	ve;
	float	teta;
	float	phi;
	t_vect	dist;

	dist = create_vector(sp.position, disp_p.intersec_point);
	z = scalar_product(dist, sp.vec_depth);
	ve = scalar_product(dist, sp.vec_width) * sp.vec_width + z * sp.vec_depth;
	teta = acos(scalar_product(ve, sp.vec_width)
			/ ((norm_of_vector(ve)))) * 180 / M_PI;
	if (z < 0)
		teta = 360 - teta;
	phi = acos(scalar_product(dist, sp.vec_height)
			/ norm_of_vector(dist)) * 180 / M_PI;
	fill_color(color, teta, phi);
}

static void	sp_texture(t_rgb *color, t_sphere sp, t_disp_point disp_p)
{
	t_vect	ve;
	float	z;
	float	teta;
	float	phi;
	t_vect	dist;

	dist = create_vector(sp.position, disp_p.intersec_point);
	z = scalar_product(dist, sp.vec_depth);
	ve = scalar_product(dist, sp.vec_width) * sp.vec_width + z * sp.vec_depth;
	teta = acos(scalar_product(ve, sp.vec_width)
			/ (norm_of_vector(ve))) * 180 / M_PI;
	if (z < 0)
		teta = 360 - teta;
	phi = acos(scalar_product(dist, sp.vec_height)
			/ norm_of_vector(dist)) * 180 / M_PI;
	z = (phi * sp.tex.height) / 180;
	*color = get_texture_color(((360 - teta) * sp.tex.width) / 360, z, sp.tex);
}

void	sphere_color(t_disp_point disp_p, t_rgb *color, t_objects *objs)
{
	if (disp_p.tex.tex == DAM)
		sp_checkerboard(disp_p, color, objs->sp[disp_p.obj_id]);
	else if (disp_p.tex.tex == TEX)
		sp_texture(color, objs->sp[disp_p.obj_id], disp_p);
	else
		*color = disp_p.color;
}
