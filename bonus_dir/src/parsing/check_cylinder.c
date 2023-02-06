/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:05:02 by odessein          #+#    #+#             */
/*   Updated: 2023/02/07 00:01:53 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	check_floats(char **line_split)
{
	float	value;

	if (!check_float_construction(line_split[3]))
		return (false);
	if (!convert_to_float(&value, line_split[3]))
		return (false);
	if (value > (float) INT_MAX || value < (float) INT_MIN)
		return (false);
	if (!check_float_construction(line_split[4]))
		return (false);
	if (!convert_to_float(&value, line_split[4]))
		return (false);
	if (value > (float) INT_MAX || value < (float) INT_MIN)
		return (false);
	return (true);
}

bool	check_cylinder(char **line_split, t_must_have *all_elem)
{
	if (!(line_split[0] && (line_split[0][0] == 'c' || line_split[0][0] == 'C')
		&& line_split[0][1] && (line_split[0][1] == 'y'
		|| line_split[0][1] == 'Y') && !line_split[0][2]))
		return (false);
	if (!check_coordinate(line_split[1]))
		return (false);
	if (!check_coordinate_direction(line_split[2]))
		return (false);
	if (!check_floats(line_split))
		return (false);
	if (!check_rgb(line_split[5]))
		return (false);
	if (BONUS && line_split[6] && !(check_path(line_split[6])) && !line_splite[7])
		return (false);
	else if (!BONUS && line_split[6])
		return (false);
	all_elem->object = true;
	return (true);
}
