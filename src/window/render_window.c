/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:55:46 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 19:33:14 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

int	render_window(void	*objss)
{
	t_vect	vector_width;
	t_vect	vector_height;
	t_viewplan	view_plan;
	t_objects	*objs;

	objs = (t_objects *) objss;
	if (!objs->need_display)
		return (1);
	//printf("%f %f %f\n", objs->cam->vec_direction[0],  objs->cam->vec_direction[1],  objs->cam->vec_direction[2] );
	vector_height = get_vec_vertical(objs->cam->vec_direction);
	if (!vector_height[0] && !vector_height[1] && !vector_height[2])
		return (2);
	vector_width = get_vec_horizontal(objs->cam->vec_direction, vector_height);
	view_plan.hori = get_screen_unit_hor_vect(objs->cam->vec_direction, vector_width, objs->cam->fov);
	view_plan.verti = get_screen_unit_vert_vect(view_plan.hori, vector_height);
	view_plan.up_left = get_up_left(view_plan.hori, view_plan.verti, objs->cam->vec_direction);
	loop_rendering(objs, view_plan);
	//To get up_left
	//We have to define 1 vector (for left_right)
	//We have to define 1 vector (for up_down)
	objs->need_display = false;
	return (1);
}
