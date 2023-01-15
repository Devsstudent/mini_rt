/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:19:12 by odessein          #+#    #+#             */
/*   Updated: 2023/01/15 22:41:51 by mbelrhaz         ###   ########.fr       */
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
	if (color_conv.rgb.R > 255.0)
		color_conv.rgb.R = 255.0;
	color_conv.rgb.G = (uint8_t)trunc((float)color_conv.rgb.G * rgb_val[1]);
	if (color_conv.rgb.G > 255.0)
		color_conv.rgb.G = 255.0;
	color_conv.rgb.B = (uint8_t)trunc((float)color_conv.rgb.B * rgb_val[2]);
	if (color_conv.rgb.B > 255.0)
		color_conv.rgb.B = 255.0;
	color = color_conv.color;
	return (color);
}

//compute cos(angle) between normal vector and rayvec
float	compute_rgb_from_angle(t_objects *objs, t_color_pam param)
{
	float	ratio;
	t_vect	rayvec;
	t_vect	normal;

	if (param.disp_p.type == SP)
		normal = get_normal_vect_sp(param.disp_p, objs);
	else if (param.disp_p.type == PL)
		normal = get_normal_vect_pl(param.disp_p, objs);
	else if (param.disp_p.type == CY)
		normal = get_normal_vect_cy(param.disp_p, objs);
	else if (param.disp_p.type == DI)
		normal = get_normal_vect_di(param.disp_p, objs);
	else
		return (1);
	rayvec = param.rayvec;
	ratio = scalar_product(rayvec, normal)
		/ (norm_of_vector(rayvec) * norm_of_vector(normal));
	if (ratio < 0.0)
		ratio = -ratio;
	return (ratio);
}

float	get_cos(t_objects *objs, t_color_pam param)
{
	t_vect	rayvec;
	t_vect	normal;
	float	cos;

	if (param.disp_p.type == SP)
		normal = get_normal_vect_sp(param.disp_p, objs);
	else if (param.disp_p.type == PL)
		normal = get_normal_vect_pl(param.disp_p, objs);
	else if (param.disp_p.type == CY)
		normal = get_normal_vect_cy(param.disp_p, objs);
	else if (param.disp_p.type == DI)
		normal = get_normal_vect_di(param.disp_p, objs);
	else
		return (0.0);
	rayvec = param.rayvec;
	cos = scalar_product(rayvec, normal)
		/ (norm_of_vector(rayvec) * norm_of_vector(normal));
	if (cos < 0.0)
		return (-cos);
	return (cos);
}

void	add_specular_component(t_objects *objs, t_color_pam param,
		float rgb[3], int i)
{
	float	cos;

	cos = get_cos(objs, param);
	if (cos >= 0.993)
	{
		rgb[0] = (float)objs->li[i].color.R / (float)param.disp_p.color.R;
		rgb[1] = (float)objs->li[i].color.G / (float)param.disp_p.color.G;
		rgb[2] = (float)objs->li[i].color.B / (float)param.disp_p.color.B;
	}
}

void	compute_rgb(t_objects *objs, t_color_pam param, float rgb[3], int i)
{
	float	ratio;

	ratio = objs->li[i].ratio - param.distance / 1000.0;
	if (ratio < 0.0)
		ratio = 0.0;
	ratio = ratio * compute_rgb_from_angle(objs, param);
	rgb[0] += (float)objs->li[i].color.R * ratio / 255;
	rgb[1] += (float)objs->li[i].color.G * ratio / 255;
	rgb[2] += (float)objs->li[i].color.B * ratio / 255;
	if (rgb[0] > 1.0)
		rgb[0] = 1.0;
	if (rgb[1] > 1.0)
		rgb[1] = 1.0;
	if (rgb[2] > 1.0)
		rgb[2] = 1.0;
	add_specular_component(objs, param, rgb, i);
}

void	ambient_light_quo(t_objects *objs, float rgb[3])
{
	rgb[0] = (float)objs->amb->color.R * objs->amb->ratio / 255.0;
	rgb[1] = (float)objs->amb->color.G * objs->amb->ratio / 255.0;
	rgb[2] = (float)objs->amb->color.B * objs->amb->ratio / 255.0;
}
