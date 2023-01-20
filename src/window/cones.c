/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:00:39 by odessein          #+#    #+#             */
/*   Updated: 2023/01/20 18:43:23 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

t_equation	get_quadra_cones_equation(t_line_eq rayline, t_cones cones)
{
	t_equation	res;
	t_xyz		origin;
	float		height;
	float		center;
	float		radius;
	t_vect		dir;

	//origin maybe false, better neeed to get a point on the axis of the cones defined by the vector director
	//So have to find a point between position and height on the director line (any point)
	origin = cones.position;
	height = cones.height;
	radius = cones.radius;
	dir = cones.vec_direction;
	center = cones.center_base;
	res.x_pow_two = (radius * radius) * (rayline.x.t * rayline.x.t + rayline.y.t * rayline.y.t - rayline.z.t * rayline.z.t) - (height * height) * (rayline.x.t * rayline.x.t + rayline.y.t * rayline.y.t);
	res.x_pow_one = (radius * radius) * ((2 * rayline.x.t * rayline.x.c - 2 * (rayline.x.t * origin.x + rayline.x.t * dir[0] * center) + 2 * rayline.y.t * rayline.y.c) - 2 * (rayline.y.t * origin.y + rayline.y.t * dir[1] * center) - 2 * rayline.z.c * rayline.z.t + 2 * (rayline.z.t * origin.z + rayline.z.t * dir[2] * center)) - (height * height) * (2 * rayline.x.t * rayline.x.c - 2 * (rayline.x.t * origin.x + rayline.x.t * dir[0] * center) + 2 * (rayline.y.t * rayline.y.c) - 2 * (rayline.y.t * origin.y + rayline.y.t * dir[1] * center));
	res.c = (radius * radius) * (rayline.x.c * rayline.x.c - 2 * (rayline.x.c * origin.x + origin.x * dir[0] * center) + origin.x * origin.x + 2 * (origin.x * dir[0] * center) + (dir[0] * center) * (dir[0] * center) + rayline.y.c * rayline.y.c - 2 * (origin.y * rayline.y.c + rayline.y.c * center * dir[1]) + origin.y * origin.y + 2 * origin.y * dir[1] * center + (dir[1] * center) * (dir[1] * center) - (rayline.z.c * rayline.z.c) + 2 * (rayline.z.t * origin.z + origin.z * dir[2] * center) - origin.z * origin.z - 2 * origin.z * dir[2] * center - (dir[2] * center) * (dir[2] * center)) - (height * height) * (rayline.x.c * rayline.x.c - 2 * (rayline.x.c * origin.x + rayline.x.c * dir[0] * center) + origin.x * origin.x + 2 * origin.x * dir[0] * center + (dir[0] * center) * (dir[0] * center) + rayline.y.c * rayline.y.c - 2 * (rayline.y.c * origin.y + rayline.y.c * dir[1] * center) + origin.y * origin.y + 2 * origin.y * dir[1] * center + (dir[1] * center) * (dir[1] * center));
	printf("%f %f %f\n%f %f %f\n", res.x_pow_two, res.x_pow_one, res.c, rayline.x.t, rayline.x.c, origin.x);
	return (res);
}

bool	get_cones(t_objects *obj, t_sol_li *list, t_line_eq rayline)
{
	t_equation	quadra;
	bool		err;
	t_solution	solu;
	int			i;

	i = 0;
	ft_memset(&solu, 0, sizeof(solu));
	while (i < obj->nb_co)
	{
		err = false;
		quadra = get_quadra_cones_equation(rayline, obj->co[i]);
		solu = solution(quadra, rayline, &err);
		if (err)
			return (false);
		if (solu.sol_one)
			printf("test");
		if (solu.sol_one && !list_add(list, new_elem(solu, obj->co[i].color, CO, i)))
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
	quadra = get_quadra_cones_equation(rayline, obj->co[i_to_view]);
	solu = solution(quadra, rayline, &err);
	if (err)
		return (false);
	if (solu.sol_one && !list_add(list ,new_elem(solu, obj->co[i_to_view].color, CO, i_to_view)))
		return (false);
	return (true);
}
