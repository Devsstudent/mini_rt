/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:23:33 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 19:03:58 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static float get_teta(t_vect dist, t_cylinder cy, t_disp_point disp_p, t_xyz a)
{
	t_xyz	p;
	t_vect	width;
	float	teta;
	float	y;
	float	z;

	y = scalar_product(-cy.vec_height, dist);
	z = scalar_product(cy.vec_depth, dist);
	p.x = a.x - y * cy.vec_height[0]; 
	p.y = a.y - y * cy.vec_height[1]; 
	p.z = a.z - y * cy.vec_height[2];
	width = create_vector(p, disp_p.intersec_point);
	teta = acos(scalar_product(width, cy.vec_width) / norm_of_vector(width))
		* 180 / M_PI;
	if (z < 0)
		teta = 360 - teta;
	return (teta);
}

static float get_len_disc(t_vect dist, t_xyz a, t_cylinder cy, t_disp_point disp_p)
{
	t_xyz	point;
	float	len;
	float	y;

	y = scalar_product(-cy.vec_height, dist);
	if (y > 0.1)
		len = norm_of_vector(dist);
	else
	{
		point.x = a.x - 2 * cy.vec_height[0];
		point.y = a.y - 2 * cy.vec_height[1];
		point.z = a.z - 2 * cy.vec_height[2];
		len = norm_of_vector(create_vector(disp_p.intersec_point, point));
	}
	return (len);
}

static void	cy_checkerboard(t_disp_point disp_p, t_xyz a, t_cylinder cy, t_rgb *color)
{
	float	length;
	float	y;
	t_vect	dist;

	dist = create_vector(a, disp_p.intersec_point);
	y = scalar_product(-cy.vec_height, dist);
	length = cy.radius + y;
	if (disp_p.type == DI)
		length = get_len_disc(dist, a, cy, disp_p);
	if ((int)get_teta(dist, cy, disp_p, a) / 30 % 2)
	{
		if ((int)length / (int) (30 * M_PI / 180 * cy.radius) % 2)
			*color = rgb_fill(255, 255, 255);
		else
			*color = rgb_fill(0, 0, 0);
	}
	else
	{
		if ((int)length / (int) (30 * M_PI / 180 * cy.radius) % 2)
			*color = rgb_fill(0, 0, 0);
		else
			*color = rgb_fill(255, 255, 255);
	}
}

static void	cy_texture(t_disp_point disp_p, t_xyz a, t_cylinder cy, t_rgb *color)
{
	float	length;
	float	y;
	t_vect	dist;

	dist = create_vector(a, disp_p.intersec_point);
	y = scalar_product(-cy.vec_height, dist);
	length = cy.radius + y;
	if (disp_p.type == DI)
		length = get_len_disc(dist, a, cy, disp_p);
	*color = get_texture_color((get_teta(dist, cy, disp_p, a) * cy.tex.width)
		/ 360, (cy.tex.height * length) / (2 * cy.radius * cy.height), cy.tex);
}

void	cylinder_color(t_disp_point disp_p, t_objects *objs, t_rgb *color)
{
	t_xyz	a;
	t_vect	vect;

	vect = objs->cy[disp_p.obj_id].vec_height;
	vect = vect * objs->cy[disp_p.obj_id].height / 2.0;
	a.x = objs->cy[disp_p.obj_id].position.x + vect[0];
	a.y = objs->cy[disp_p.obj_id].position.y + vect[1];
	a.z = objs->cy[disp_p.obj_id].position.z + vect[2];
	if (disp_p.tex.tex == TEX)
		cy_texture(disp_p, a, objs->cy[disp_p.obj_id], color);
	else if (disp_p.tex.tex == DAM)
		cy_checkerboard(disp_p, a, objs->cy[disp_p.obj_id], color);
	else
		*color = disp_p.color;
}
