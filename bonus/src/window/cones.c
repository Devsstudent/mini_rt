/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:00:39 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 18:56:53 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

t_equation	get_quadra_cone_equation(t_line_eq rayline, t_cone cone)
{
	t_equation	res;
	float		cos;
	t_vect		vec;
	float		a,b,c,i,j,k;
	float		x0,y0,z0,xc,yc,zc;
	float		a2cos2, b2cos2, c2cos2;
	float		x0xc2, y0yc2, z0zc2;

	cos = cone.height / (sqrtf(cone.radius * cone.radius + (cone.radius / 2)
		* (cone.radius / 2)));
	vec = normalize_vector(cone.vec_dir);
	a = vec[0];
	b = vec[1];
	c = vec[2];
	i = rayline.x.t;
	j = rayline.y.t;
	k = rayline.z.t;
	x0 = rayline.x.c;
	y0 = rayline.y.c;
	z0 = rayline.z.c;
	xc = cone.position.x;
	yc = cone.position.y;
	zc = cone.position.z;
	a2cos2 = a * a - cos * cos;
	b2cos2 = b * b - cos * cos;
	c2cos2 = c * c - cos * cos;
	x0xc2 = (x0 - xc) * (x0 - xc);
	y0yc2 = (y0 - yc) * (y0 - yc);
	z0zc2 = (z0 - zc) * (z0 - zc);
	//a
	res.x_pow_two = i * i * (a2cos2) + j * j * (b2cos2)
		+ k * k * (c2cos2) + 2 * (b * c * j * k + a * b * i * j
		+ a * c * i * k);

	//b
	res.x_pow_one = 2 * (i * a2cos2 * (x0 - xc) + j * b2cos2 * (y0-yc)
		+ k * c2cos2 * (z0 - zc) + a * b * (i * y0 - i * yc + x0 * j - xc * j)
		+ a * c * (i * z0 - i * zc + x0 * k - xc * k) + b * c * (j * z0
		+ k * y0 - zc * j - yc * k));

	//c
	res.c = a2cos2 * x0xc2 + b2cos2 * y0yc2 + c2cos2 * z0zc2 + 2 * (a * (b
		* (x0 * y0 - yc * x0) + c * (x0 * z0 - x0 * zc)) - a * xc * (b
		* (y0 - yc) + c * (z0 - zc)) + b * c * ((y0 - yc) * (z0 - zc)));
	return (res);
}

bool	get_cones(t_objects *obj, t_sol_li *list, t_line_eq rayline)
{
	t_equation	quadra;
	bool		err;
	t_solution	solu;
	int			i;

	i = 0;
	while (i < obj->nb_co)
	{
		err = false;
		quadra = get_quadra_cone_equation(rayline, obj->co[i]);
		solu = solution(quadra, rayline, &err);
		if (err)
			return (false);
		if (solu.sol_one
			&& !list_add(list, new_elem(solu, obj->co[i].color, CO, i)))
			return (false);
		i++;
	}
	return (true);
}

bool	get_specific_cone(t_objects *obj, t_sol_li *list, t_line_eq rayline, int i_to_view)
{
	t_equation	quadra;
	bool		err;
	t_solution	solu;

	err = false;
	quadra = get_quadra_cone_equation(rayline, obj->co[i_to_view]);
	solu = solution(quadra, rayline, &err);
	if (err)
		return (false);
	if (solu.sol_one && !list_add(list
			,new_elem(solu, obj->co[i_to_view].color, CO, i_to_view)))
		return (false);
	return (true);
}

