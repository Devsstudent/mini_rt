/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:12:29 by odessein          #+#    #+#             */
/*   Updated: 2023/01/16 21:06:22 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static bool	in_the_way(t_xyz point, t_vect rayvec, t_xyz origin)
{
	t_vect	vect;

	vect[0] = point.x - origin.x;
	vect[1] = point.y - origin.y;
	vect[2] = point.z - origin.z;
	if (norm_of_vector(vect) > norm_of_vector(rayvec))
		return (false);
	return (true);
}

static int	intersect_self(t_objects *objs, t_disp_point point, int i)
{
	t_line_eq		rayline;
	t_sol_li		list;
	t_vect			rayvec;
	t_disp_point	intersection;

	init_sol_li(&list);
	rayvec[0] = objs->li[i].position.x - objs->cam->position.x;
	rayvec[1] = objs->li[i].position.y - objs->cam->position.y;
	rayvec[2] = objs->li[i].position.z - objs->cam->position.z;
	rayline = get_rayline_eq(rayvec, objs->cam->position);
	if (point.type == SP
		&& !get_specific_sphere(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	if (point.type == PL
		&& !get_specific_plane(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	if ((point.type == CY || point.type == DI)
		&& !get_specific_cylinder(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	intersection = get_intersection(&list, objs->cam->position);
	if (list.head != NULL && list.head->solution.sol_one
		&& in_the_way(intersection.intersec_point, rayvec, objs->cam->position))
		return (free_list(&list), 0);
	free_list(&list);
	return (1);
}

void	get_rayvec_light(t_objects *objs, t_xyz point, t_vect *rayvec, int i)
{
	(*rayvec)[0] = objs->li[i].position.x - point.x;
	(*rayvec)[1] = objs->li[i].position.y - point.y;
	(*rayvec)[2] = objs->li[i].position.z - point.z;
}

t_disp_point	check_light_shadow(t_disp_point disp_p, t_objects *objs,
					int i, t_sol_li *list)
{
	t_line_eq		rayline;
	t_vect			rayvec;

	get_rayvec_light(objs, disp_p.intersec_point, &rayvec, i);
	rayline = get_rayline_eq(rayvec, disp_p.intersec_point);
	if (!get_sphere(objs, list, rayline))
		return (error_intersec());
	if (!get_plane(objs, list, rayline))
		return (error_intersec());
	if (!get_cylinder(objs, list, rayline))
		return (error_intersec());
	return (get_intersection(list, disp_p.intersec_point));
}

bool	check_no_shadow(t_disp_point intersection, t_disp_point initial,
			t_objects *objs, int i)
{
	t_vect			rayvec;
	int				way_to_the_light;

	way_to_the_light = 0;
	way_to_the_light = intersect_self(objs, initial, i);
	if (way_to_the_light == -1)
		return (false);
	get_rayvec_light(objs, initial.intersec_point, &rayvec, i);
	if (intersection.intersec_point.x != -1
		&& intersection.intersec_point.y != -1
		&& intersection.intersec_point.z != -1
		&& in_the_way(intersection.intersec_point,
			rayvec, initial.intersec_point))
		return (true);
	else if (way_to_the_light == 0)
		return (true);
	return (false);
}
