/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quadra_cones.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:33:27 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 21:36:31 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static void	fill_vars(t_vect vec, t_line_eq rayline, t_cone cone,
				t_cone_variable *vars)
{
	vars->a = vec[0];
	vars->b = vec[1];
	vars->c = vec[2];
	vars->i = rayline.x.t;
	vars->j = rayline.y.t;
	vars->k = rayline.z.t;
	vars->x0 = rayline.x.c;
	vars->y0 = rayline.y.c;
	vars->z0 = rayline.z.c;
	vars->xc = cone.position.x;
	vars->yc = cone.position.y;
	vars->zc = cone.position.z;
	vars->x0xc2 = (vars->x0 - vars->xc) * (vars->x0 - vars->xc);
	vars->y0yc2 = (vars->y0 - vars->yc) * (vars->y0 - vars->yc);
	vars->z0zc2 = (vars->z0 - vars->zc) * (vars->z0 - vars->zc);
}

static void	fill_res(t_equation *res, t_cone_variable vars)
{
	res->x_pow_one = 2 * (vars.i * vars.a2cos2 * (vars.x0 - vars.xc) + vars.j
			* vars.b2cos2 * (vars.y0 - vars.yc)
			+ vars.k * vars.c2cos2 * (vars.z0 - vars.zc) + vars.a * vars.b
			* (vars.i * vars.y0 - vars.i * vars.yc + vars.x0 * vars.j - vars.xc
				* vars.j) + vars.a * vars.c * (vars.i * vars.z0 - vars.i
				* vars.zc + vars.x0 * vars.k - vars.xc * vars.k) + vars.b
			* vars.c * (vars.j * vars.z0 + vars.k * vars.y0 - vars.zc
				* vars.j - vars.yc * vars.k));
	res->c = vars.a2cos2 * vars.x0xc2 + vars.b2cos2 * vars.y0yc2
		+ vars.c2cos2 * vars.z0zc2 + 2 * (vars.a * (vars.b * (vars.x0
					* vars.y0 - vars.yc * vars.x0) + vars.c * (vars.x0
					* vars.z0 - vars.x0 * vars.zc)) - vars.a * vars.xc
			* (vars.b * (vars.y0 - vars.yc) + vars.c * (vars.z0
					- vars.zc)) + vars.b * vars.c * ((vars.y0 - vars.yc)
				* (vars.z0 - vars.zc)));
}

t_equation	get_quadra_cone_equation(t_line_eq rayline, t_cone cone)
{
	t_equation		res;
	float			cos;
	t_vect			vec;
	t_cone_variable	vars;

	cos = cone.height / (sqrtf(cone.height * cone.height + (cone.radius)
				* (cone.radius)));
	vec = normalize_vector(cone.vec_dir);
	fill_vars(vec, rayline, cone, &vars);
	vars.a2cos2 = vars.a * vars.a - cos * cos;
	vars.b2cos2 = vars.b * vars.b - cos * cos;
	vars.c2cos2 = vars.c * vars.c - cos * cos;
	res.x_pow_two = vars.i * vars.i * (vars.a2cos2) + vars.j * vars.j
		* (vars.b2cos2) + vars.k * vars.k * (vars.c2cos2) + 2 * (vars.b
			* vars.c * vars.j * vars.k + vars.a * vars.b * vars.i
			* vars.j + vars.a * vars.c * vars.i * vars.k);
	fill_res(&res, vars);
	return (res);
}
