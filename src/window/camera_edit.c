/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:06:38 by odessein          #+#    #+#             */
/*   Updated: 2023/01/09 21:02:19 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

static void	apply_action_cam(t_edit edit_info, t_objects *objs)
{
	if (edit_info.action == TRANSLATE)
	{
		objs->cam->position.x = edit_info.coord.x;
		objs->cam->position.y = edit_info.coord.y;
		objs->cam->position.z = edit_info.coord.z;
	}
	else if (edit_info.action == ROTATE)
	{
		printf("%f %f %f\n", objs->cam->vec_direction[0], objs->cam->vec_direction[1], objs->cam->vec_direction[2]);
		printf("%f %f %f\n", objs->vect_width[0], objs->vect_width[1], objs->vect_width[2]);
		printf("%f %f %f\n", objs->vect_height[0], objs->vect_height[1], objs->vect_height[2]);
		objs->cam->vec_direction = apply_rotation(objs->cam->vec_direction, edit_info.axis, edit_info.angle);
		 objs->vect_width = apply_rotation(objs->vect_width, edit_info.axis, edit_info.angle);
		 objs->vect_height = apply_rotation(objs->vect_height, edit_info.axis, edit_info.angle);
		objs->edited = true;
	}
}

bool	ask_c(t_objects *objs)
{
	t_edit		edit_info;
	t_type	type;

	type = C;
	edit_info = get_edit(type);
	apply_action_cam(edit_info, objs);
	return (true);
}
