/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_equation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:24:28 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/07 19:24:34 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

bool	resolve_equation(t_objects *objs, t_sol_li *list,
			t_vect rayvec, t_i_j i_j)
{
	int				color;
	t_line_eq		rayline;
	t_disp_point	intersec_point;

	rayline = get_rayline_eq(rayvec, objs->cam->position);
	color = 0;
	if (!get_sphere(objs, list, rayline))
		free_exit(objs);
	if (!get_plane(objs, list, rayline))
		free_list_exit(objs, list);
	if (!get_cylinder(objs, list, rayline))
		free_list_exit(objs, list);
	intersec_point = get_intersection(list, objs->cam->position);
	if (intersec_point.intersec_point.x == -1
		&& intersec_point.intersec_point.y == -1
		&& intersec_point.intersec_point.z == -1)
		return (free_list(list), true);
	if (!get_pixel_color(&color, intersec_point, objs))
		free_list_exit(objs, list);
	if (list && (list->head) && (list->head)->solution.sol_one)
		img_pixel_put(objs->mlx, i_j.j, i_j.i, color);
	free_list(list);
	return (true);
}
