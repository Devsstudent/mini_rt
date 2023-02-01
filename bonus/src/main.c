/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 21:36:13 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	fill_obj_systems(t_objects *objs)
{
	int	i;

	i = 0;
	if (!fill_cam_system(objs))
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
