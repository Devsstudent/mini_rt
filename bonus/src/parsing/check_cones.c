/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:11:45 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 17:53:19 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

static bool	check_floats(char **line)
{
	float	value;

	if (!check_float_construction(line[3]))
		return (false);
	if (!convert_to_float(&value, line[3]))
		return (false);
	if (value > (float) INT_MAX || value < (float) INT_MIN)
		return (false);
	if (!check_float_construction(line[4]))
		return (false);
	if (!convert_to_float(&value, line[4]))
		return (false);
	if (value > (float) INT_MAX || value < (float) INT_MIN)
		return (false);
	return (true);
}

bool	check_cones(char **line, t_must_have *all_elem)
{
	if (!(line[0] && (line[0][0] == 'c' || line[0][0] == 'C')
			&& line[0][1] && (line[0][1] == 'o' || line[0][1] == 'O') && !line[0][2]))
			return (false);
	if (!check_coordinate(line[1]))
		return (false);
	if (!check_coordinate_direction(line[2]))
		return (false);
	if (!check_floats(line))
		return (false);
	if (!check_rgb(line[5]))
		return (false);
	if (line[6])
		return (false);
	all_elem->object = true;
	return (true);
}