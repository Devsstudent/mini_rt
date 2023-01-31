/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:21:06 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 13:45:59 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

void	pl_color(t_rgb *color, t_disp_point disp_p, t_objects *objs, t_rgb white, t_rgb black)
{
	float	x;
	float	y;
	t_vect	dist;

	dist = create_vector(disp_p.intersec_point, objs->pl[disp_p.obj_id].position);
	x = scalar_product(dist, objs->pl[disp_p.obj_id].vec_width);
	y = scalar_product(dist, objs->pl[disp_p.obj_id].vec_height);
	if ((x <= 0 && y <= 0) || (y >= 0 && x >= 0))
	{
		if (((int)x / 10) % 2 == ((int)y / 10) % 2)
			*color = black;
		else
			*color = white;
	}
	else if ((x < 0 && y > 0) || (y < 0 && x > 0))
	{
		if (((int)x / 10) % 2 == (-(int)y / 10) % 2)
			*color = white;
		else
			*color = black;
	}
}
