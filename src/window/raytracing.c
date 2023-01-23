/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:51 by odessein          #+#    #+#             */
/*   Updated: 2023/01/20 19:21:07 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	loop_rendering(t_objects *objs, t_viewplan view_plan)
{
	int	i;

	i = 0;
	while (i < WIN_H)
	{
		if (!loop_line(objs, &view_plan, i))
			return (false);
		i++;
	}
	mlx_put_image_to_window(objs->mlx->mlx, objs->mlx->win,
		objs->mlx->img, 0, 0);
	return (true);
}

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
//	if (!get_cones(objs, list, rayline))
//		free_list_exit(objs, list);
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

bool	loop_line(t_objects *objs, t_viewplan *view_plan, int i)
{
	int				j;
	t_sol_li		list;
	t_vect			rayvec;
	t_i_j			i_j;

	j = 0;
	while (j < WIN_W)
	{
		init_sol_li(&list);
		i_j.i = i;
		i_j.j = j;
		rayvec = get_vector(view_plan->up_left,
				multp(get_opposite_vector(view_plan->hori), j),
				multp(get_opposite_vector(view_plan->verti), i));
		if (!resolve_equation(objs, &list, rayvec, i_j))
			return (false);
		j++;
	}
	return (true);
}
