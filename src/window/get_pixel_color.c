/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:39:22 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/14 22:56:27 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static bool	loop_light(t_disp_point disp_p, t_objects *objs, t_final_pix_color *final)
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
		if (intersection.err)
			return (free_list(&list), false);
		if (check_no_shadow(intersection, disp_p, objs, i))
		{
			(free_list(&list));
			continue ;
		}
		get_rayvec_light(objs, disp_p.intersec_point, &rayvec, i);
		param.distance = norm_of_vector(rayvec);
		param.rayvec = rayvec;
		param.disp_p = disp_p;
		param.intersec = intersection;
		compute_rgb(objs, param, &final->diffuse, i);
		fill_specular(objs, param, &final->specular, i);
		free_list(&list);
	}
	return (true);
}

bool	get_pixel_color(int *color, t_disp_point disp_p, t_objects *objs)
{
	t_rgb				color_rgb;
	float				rgb[3];
	t_final_pix_color	final;

	ft_memset(&rgb, 0, sizeof(rgb));
	ft_memset(&final, 0, sizeof(final));
	final.ambient[0] = objs->amb->ratio * objs->amb->color.R;
	final.ambient[1] = objs->amb->ratio * objs->amb->color.G;
	final.ambient[2] = objs->amb->ratio * objs->amb->color.B;
	color_rgb.R = disp_p.color.R;
	color_rgb.G = disp_p.color.G;
	color_rgb.B = disp_p.color.B;
	loop_light(disp_p, objs, &final);
	*color = create_color(color_rgb, final);
	return (true);
}
