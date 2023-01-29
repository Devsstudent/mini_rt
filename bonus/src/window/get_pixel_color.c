/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:39:22 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/29 20:08:59 by odessein         ###   ########.fr       */
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

static void	sphere_color(t_vect dist, t_disp_point disp_p, t_rgb white, t_rgb black, t_rgb *color, t_objects *objs)
{
	float	x;
	float	y;
	float	z;
	t_vect	ve;
	float	cos_teta;
	float	cos_phi;
	t_sphere	sp;

	sp = objs->sp[disp_p.obj_id];

	x = scalar_product(dist, sp.vec_width);
	y = scalar_product(dist, sp.vec_height);
	z = scalar_product(dist, sp.vec_depth);

	ve = x * sp.vec_width + z * sp.vec_depth;

	cos_teta = scalar_product(ve, sp.vec_width) / ((norm_of_vector(ve)));

	float	teta = acos(cos_teta) * 180 / M_PI;
	if (z < 0)
		teta = 360 - teta;

	cos_phi = scalar_product(dist, sp.vec_height) / norm_of_vector(dist);

	float	phi = acos(cos_phi) * 180 / M_PI;

	if (((int)teta / 30) % 2)
	{
		if ((int)phi / 30 % 2)
			*color = white;
		else
			*color = black;
	}
	else
	{
		if ((int)phi / 30 % 2)
			*color = black;
		else
			*color = white;
	}
}

static void	fill_color(t_rgb *color, t_disp_point disp_p, t_objects *objs, t_i_j i_j)
{
	t_vect	dist;
	float	x;
	float	y;
	t_rgb	white;
	t_rgb	black;

	(void) i_j;
	white.R = 255;
	white.G = 255;
	white.R = 255;
	ft_memset(&black, 0, sizeof(black));
	if (disp_p.type == PL && disp_p.tex.tex == DAM)
	{
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
	else if (disp_p.type == SP && disp_p.tex.tex == DAM)
	{
		dist = create_vector(objs->sp[disp_p.obj_id].position, disp_p.intersec_point);
		sphere_color(dist, disp_p, white, black, color, objs);
	}
	else
		*color = disp_p.color;
}

//Rajouter une structure de static a reinstialiser pour s'avoir la position du dernier moment ou on a changer de couleur pour comparer avec le vecteur u et v si la distance a ete parcourus ou pas

//C'est bancale ca casse les couiiles
bool	get_pixel_color(int *color, t_disp_point disp_p, t_objects *objs, t_i_j i_j)
{
	t_rgb				color_rgb;
	float				rgb[3];
	t_final_pix_color	final;
	float				ka;

	ka = 0.5;
	ft_memset(&rgb, 0, sizeof(rgb));
	ft_memset(&final, 0, sizeof(final));
	final.ambient[0] = ka * objs->amb->ratio * objs->amb->color.R;
	final.ambient[1] = ka * objs->amb->ratio * objs->amb->color.G;
	final.ambient[2] = ka * objs->amb->ratio * objs->amb->color.B;
	fill_color(&color_rgb, disp_p, objs, i_j);
	loop_light(disp_p, objs, &final);
	*color = create_color(color_rgb, final);
	return (true);
}
