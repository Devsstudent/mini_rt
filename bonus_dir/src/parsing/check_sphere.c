/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:46:08 by odessein          #+#    #+#             */
/*   Updated: 2023/02/07 16:03:16 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	check_sphere_end(char **line_split)
{
	if (BONUS)
		if (line_split[4] && (!check_path(line_split[4]) && !line_split[5]))
			return (false);
	if (!BONUS)
		if (line_split[4])
			return (false);
	return (true);
}

bool	check_sphere(char **line_split, t_must_have *all_elem)
{
	bool	first;
	float	value;

	first = (line_split[0]
			&& (line_split[0][0] == 's' || line_split[0][0] == 'S')
			&& line_split[0][1]
			&& (line_split[0][1] == 'p' || line_split[0][1] == 'P')
			&& !line_split[0][2]);
	if (!first)
		return (false);
	if (!check_coordinate(line_split[1]))
		return (false);
	if (!check_float_construction(line_split[2]))
		return (false);
	if (!convert_to_float(&value, line_split[2]))
		return (false);
	if (value > (float) INT_MAX || value < (float) INT_MIN)
		return (false);
	if (!check_rgb(line_split[3]))
		return (false);
	if (!check_sphere_end(line_split))
		return (false);
	all_elem->object = true;
	return (true);
}
