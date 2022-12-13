/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:51 by odessein          #+#    #+#             */
/*   Updated: 2022/12/13 16:44:21 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_xyz	multp(t_xyz vector, int t)
{
	t_xyz	res;

	res.x = vector.x * (float) t;
	res.y = vector.y * (float) t;
	res.z = vector.z * (float) t;
	return (res);
}

t_line_eq	get_rayline_eq(t_xyz vec_line, t_xyz start_point)
{
	t_line_eq	res;

	res.x.c = start_point.x;
	res.x.t = vec_line.x;
	res.y.c = start_point.y;
	res.y.t = vec_line.y;
	res.z.c = start_point.z;
	res.z.t = vec_line.z;
	return (res);
}

t_xyz	get_vector(t_xyz hori, t_xyz verti, t_xyz orient)
{
	t_xyz	res;

	res.x = hori.x * (WIN_W  / 2)+ verti.x * (WIN_H / 2) + orient.x;
	res.y = hori.y * (WIN_W / 2) + verti.y * (WIN_H / 2) + orient.y;
	res.z = hori.z * (WIN_W / 2) + verti.z * (WIN_H / 2) + orient.z;
	return (res);
}

void	loop(t_mlx_info *mlx, t_xyz hori, t_xyz verti, t_xyz start_point, t_xyz orient, t_objects *objs)
{
	int			i;
	int			j;
	t_xyz		rayvec;
	t_line_eq	rayline;
	t_equation	quadra;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			rayvec = get_vector(multp(hori, j), multp(verti, i), orient);
			rayline = get_rayline_eq(rayvec, start_point);
			quadra = get_quadra_sphere_equation(rayline, objs);
			if (solution(quadra))
				mlx_pixel_put(mlx->mlx, mlx->win, j, i, mlx_get_color_value(mlx->mlx, 0xABCDEF));
			//transposer dans l'equation de l'objet les x,y,z line
			j++;
		}
		i++;
	}
}

t_equation	get_quadra_sphere_equation(t_line_eq rayline, t_objects *objs)
{
	t_equation	res;
	t_xyz		origin;
	float		rayon;

	origin = objs->sp->position;
	rayon = objs->sp->diameter / 2.0;
	res.x_pow_two = powf(rayline.x.t, 2) + powf(rayline.y.t, 2) + powf(rayline.z.t, 2);
	res.x_pow_one = -2 * (rayline.x.t * (rayline.x.c + rayline.x.c * origin.x) + rayline.y.t * (rayline.y.c + rayline.y.c * origin.y) + rayline.z.t * (rayline.z.c + rayline.z.c * origin.z));
	res.c = powf(rayline.x.c, 2) + powf(rayline.y.c, 2) + powf(rayline.z.c, 2) + powf(origin.x, 2) + powf(origin.y, 2) + powf(origin.z, 2) - powf(rayon, 2);
	return (res);
}
