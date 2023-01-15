/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:19:12 by odessein          #+#    #+#             */
/*   Updated: 2023/01/15 21:48:25 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

int	create_color(t_rgb rgb, t_final_pix_color final)
{
	int		color;
	t_color	color_conv;
	int		rgb1[3];

	(void) rgb;
	//printf("%f %f %f\n", final.diffuse[0], final.ambient[0], final.specular[0]);
	color_conv.rgb.T = 0;
	rgb1[0] = rgb.R * (final.diffuse[0] + final.ambient[0] / 255) + final.specular[0];
	rgb1[1] = rgb.G * (final.diffuse[1] + final.ambient[1] / 255) + final.specular[1];
	rgb1[2] = rgb.B * (final.diffuse[2] + final.ambient[2] / 255) + final.specular[2];
	if (rgb1[0] >= 255)
		rgb1[0] = 255;
	if (rgb1[1] >= 255)
		rgb1[1] = 255;
	if (rgb1[2] >= 255)
		rgb1[2] = 255;
	if (rgb1[0] <= 0)
		rgb1[0] = 0; 
	if (rgb1[1] <= 0)
		rgb1[1] = 0;
	if (rgb1[2] <= 0)
		rgb1[2] = 0;
//	printf("%i %i %i\n", rgb1[0], rgb1[1], rgb1[2]);
	color_conv.rgb.R = (uint8_t)rgb1[0];
	color_conv.rgb.G = (uint8_t)rgb1[1];
	color_conv.rgb.B = (uint8_t)rgb1[2];
	color = color_conv.color;
	return (color);
}

//compute cos(angle) between normal vector and rayvec
float	compute_rgb_from_angle(t_objects *objs, t_color_pam param)
{
	float	ratio;
	t_vect	rayvec;
	t_vect	normal;
	float	kd;

	if (param.disp_p.type == SP)
	{
		kd = 1;
		normal = normalize_vector(get_normal_vect_sp(param.disp_p, objs));
	}
	else if (param.disp_p.type == PL)
	{
		kd = 1;
		normal = normalize_vector(get_normal_vect_pl(param.disp_p, objs));
	}
	else if (param.disp_p.type == CY)
	{
		kd = 1;
		normal = normalize_vector(get_normal_vect_cy(param.disp_p, objs));
	}
	else if (param.disp_p.type == DI)
	{
		kd = 1;
		normal = normalize_vector(get_normal_vect_di(param.disp_p, objs));
	}
	else
		return (1);
	kd = 0.8;
	rayvec = normalize_vector(param.rayvec);
	ratio = kd * fmax(scalar_product(rayvec, normal), 0);
	return (ratio);
}

void	compute_rgb(t_objects *objs, t_color_pam param, t_vect *diffuse, int i)
{
	float	ratio;

	ratio =  compute_rgb_from_angle(objs, param) * objs->li[i].ratio;
	(*diffuse)[0] += (float)objs->li[i].color.R * ratio / 255;
	(*diffuse)[1] += (float)objs->li[i].color.G * ratio / 255;
	(*diffuse)[2] += (float)objs->li[i].color.B * ratio / 255;
	if ((*diffuse)[0] > 1)
		(*diffuse)[0] = 1;
	if ((*diffuse)[1] > 1)
		(*diffuse)[0] = 1;
	if ((*diffuse)[2] > 1)
		(*diffuse)[0] = 1;
}

void	fill_specular(t_objects *objs, t_color_pam param, t_vect *specular, int i)
{
	float	ratio;

	ratio = get_specular(param.rayvec, param.disp_p, objs);
	(*specular)[0] += (float)objs->li[i].color.R * ratio * objs->li[i].ratio;
	(*specular)[1] += (float)objs->li[i].color.G * ratio * objs->li[i].ratio;
	(*specular)[2] += (float)objs->li[i].color.B * ratio * objs->li[i].ratio;
}
