/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:19:12 by odessein          #+#    #+#             */
/*   Updated: 2023/01/14 22:50:10 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

int	create_color(t_rgb rgb, float rgb_val[3])
{
	int		color;
	t_color	color_conv;

	color_conv.rgb = rgb;
	color_conv.rgb.T = 0;
	color_conv.rgb.R = (uint8_t)trunc((float)color_conv.rgb.R * rgb_val[0]);
	color_conv.rgb.G = (uint8_t)trunc((float)color_conv.rgb.G * rgb_val[1]);
	color_conv.rgb.B = (uint8_t)trunc((float)color_conv.rgb.B * rgb_val[2]);
	color = color_conv.color;
	return (color);
}

//compute cos(angle) between normal vector and rayvec
//for now only works on spheres
float	compute_rgb_from_angle(t_objects *objs, t_color_pam param)
{
	float	ratio;
	t_vect	rayvec;
	t_vect	normal;

	if (param.disp_p.type != SP)
		return (1);
	rayvec = param.rayvec;
	normal = get_normal_vect_sp(param.disp_p, objs);
	ratio = scalar_product(rayvec, normal)
		/ (norm_of_vector(rayvec) * norm_of_vector(normal));
	return (ratio);
}

void	compute_rgb(t_objects *objs, t_color_pam param, float rgb[3], int i)
{
	float	ratio;

	ratio = objs->li[i].ratio - param.distance / 1000.0;
	ratio = ratio * compute_rgb_from_angle(objs, param);
	if (ratio < 0.0)
		ratio = 0.0;
	rgb[0] += (float)objs->li[i].color.R * ratio / 255.0;
	rgb[1] += (float)objs->li[i].color.G * ratio / 255.0;
	rgb[2] += (float)objs->li[i].color.B * ratio / 255.0;
	if (rgb[0] > 1.0)
		rgb[0] = 1.0;
	if (rgb[1] > 1.0)
		rgb[1] = 1.0;
	if (rgb[2] > 1.0)
		rgb[2] = 1.0;
}

void	ambient_light_quo(t_objects *objs, float rgb[3])
{
	rgb[0] = (float)objs->amb->color.R * objs->amb->ratio / 255.0;
	rgb[1] = (float)objs->amb->color.G * objs->amb->ratio / 255.0;
	rgb[2] = (float)objs->amb->color.B * objs->amb->ratio / 255.0;
}
