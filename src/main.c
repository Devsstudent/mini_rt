/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2022/12/04 22:06:54 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int		main(int ac, char **av)
{
	char	**lines;
	t_objects	objects;
	//Structure definir sur la stack

	lines = parsing(ac, av);
	if (!lines)
	{
		return (1);
	}
	if (!fill_structs(lines, &objects))
	{
		return (2);
	}
	printf("strut camera\n camera fov = %i", objects.cam[0].fov);
	//Parsing
		//if not error msg (function for it)
	//Start_game
	return (0);
}

