/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:05:30 by odessein          #+#    #+#             */
/*   Updated: 2022/12/19 13:22:36 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	get_sphere(t_objects *obj, t_viewplan *viewplan, t_solution_list **list, t_vect rayvec)
{
	t_line_eq	rayline;
	t_equation	quadratic;
	bool		err;
	t_solution		solu;
	int		i;

	i = 0;
	(void) viewplan;
	while (i < obj->nb_sp)
	{
		err = false;
		rayline = get_rayline_eq(rayvec, obj->cam->position);
		quadratic = get_quadra_sphere_equation(rayline, obj->sp[i]);
		solu = solution(quadratic, rayline, &err);
		if (err)
			return (false);
		if (!list_add(list, new_elem(SP, solu)))
			return (false);
		i++;
	}
	return (true);
}

t_equation	get_quadra_sphere_equation(t_line_eq rayline, t_sphere sphere)
{
	t_equation	res;
	t_xyz		origin;
	float		rayon;

	origin = sphere.position;
	rayon = sphere.diameter / 2.0;
	res.x_pow_two = powf(rayline.x.t, 2) + powf(rayline.y.t, 2) + powf(rayline.z.t, 2);
	res.x_pow_one = 2  * (rayline.x.t * (rayline.x.c - origin.x) + rayline.y.t * (rayline.y.c - origin.y) + rayline.z.t * (rayline.z.c - origin.z));
	res.c = powf(origin.x, 2) + powf(origin.y, 2) + powf(origin.z, 2) + powf(rayline.x.c, 2) + powf(rayline.y.c, 2) + powf(rayline.z.c, 2) - 2 * (rayline.x.c * origin.x + rayline.y.c * origin.y + rayline.z.c * origin.z) - powf(rayon, 2);
	return (res);
}
