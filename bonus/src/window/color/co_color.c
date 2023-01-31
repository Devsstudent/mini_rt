/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:23:59 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 19:28:29 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static float get_teta(t_vect dist, t_cone co, t_disp_point disp_p, t_vect *len)
{
	float	teta;
	float	y, z;
	t_vect	buff;
	t_xyz	b;

	z = scalar_product(dist, -co.vec_depth);
	y = scalar_product(dist, -co.vec_height);
	buff = y * -co.vec_height;
	b.x = buff[0] +	co.position.x;
	b.y = buff[1] +	co.position.y;
	b.z = buff[2] +	co.position.z;
	*len = (create_vector(b, disp_p.intersec_point));
	teta = acos(scalar_product(*len, co.vec_width) / norm_of_vector(*len)) * 180 / M_PI;
	if (z < 0)
		teta = 360 - teta;
	return (teta);
}

static void	co_checkerboard(t_rgb *color, t_disp_point disp_p, t_cone co)
{
	t_vect	dist;
	float	teta;
	t_vect	len;

	dist = create_vector(co.position, disp_p.intersec_point);
	teta = get_teta(dist, co, disp_p, &len);
	if ((int) (teta / 30) % 2 == 0)
	{
		if ((int) norm_of_vector(dist) / (int) (30 * M_PI / 180 * co.radius) % 2 == 0)
			*color = rgb_fill(0, 0, 0);
		else
			*color = rgb_fill(255, 255, 255);
	}
	else
	{
		if ((int) norm_of_vector(dist) / (int) (30 * M_PI / 180 * co.radius) % 2 == 0)
			*color = rgb_fill(255, 255, 255);
		else
			*color = rgb_fill(0, 0, 0);
	}
}

static void co_texture(t_rgb *color, t_disp_point disp_p, t_cone co)
{
	float	teta;
	float	height_max;
	t_vect	dist;
	t_vect	len;
	float	y;

	dist = create_vector(co.position, disp_p.intersec_point);
	height_max = sqrt((co.radius * co.radius) + (co.height * co.height));
	teta = get_teta(dist, co, disp_p, &len);
	if (disp_p.type == CO_DI)
		height_max = height_max - norm_of_vector(len);
	else
		height_max = norm_of_vector(dist);
	y = (int) (height_max * co.tex.height) / ((int) (co.radius * co.height));
	*color = get_texture_color((teta * co.tex.width) / 360, y, co.tex);
}

void	cones_color(t_rgb *color, t_disp_point disp_p, t_objects *objs)
{
	if (disp_p.tex.tex == DAM)
		co_checkerboard(color, disp_p, objs->co[disp_p.obj_id]);
	else if (disp_p.tex.tex == TEX)
		co_texture(color, disp_p, objs->co[disp_p.obj_id]);
	else
		*color = disp_p.color;
}

