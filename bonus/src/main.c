/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 11:59:42 by odessein         ###   ########.fr       */
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
	//why the vector director of the cam ? 
	sp->vec_depth = normalize_vector(objs->cam->vec_direction);
}

void	fill_cy_system(t_objects *objs, int i)
{
	t_cylinder	*cy;

	cy = &(objs->cy[i]);
	//do not normalize vec_direction here, honestly I don't know why
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

bool	fill_obj_systems(t_objects *objs)
{ int	i;
	i = 0;
	if (!fill_cam_system(objs))
//	else
//	else
		return (false);
	while (i < objs->nb_pl)
		fill_pl_system(objs, i++);
	i = 0;
	while (i < objs->nb_sp)
		fill_sp_system(objs, i++);
	i = 0;
	while (i < objs->nb_cy)
		fill_cy_system(objs, i++);
	i = 0;
	while (i < objs->nb_co)
		fill_co_system(objs, i++);
	return (true);
}

int	main(int ac, char **av)
{
	char		**lines;
	t_objects	objects;

	lines = parsing(ac, av);
	if (!lines)
		return (1);
	objects.mlx = malloc(sizeof(t_mlx_info));
	if (!objects.mlx)
		return (free_double_arr(lines), 2);
	objects.mlx->mlx = mlx_init();
	if (!objects.mlx->mlx)
		return (free_double_arr(lines), 4);
	if (!fill_structs(lines, &objects))
		return (2);
	if (!fill_obj_systems(&objects))
		return (3);
	objects.need_display = true;
	if (!window(&objects))
		return (3);
	free_objs(&objects);
	return (0);
}
