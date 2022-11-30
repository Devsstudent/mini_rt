/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:00:49 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 21:58:27 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_plane(char **line_split, t_must_have *all_elem)
{
	bool	first;

	first = line_split[0] && line_split[0][0] == 'p' && line_split[0][1] && line_split[0][1] == 'l' && !line_split[0][2];
	if (!first)
		return (false);
	if (!check_coordinate(line_split[1]))
		return (false);
	if (!check_coordinate_direction(line_split[2]))
		return (false);
	if (!check_rgb(line_split[3]))
		return (false);
	if (line_split[4])
		return (false);
	all_elem->object = true;
	return (true);
}
