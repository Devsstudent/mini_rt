/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:00:39 by odessein          #+#    #+#             */
/*   Updated: 2023/01/17 19:13:22 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

t_equation	get_quadra_cones_equation(t_line_eq rayline, t_cones cones)
{
	t_equation	res;
	t_xyz		origin;
	float		height;
	float		radius;

	//origin maybe false, better neeed to get a point on the axis of the cones defined by the vector director
	//So have to find a point between position and height on the director line (any point)
	origin = cones.position;
	height = cones.height;
	radius = cones.radius;
	res.x_pow_two = radius * radius - 2 * (height * height);
	res.x_pow_one = (radius * radius) * (2 * rayline.x.t * rayline.x.c - 2 * rayline.x.t * rayline.x.c * origin.x + 2 * rayline.y.t * rayline.y.c - 2 * rayline.y.t * rayline.y.c * origin.y - rayline.z.t * rayline.z.c - 2 * rayline.z.c * rayline.z.t * origin.z) - (height * height) * (rayline.x.t * rayline.x.c - 2 * rayline.x.t * rayline.x.c * origin.x + rayline.y.c * rayline.y.t - 2 * rayline.y.c * rayline.y.t * origin.y);
	res.c = (rayline.x.t * rayline.x.c) * (rayline.x.t * rayline.x.c) + origin.x * origin.x + origin.y * origin.y - origin.z * origin.z + (rayline.y.t * rayline.y.c) * (rayline.y.t * rayline.y.c) - (rayline.z.c * rayline.z.t) * (rayline.z.c *rayline.z.t) - (height * height) * ((rayline.x.t * rayline.x.c) * (rayline.x.c * rayline.x.t) + origin.x * origin.x + (rayline.y.c * rayline.y.t) * (rayline.y.c * rayline.y.t) + origin.y * origin.y);
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
