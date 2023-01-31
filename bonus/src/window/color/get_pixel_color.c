/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:39:22 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/31 15:30:41 by odessein         ###   ########.fr       */
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

static void	fill_color(t_rgb *color, t_disp_point disp_p, t_objects *objs, t_i_j i_j)
{
	t_vect	dist;
	t_rgb	white;
	t_rgb	black;

	(void) i_j;
	white.R = 255;
	white.G = 255;
	white.B = 255;
	ft_memset(&black, 0, sizeof(black));
	if (disp_p.type == PL)
		pl_color(color, disp_p, objs);
	else if (disp_p.type == SP)
		sphere_color(disp_p, color, objs);
	else if (disp_p.type == CY || disp_p.type == DI)
	{
		t_xyz	a;
		t_vect	vect;
		vect = objs->cy[disp_p.obj_id].vec_height;
		vect = vect * objs->cy[disp_p.obj_id].height / 2.0;
		a.x = objs->cy[disp_p.obj_id].position.x + vect[0];
		a.y = objs->cy[disp_p.obj_id].position.y + vect[1];
		a.z = objs->cy[disp_p.obj_id].position.z + vect[2];
		dist = create_vector(a, disp_p.intersec_point);
		cylinder_color(dist, disp_p, white, black, color, objs, a);
	}
	else if (disp_p.type == CO || disp_p.type == CO_DI)
	{
		dist = create_vector(objs->co[disp_p.obj_id].position, disp_p.intersec_point);
		cones_color(dist, color, white, black, disp_p, objs);
	}
	else
		*color = disp_p.color;
}

t_rgb	get_texture_color(int x, int y, t_obj_texture tex)
{
	t_rgb	res;

	res.B = tex.addr[x * (tex.bpp / 8) + y * (tex.line_size)];
	res.G = tex.addr[x * (tex.bpp / 8) + y * (tex.line_size) + 1];
	res.R = tex.addr[x * (tex.bpp / 8) + y * (tex.line_size) + 2];
	return (res);
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
