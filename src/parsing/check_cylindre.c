/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylindre.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:05:02 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 18:08:46 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_cyliner(char **line_split, t_must_have *all_elem)
{
	bool	first;
	float	value;
	bool	third;

	first = line_split[0] && line_split[0][0] == 's' && !line_split[0][1] && line_split[0][1] && line_split[0][1] == 'h' && !line_split[0][2];
	if (!first)
		return (free_split_return_false(line_split));
	if (!check_coordinate(line_split[1]))
		return (free_split_return_false(line_split));
	if (!check_coordinate_direction(line_split[2]))
		return (free_split_return_false(line_split));
	if (!check_float_construction(line_split[3]))
		return (free_split_return_false(line_split));
	if (!convert_to_float(&value, line_split[3]))
		return (free_split_return_false(line_split));
	if (value >  340282346638528859811704183484516925440 || value < -340282346638528859811704183484516925440)
		return (free_split_return_false(line_split));
	if (!check_float_construction(line_split[4]))
		return (free_split_return_false(line_split));
	if (!convert_to_float(&value, line_split[4]))
		return (free_split_return_false(line_split));
	if (value >  340282346638528859811704183484516925440 || value < -340282346638528859811704183484516925440)
		return (free_split_return_false(line_split));
	if (!check_rgb(line_split[5])
		return (free_split_return_false(line_split));
	if (line_split[6])
		return (free_split_return_false(line_split));
	all_element->object = true;
	return (true);
}
