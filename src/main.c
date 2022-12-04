/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2022/12/04 22:38:58 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int		main(int ac, char **av)
{
	char	**lines;
	t_objects	objects;

	lines = parsing(ac, av);
	if (!lines)
	{
		return (1);
	}
	if (!fill_structs(lines, &objects))
	{
		return (2);
	}
	printf("camera fov = %i\n", objects.cam[0].fov);
	printf("sphere rgb = %i,%i,%i\n", objects.sp[0].color.R, objects.sp[0].color.G, objects.sp[0].color.B);
	printf("cylinder height = %f\n", objects.cy[0].height);
	//Parsing
		//if not error msg (function for it)
	//Start_game
	return (0);
}

