/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:51 by odessein          #+#    #+#             */
/*   Updated: 2023/01/07 18:33:26 by mbelrhaz         ###   ########.fr       */
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
	mlx_put_image_to_window(objs->mlx->mlx, objs->mlx->win, objs->mlx->img, 0, 0);
	return (true);
}

bool	resolve_equation(t_objects *objs, t_solution_list **list, t_vect rayvec, t_i_j i_j)
{
	int				color;
	t_line_eq		rayline;
	t_disp_point	intersec_point;

	rayline = get_rayline_eq(rayvec, objs->cam->position);
	color = 0;
	if (!get_sphere(objs, list, rayline))
		return (false);
	if (!get_plane(objs, list, rayline))
		return (false);
	if (!get_cylinder(objs, list, rayline))
		return (false);
	intersec_point = fill_list_intersection(list, objs->cam->position);
	if (intersec_point.intersec_point.x == -1 && intersec_point.intersec_point.y == -1 && intersec_point.intersec_point.z == -1)
		return (true);
	if (!get_pixel_color(&color, intersec_point, objs))
		return (false);
	if (list && (*list) && (*list)->solution.sol_one)
	{
		img_pixel_put(objs->mlx, i_j.j, i_j.i, color);
	}
	free_list(list);
	return (true);
}

bool	loop_line(t_objects *objs, t_viewplan *view_plan, int i)
{
	int				j;
	t_solution_list			*list;
	t_vect			rayvec;
	t_i_j			i_j;

	j = 0;
	list = malloc(sizeof(t_solution_list));
	if (!list)
		free_exit(objs);
	list = NULL;
	while (j < WIN_W)
	{
		i_j.i = i;
		i_j.j = j;
		rayvec = get_vector(view_plan->up_left, multp(get_opposite_vector(view_plan->hori), j), multp(get_opposite_vector(view_plan->verti), i));
		if (!resolve_equation(objs, &list, rayvec, i_j))
			return (false);
		j++;
	}
	return (true);
}
