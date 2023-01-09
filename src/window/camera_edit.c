/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:06:38 by odessein          #+#    #+#             */
/*   Updated: 2023/01/09 15:30:21 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

void	apply_action_cam(t_edit edit_info, t_camera *cam)
{
	if (edit_info.action == TRANSLATE)
	{
		cam->position.x = edit_info.coord.x;
		cam->position.y = edit_info.coord.y;
		cam->position.z = edit_info.coord.z;
	}
	else if (edit_info.action == ROTATE)
		cam->vec_direction = apply_rotation(cam->vec_direction, edit_info.axis, edit_info.angle);
}

bool	ask_c(t_objects *objs)
{
	t_edit		edit_info;
	t_type	type;

	type = C;
	edit_info = get_edit(type);
	apply_action_cam(edit_info, objs->cam);
	return (true);
}
