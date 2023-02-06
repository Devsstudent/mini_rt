/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:21:06 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 21:16:25 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static void	pl_checkerboard(t_rgb *color, t_objects *objs, t_disp_point disp_p)
{
	float	x;
	float	y;
	t_vect	dist;

	dist = create_vector(disp_p.intersec_point,
			objs->pl[disp_p.obj_id].position);
	x = scalar_product(dist, objs->pl[disp_p.obj_id].vec_width);
	y = scalar_product(dist, objs->pl[disp_p.obj_id].vec_height);
	if ((x <= 0 && y <= 0) || (y >= 0 && x >= 0))
	{
		if (((int)x / 10) % 2 == ((int)y / 10) % 2)
			*color = rgb_fill(0, 0, 0);
		else
			*color = rgb_fill(255, 255, 255);
	}
	else if ((x < 0 && y > 0) || (y < 0 && x > 0))
	{
		if (((int)x / 10) % 2 == (-(int)y / 10) % 2)
			*color = rgb_fill(255, 255, 255);
		else
			*color = rgb_fill(0, 0, 0);
	}
}

static void	pl_texture(t_rgb *color, t_objects *objs, t_disp_point disp_p)
{
	int		x;
	int		y;
	t_vect	dist;

	dist = create_vector(disp_p.intersec_point,
			objs->pl[disp_p.obj_id].position);
	x = scalar_product(dist, objs->pl[disp_p.obj_id].vec_width);
	y = scalar_product(dist, objs->pl[disp_p.obj_id].vec_height);
	x = x % objs->pl[disp_p.obj_id].tex.width;
	if (x < 0)
		x *= -1;
	y = y % objs->pl[disp_p.obj_id].tex.height;
	if (y < 0)
		y *= -1;
	*color = get_texture_color(x, y, objs->pl[disp_p.obj_id].tex);
}

void	pl_color(t_rgb *color, t_disp_point disp_p, t_objects *objs)
{
	if (disp_p.tex.tex == DAM)
		pl_checkerboard(color, objs, disp_p);
	else if (disp_p.tex.tex == TEX)
		pl_texture(color, objs, disp_p);
	else
		*color = disp_p.color;
}
