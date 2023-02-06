/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj_systems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:49:51 by odessein          #+#    #+#             */
/*   Updated: 2023/02/06 20:30:48 by mbelrhaz         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */
#include "parsing.h"

bool	fill_cam_system(t_objects *objs)
{
	objs->vect_height = get_vec_vertical(objs->cam->vec_direction);
	if (!objs->vect_height[0] && !objs->vect_height[1]
		&& !objs->vect_height[2])
		return (false);
	objs->vect_width = get_vec_horizontal(objs->cam->vec_direction,
			objs->vect_height);
	return (true);
}

bool	fill_pl_system(t_objects *objs, int i)
{
	t_plane	*pl;

	pl = &(objs->pl[i]);
	if (!pl->vec_direction[0] && !pl->vec_direction[1]
		&& !pl->vec_direction[2])
		return (false);
	pl->vec_height = normalize_vector(get_vec_vertical(pl->vec_direction));
	pl->vec_width = normalize_vector(get_vec_horizontal(pl->vec_direction,
				pl->vec_height));
	return (true);
}

bool	fill_sp_system(t_objects *objs, int i)
{
	t_sphere	*sp;

	sp = &(objs->sp[i]);
	sp->vec_height = normalize_vector(objs->vect_height);
	sp->vec_width = normalize_vector(objs->vect_width);
	sp->vec_depth = normalize_vector(objs->cam->vec_direction);
	return (true);
}

bool	fill_cy_system(t_objects *objs, int i)
{
	t_cylinder	*cy;

	cy = &(objs->cy[i]);
	if (!cy->vec_direction[0] && !cy->vec_direction[1]
		&& !cy->vec_direction[2])
		return (false);
	cy->vec_height = normalize_vector(cy->vec_direction);
	cy->vec_width = normalize_vector(get_vec_vertical(cy->vec_direction));
	cy->vec_depth = normalize_vector(get_vec_horizontal(cy->vec_direction,
				cy->vec_width));
	return (true);
}
