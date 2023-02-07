/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:05:02 by odessein          #+#    #+#             */
/*   Updated: 2023/02/07 16:53:03 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	convert_to_float_check_value(char *to_conv)
{
	float	val;

	val = 0;
	if (!convert_to_float(&val, to_conv))
		return (false);
	if (val > (float) INT_MAX || val < (float) INT_MIN)
		return (false);
	return (true);
}

bool	conditional_sequence(char **line_split, bool first)
{
	if (!first)
		return (false);
	if (!check_coordinate(line_split[1]))
		return (false);
	if (!check_coordinate_direction(line_split[2]))
		return (false);
	if (!check_float_construction(line_split[3]))
		return (false);
	if (!convert_to_float_check_value(line_split[3]))
		return (false);
	if (!check_float_construction(line_split[4]))
		return (false);
	if (!convert_to_float_check_value(line_split[4]))
		return (false);
	if (!check_rgb(line_split[5]))
		return (false);
	if (BONUS && line_split[6] && !check_path(line_split[6]) && !line_split[7])
		return (false);
	if (!BONUS && line_split[6])
		return (false);
	return (true);
}

bool	check_cylinder(char **line_split, t_must_have *all_elem)
{
	bool	first;

	first = (line_split[0]
			&& (line_split[0][0] == 'c' || line_split[0][0] == 'C')
			&& line_split[0][1]
			&& (line_split[0][1] == 'y' || line_split[0][1] == 'Y')
			&& !line_split[0][2]);
	if (!conditional_sequence(line_split, first))
		return (false);
	all_elem->object = true;
	return (true);
}
