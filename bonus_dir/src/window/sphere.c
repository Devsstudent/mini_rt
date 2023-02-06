/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:05:30 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 20:34:05 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	get_specific_sphere(t_objects *obj, t_sol_li *list,
			t_line_eq rayline, int i_to_view)
{
	t_equation		quadratic;
	bool			err;
	t_solution		solu;
	t_new_elem_info	info;

	err = false;
	quadratic = get_quadra_sphere_equation(rayline, obj->sp[i_to_view]);
	solu = solution(quadratic, rayline, &err);
	if (err)
		return (false);
	fill_info(&info, obj->sp[i_to_view].color,
		i_to_view, obj->sp[i_to_view].tex);
	info.type = SP;
	if (solu.sol_one && !list_add(list,
			new_elem(solu, info)))
		return (false);
	return (true);
}

bool	get_sphere(t_objects *obj, t_sol_li *list, t_line_eq rayline)
{
	t_equation		quadratic;
	bool			err;
	t_solution		solu;
	int				i;
	t_new_elem_info	info;

	i = 0;
	while (i < obj->nb_sp)
	{
		err = false;
		quadratic = get_quadra_sphere_equation(rayline, obj->sp[i]);
		solu = solution(quadratic, rayline, &err);
		if (err)
			return (false);
		fill_info(&info, obj->sp[i].color, i, obj->sp[i].tex);
		info.type = SP;
		if (solu.sol_one
			&& !list_add(list, new_elem(solu, info)))
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
	res.x_pow_two = rayline.x.t * rayline.x.t
		+ rayline.y.t * rayline.y.t + rayline.z.t * rayline.z.t;
	res.x_pow_one = 2 * (rayline.x.t * (rayline.x.c - origin.x)
			+ rayline.y.t * (rayline.y.c - origin.y)
			+ rayline.z.t * (rayline.z.c - origin.z));
	res.c = origin.x * origin.x + origin.y * origin.y
		+ origin.z * origin.z + rayline.x.c * rayline.x.c
		+ rayline.y.c * rayline.y.c + rayline.z.c * rayline.z.c
		- 2 * (rayline.x.c * origin.x + rayline.y.c * origin.y
			+ rayline.z.c * origin.z) - rayon * rayon;
	return (res);
}
