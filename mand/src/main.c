/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:50:57 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 16:12:08 by odessein         ###   ########.fr       */
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
	objects.need_display = true;
	if (!window(&objects))
		return (3);
	free_objs(&objects);
	return (0);
}
