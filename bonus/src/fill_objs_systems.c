/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objs_systems.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:33:36 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/01 18:34:35 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

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

void	fill_pl_system(t_objects *objs, int i)
{
	t_plane	*pl;

	pl = &(objs->pl[i]);
	pl->vec_height = normalize_vector(get_vec_vertical(pl->vec_direction));
	pl->vec_width = normalize_vector(get_vec_horizontal(pl->vec_direction
		, pl->vec_height));

}

void	fill_sp_system(t_objects *objs, int i)
{
	t_sphere	*sp;

	sp = &(objs->sp[i]);
	sp->vec_height = normalize_vector(objs->vect_height);
	sp->vec_width = normalize_vector(objs->vect_width);
	sp->vec_depth = normalize_vector(objs->cam->vec_direction);
}

void	fill_cy_system(t_objects *objs, int i)
{
	t_cylinder	*cy;

	cy = &(objs->cy[i]);
	cy->vec_height = normalize_vector(cy->vec_direction);
	cy->vec_width = normalize_vector(get_vec_vertical(cy->vec_direction));
	cy->vec_depth = normalize_vector(get_vec_horizontal(cy->vec_direction
			, cy->vec_width));
}

void	fill_co_system(t_objects *objs, int i)
{
	t_cone	*co;

	co = &(objs->co[i]);
	co->vec_height = normalize_vector(co->vec_dir);
	co->vec_width = normalize_vector(get_vec_vertical(co->vec_height));
	co->vec_depth = normalize_vector(get_vec_horizontal(co->vec_height
			, co->vec_width));
}

