/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2023/01/20 18:41:41 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	main(int ac, char **av)
{
	char		**lines;
	t_objects	objects;

	lines = parsing(ac, av);
	if (!lines)
		return (1);
	if (!fill_structs(lines, &objects))
		return (2);
	objects.mlx = malloc(sizeof(t_mlx_info));
	objects.need_display = true;
	objects.co = malloc(sizeof(t_cones *));
	objects.co[0].vec_dir[0] = 0;
	objects.co[0].vec_dir[1] = 0;
	objects.co[0].vec_dir[2] = 1;
	objects.co[0].c_top.x = 0;
	objects.co[0].c_top.y = 0;
	objects.co[0].c_top.z = 20;
	objects.nb_co = 1;
	if (!window(&objects))
		return (3);
	free_objs(&objects);
	return (0);
}
