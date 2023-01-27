/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:00:49 by odessein          #+#    #+#             */
/*   Updated: 2023/01/27 10:43:57 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_path(char *path)
{
	size_t	size;

	if (!path)
		return (false);
	size = ft_strlen(path);
	if (size > 4 && (path[size - 1] != 'm' || path[size - 2] != 'p'
		|| path[size - 3] != 'm' || path[size - 4] != '.'))
		return (false)
	else if (size < 4)
		return (false);
	if (access(path, F_OK) == -1)
		return (false);
	return (true);
}

bool	check_plane(char **line_split, t_must_have *all_elem)
{
	bool	first;

	first = (line_split[0] && (line_split[0][0] == 'p'
				|| line_split[0][0] == 'P') && line_split[0][1]
			&& (line_split[0][1] == 'l' || line_split[0][1] == 'L')
			&& !line_split[0][2]);
	if (!first)
		return (false);
	if (!check_coordinate(line_split[1]))
		return (false);
	if (!check_coordinate_direction(line_split[2]))
		return (false);
	if (!check_rgb(line_split[3]))
		return (false);
	if (line_split[4] && !check_path(line_split[4]) && !line_split[5])
		return (false);
	all_elem->object = true;
	return (true);
}
