/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2023/01/23 21:17:51 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	main(int ac, char **av)
{
	char		**lines;
	t_objects	objects;
	t_cones		co;

	lines = parsing(ac, av);
	if (!lines)
		return (1);
	if (!fill_structs(lines, &objects))
		return (2);
	objects.mlx = malloc(sizeof(t_mlx_info));
	objects.need_display = true;
	objects.co = malloc(sizeof(t_cones *));
	co.vec_dir[0] = 0;
	co.vec_dir[1] = 0;
	co.vec_dir[2] = 1;
	co.vec_dir = normalize_vector(objects.co->vec_dir);
	co.c_top.x = 0;
	co.c_top.y = 0;
	co.c_top.z = -50;
	co.angle = 1;
	co.color.R = 255;
	co.color.G = 255;
	co.color.B = 255;
	objects.co = &co;
	objects.nb_co = 1;
	if (!window(&objects))
		return (3);
	free_objs(&objects);
	return (0);
}
