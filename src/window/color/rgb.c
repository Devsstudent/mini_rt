/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:19:12 by odessein          #+#    #+#             */
/*   Updated: 2023/02/07 19:55:12 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static void	handle_overflow(int rgb[3])
{
	if (rgb[0] >= 255)
		rgb[0] = 255;
	if (rgb[1] >= 255)
		rgb[1] = 255;
	if (rgb[2] >= 255)
		rgb[2] = 255;
	if (rgb[0] <= 0)
		rgb[0] = 0;
	if (rgb[1] <= 0)
		rgb[1] = 0;
	if (rgb[2] <= 0)
		rgb[2] = 0;
}

int	create_color(t_rgb rgb, t_final_pix_color final)
{
	int		color;
	t_color	color_conv;
	int		rgb1[3];

	color_conv.rgb.t = 0;
	rgb1[0] = rgb.r * (final.diffuse[0] + final.ambient[0] / 255)
		+ final.specular[0];
	rgb1[1] = rgb.g * (final.diffuse[1] + final.ambient[1] / 255)
		+ final.specular[1];
	rgb1[2] = rgb.b * (final.diffuse[2] + final.ambient[2] / 255)
		+ final.specular[2];
	handle_overflow(rgb1);
	color_conv.rgb.r = (uint8_t)rgb1[0];
	color_conv.rgb.g = (uint8_t)rgb1[1];
	color_conv.rgb.b = (uint8_t)rgb1[2];
	color = color_conv.color;
	return (color);
}

void	compute_rgb(t_objects *objs, t_color_pam param, t_vect *diffuse, int i)
{
	float	ratio;

	ratio = compute_rgb_from_angle(objs, param) * objs->li[i].ratio;
	(*diffuse)[0] += (float)objs->li[i].color.r * ratio / 255;
	(*diffuse)[1] += (float)objs->li[i].color.g * ratio / 255;
	(*diffuse)[2] += (float)objs->li[i].color.b * ratio / 255;
	if ((*diffuse)[0] > 1)
		(*diffuse)[0] = 1;
	if ((*diffuse)[1] > 1)
		(*diffuse)[0] = 1;
	if ((*diffuse)[2] > 1)
		(*diffuse)[0] = 1;
}

void	fill_specular(t_objects *objs, t_color_pam param,
			t_vect *specular, int i)
{
	float	ratio;

	ratio = get_specular(param.rayvec, param.disp_p, objs);
	(*specular)[0] += (float)objs->li[i].color.r * ratio * objs->li[i].ratio;
	(*specular)[1] += (float)objs->li[i].color.g * ratio * objs->li[i].ratio;
	(*specular)[2] += (float)objs->li[i].color.b * ratio * objs->li[i].ratio;
}
