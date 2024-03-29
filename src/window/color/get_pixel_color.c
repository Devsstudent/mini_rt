/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:39:22 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/07 19:53:31 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static bool	loop_light(t_disp_point disp_p, t_objects *objs,
				t_final_pix_color *final)
{
	int					i;
	t_sol_li			list;
	t_disp_point		intersection;
	t_vect				rayvec;
	t_color_pam			param;

	i = -1;
	while (++i < objs->nb_li)
	{
		init_sol_li(&list);
		intersection = check_light_shadow(disp_p, objs, i, &list);
		(free_list(&list));
		if (intersection.err)
			return (false);
		if (check_no_shadow(intersection, disp_p, objs, i))
			continue ;
		get_rayvec_light(objs, disp_p.intersec_point, &rayvec, i);
		param.distance = norm_of_vector(rayvec);
		param.rayvec = rayvec;
		param.disp_p = disp_p;
		compute_rgb(objs, param, &final->diffuse, i);
		fill_specular(objs, param, &final->specular, i);
	}
	return (true);
}

static void	fill_color(t_rgb *color, t_disp_point disp_p, t_objects *objs)
{
	t_rgb	white;
	t_rgb	black;

	white.r = 255;
	white.g = 255;
	white.b = 255;
	ft_memset(&black, 0, sizeof(black));
	if (disp_p.type == PL)
		pl_color(color, disp_p, objs);
	else if (disp_p.type == SP)
		sphere_color(disp_p, color, objs);
	else if (disp_p.type == CY || disp_p.type == DI)
		cylinder_color(disp_p, objs, color);
	else if (BONUS && (disp_p.type == CO || disp_p.type == CO_DI))
		cones_color(color, disp_p, objs);
	else
		*color = disp_p.color;
}

t_rgb	get_texture_color(int x, int y, t_obj_texture tex)
{
	t_rgb	res;

	res.b = tex.addr[x * (tex.bpp / 8) + y * (tex.line_size)];
	res.g = tex.addr[x * (tex.bpp / 8) + y * (tex.line_size) + 1];
	res.r = tex.addr[x * (tex.bpp / 8) + y * (tex.line_size) + 2];
	return (res);
}

bool	get_pixel_color(int *color, t_disp_point disp_p, t_objects *objs)
{
	t_rgb				color_rgb;
	float				rgb[3];
	t_final_pix_color	final;
	float				ka;

	ka = 0.5;
	ft_memset(&rgb, 0, sizeof(rgb));
	ft_memset(&final, 0, sizeof(final));
	final.ambient[0] = ka * objs->amb->ratio * objs->amb->color.r;
	final.ambient[1] = ka * objs->amb->ratio * objs->amb->color.g;
	final.ambient[2] = ka * objs->amb->ratio * objs->amb->color.b;
	fill_color(&color_rgb, disp_p, objs);
	loop_light(disp_p, objs, &final);
	*color = create_color(color_rgb, final);
	return (true);
}
