/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:00:39 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 12:27:30 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

typedef struct s_eqq{
	t_xyz	x;
	t_vect	dir;
}			t_eqq;

t_equation	get_quadra_cones_equation(t_line_eq rayline, t_cones cones, t_objects *objs)
{
	t_equation	res;
	t_eqq		ray;
	t_vect		cam_top_cones;
	float		angle;

	ray.x.x = rayline.x.c;
	ray.x.y = rayline.y.c;
	ray.x.z = rayline.z.c;
	ray.dir[0] = rayline.x.t;
	ray.dir[1] = rayline.y.t;
	ray.dir[2] = rayline.z.t;
	ray.dir = normalize_vector(ray.dir);
	angle = cones.angle * M_PI / 180;
	cam_top_cones[0] = cones.c_top.x - objs->cam->position.x;
	cam_top_cones[1] = cones.c_top.y - objs->cam->position.y;
	cam_top_cones[2] = cones.c_top.z - objs->cam->position.z;
	cam_top_cones = normalize_vector(cam_top_cones);
	res.x_pow_two = powf(scalar_product(ray.dir, cones.vec_dir), 2) - pow(cosf(angle), 2);
	res.x_pow_one = 2 * (scalar_product(ray.dir, cones.vec_dir) * scalar_product(cam_top_cones, ray.dir) - scalar_product(ray.dir, cam_top_cones) * powf(cosf(angle), 2));
	res.c = powf(scalar_product(cam_top_cones, cones.vec_dir), 2) - scalar_product(cam_top_cones, cam_top_cones) * cosf(angle) * cosf(angle);
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
		quadra = get_quadra_cones_equation(rayline, obj->co[i], obj);
		solu = solution(quadra, rayline, &err);
		if (err)
			return (false);
		if (solu.one.x == -1 && solu.one.y == -1 && solu.one.z == -1)
			printf("hmm\n");
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
	quadra = get_quadra_cones_equation(rayline, obj->co[i_to_view], obj);
	solu = solution(quadra, rayline, &err);
	if (err)
		return (false);
	if (solu.sol_one && !list_add(list ,new_elem(solu, obj->co[i_to_view].color, CO, i_to_view)))
		return (false);
	return (true);
}
