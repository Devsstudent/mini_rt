/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2023/02/06 15:17:33 by odessein         ###   ########.fr       */
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
		if (!fill_pl_system(objs, i++))
			return (false);
	i = 0;
	while (i < objs->nb_sp)
		if (!fill_sp_system(objs, i++))
			return (false);
	i = 0;
	while (i < objs->nb_cy)
		if (!fill_cy_system(objs, i++))
			return (false);
	i = 0;
	while (i < objs->nb_co)
		if (!fill_co_system(objs, i++))
			return (false);
	return (true);
}

static bool	init_mlx(t_objects *objects)
{
	objects->mlx = malloc(sizeof(t_mlx_info));
	if (!objects->mlx)
		return (false);
	objects->mlx->mlx = mlx_init();
	if (!objects->mlx->mlx)
		return (free(objects->mlx), false);
	objects->mlx->win = mlx_new_window(objects->mlx->mlx, 780,
			540, "mini_rt :)");
	objects->mlx->img = mlx_new_image(objects->mlx->mlx, WIN_W, WIN_H);
	if (!objects->mlx->img || !objects->mlx->win)
		return (close_window(objects), false);
	objects->mlx->data = mlx_get_data_addr(objects->mlx->img,
			&objects->mlx->bpp, &objects->mlx->line_size,
			&objects->mlx->endian);
	if (!objects->mlx->data)
		return (close_window(objects), false);
	return (true);
}

int	main(int ac, char **av)
{
	char		**lines;
	t_objects	objects;

	ft_memset(&objects, 0, sizeof(objects));
	objects.editing = false;
	lines = parsing(ac, av);
	if (!lines)
		return (1);
	if (!init_mlx(&objects))
		return (free_double_arr(lines), 2);
	if (!fill_structs(lines, &objects))
		return (free_double_arr(lines), close_window(&objects), 3);
	if (!fill_obj_systems(&objects))
		return (close_window(&objects), 4);
	objects.need_display = true;
	window(&objects);
	free_objs(&objects);
	return (0);
}
