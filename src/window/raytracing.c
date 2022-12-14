/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:51 by odessein          #+#    #+#             */
/*   Updated: 2022/12/14 17:04:28 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_vect	multp(t_vect vector, int t)
{
	t_vect	res;

	res[0] = vector[0] * (float) t;
	res[1] = vector[1] * (float) t;
	res[2] = vector[2] * (float) t;
	return (res);
}

t_line_eq	get_rayline_eq(t_vect vec_line, t_xyz start_point)
{
	t_line_eq	res;

	res.x.c = start_point.x;
	res.x.t = vec_line[0];
	res.y.c = start_point.y;
	res.y.t = vec_line[1];
	res.z.c = start_point.z;
	res.z.t = vec_line[2];
	return (res);
}

t_vect	get_vector(t_vect up_left, t_vect hori, t_vect verti)
{
	t_vect	res;

	res = up_left + hori + verti;
	return (res);
}

t_vect	get_up_left(t_vect hori, t_vect verti, t_vect orient)
{
	t_vect	h_v_o;

	h_v_o[0] = hori[0] * (WIN_W / 2) + verti[0] * (WIN_H / 2) + orient[0];
	h_v_o[1] = hori[1] * (WIN_W / 2) + verti[1] * (WIN_H / 2) + orient[1];
	h_v_o[2] = hori[2] * (WIN_W / 2) + verti[2] * (WIN_H / 2) + orient[2];
	return (h_v_o);
}

void	img_pixel_put(t_mlx_info *mlx, int j, int i, int color)
{
	char	*data_img;
	int		addon ;

	data_img = mlx->data;
	addon = (j * (mlx->bpp / 8)) + (i * mlx->line_size);
	*(unsigned int *)(data_img + addon) = color;
}

void	loop(t_mlx_info *mlx, t_vect hori, t_vect verti, t_xyz start_point, t_vect orient, t_objects *objs)
{
	int			i;
	int			j;
	t_vect		rayvec;
	t_line_eq	rayline;
	t_equation	quadra;
	t_vect		vect_up_left;
	t_vect		opp_hori;
	t_vect		opp_verti;

	i = 0;
	opp_hori = get_opposite_vector(hori);
	opp_verti = get_opposite_vector(verti);
	vect_up_left = get_up_left(hori, verti, orient);
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			rayvec = get_vector(vect_up_left, multp(opp_hori, j), multp(opp_verti, i));
			//printf("vector : %f %f %f\n", rayvec.x, rayvec.y, rayvec.z);
			rayline = get_rayline_eq(rayvec, start_point);
			quadra = get_quadra_plan_equation(rayline, objs);
			if (solution(quadra))
			img_pixel_put(mlx, j, i, mlx_get_color_value(mlx->mlx, 0xABCDEF));
			quadra = get_quadra_sphere_equation(rayline, objs);
			if (solution(quadra))
				img_pixel_put(mlx, j, i, mlx_get_color_value(mlx->mlx, 0x9AE));
			//transposer dans l'equation de l'objet les x,y,z line
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(objs->mlx->mlx, objs->mlx->win, objs->mlx->img, 0, 0);
}

t_equation	get_quadra_plan_equation(t_line_eq rayline, t_objects *objs)
{
	t_equation	res;
	t_vect		vect_plan;
	t_xyz		p_plan;

	vect_plan = objs->pl->vec_direction;
	p_plan = objs->pl->position;
	res.x_pow_two = 0;
	res.x_pow_one = rayline.x.t * vect_plan[0] + rayline.y.t * vect_plan[1] + rayline.z.t * vect_plan[2];
	res.c = vect_plan[0] * p_plan.x + vect_plan[1] * p_plan.y + vect_plan[2] * p_plan.z - (rayline.x.t * rayline.x.c + rayline.y.t * rayline.y.c + rayline.z.t * rayline.z.c);
	return (res);
}

t_equation	get_quadra_sphere_equation(t_line_eq rayline, t_objects *objs)
{
	t_equation	res;
	t_xyz		origin;
	float		rayon;

	origin = objs->sp->position;
	rayon = objs->sp->diameter / 2.0;
	res.x_pow_two = powf(rayline.x.t, 2) + powf(rayline.y.t, 2) + powf(rayline.z.t, 2);
	res.x_pow_one = 2  * (rayline.x.t * (rayline.x.c - origin.x) + rayline.y.t * (rayline.y.c - origin.y) + rayline.z.t * (rayline.z.c - origin.z));
	res.c = powf(origin.x, 2) + powf(origin.y, 2) + powf(origin.z, 2) + powf(rayline.x.c, 2) + powf(rayline.y.c, 2) + powf(rayline.z.c, 2) - 2 * (rayline.x.c * origin.x + rayline.y.c * origin.y + rayline.z.c * origin.z) - powf(rayon, 2);
	return (res);
}
