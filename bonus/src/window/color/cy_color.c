/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:23:33 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 13:23:50 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

void	cylinder_color(t_vect dist, t_disp_point disp_p, t_rgb white, t_rgb black, t_rgb *color, t_objects *objs, t_xyz a)
{
	float	length;
	float	teta;
	float	cos_teta;
	float	y, z;
	t_xyz	p;

	t_cylinder cy = objs->cy[disp_p.obj_id];
	y = scalar_product(-cy.vec_height, dist);
	z = scalar_product(cy.vec_depth, dist);
	p.x = a.x - y * cy.vec_height[0]; 
	p.y = a.y - y * cy.vec_height[1]; 
	p.z = a.z - y * cy.vec_height[2];
	t_vect	vec = create_vector(p, disp_p.intersec_point);
	cos_teta = scalar_product(vec, cy.vec_width) / norm_of_vector(vec);
	teta = acos(cos_teta) * 180 / M_PI;
	if (z < 0)
		teta = 360 - teta;
	length = cy.radius + y;
	if (disp_p.type == DI)
	{
		if (y > 0.1)
			length = norm_of_vector(dist);
		else
		{
			t_xyz point;
			point.x = a.x - 2 * cy.vec_height[0];
			point.y = a.y - 2 * cy.vec_height[1];
			point.z = a.z - 2 * cy.vec_height[2];
			length = norm_of_vector(create_vector(disp_p.intersec_point, point));
		}
	}
	float	square_side = 30 * M_PI / 180 * cy.radius;
	if ((int)teta / 30 % 2)
	{
		if ((int)length / (int)square_side % 2)
			*color = white;
		else
			*color = black;
	}
	else
	{
		if ((int)length / (int)square_side % 2)
			*color = black;
		else
			*color = white;
	}
}
