/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2022/12/05 14:35:18 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	free_object(t_objects *obj)
{
	if (obj->cy)
		free(obj->cy);
	if (obj->pl)
		free(obj->pl);
	if (obj->sp)
		free(obj->sp);
	if (obj->li)
		free(obj->li);
	free(obj->cam);
	free(obj->amb);
}

int		main(int ac, char **av)
{
	char	**lines;
	t_objects	objects;
	t_mlx_info	mlx;

	lines = parsing(ac, av);
	if (!lines)
	{
		return (1);
	}
	if (!fill_structs(lines, &objects))
	{
		return (2);
	}
	if (!window(&objects, &mlx))
		return (3);
	//printf("plan nb = %i\n", objects.nb_cy);
	//printf("sphere rgb = %i,%i,%i\n", objects.sp[0].color.R, objects.sp[0].color.G, objects.sp[0].color.B);
//	printf("cylinder height = %f\n", objects.cy[0].height);
	//Parsing
		//if not error msg (function for it)
	//Start_game
	free_object(&objects);
	return (0);
}

