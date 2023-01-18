/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2023/01/18 16:14:28 by odessein         ###   ########.fr       */
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
	objects.co = malloc(sizeof(t_cones));
	objects.co->height = 25;
	objects.co->radius = 10;
	objects.co->position.x = 0;
	objects.co->position.y = 0;
	objects.co->position.z = 1000;
	objects.co->color.R = 255;
	objects.co->color.G = 0;
	objects.co->color.B = 0;
	objects.nb_co = 1;
	if (!window(&objects))
		return (3);
	free_objs(&objects);
	return (0);
}
