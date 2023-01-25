/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:46:08 by odessein          #+#    #+#             */
/*   Updated: 2023/01/04 15:16:04 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

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
	if (line_split[4])
		return (false);
	all_elem->object = true;
	return (true);
}
