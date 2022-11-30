/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:36:51 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 15:06:25 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_light(char **line_split)
{
	bool	first;
	float	value;
	bool	third;

	first = line_split[0] && line_split[0][0] == 'L' && !line_split[0][1];
	if (!first)
		return (false);
	if (!check_coordinate(line_split[1]))
		return (false);
	third = line_split[2] && line_split[2][0] && ft_isdigit(line_split[2][0])
		&& line_split[2][1] && line_split[2][1] == '.' && line_split[2][2]
		&& ft_isdigit(line_split[2][2]) && !line_split[2][3];
	if (!third)
		return (false);
	else if (!convert_to_float(&value, line_split[2]))
		return (false);
	if (value < 0 || value > 1)
		return (false);
	if (!check_rgb(line_split[3]))
		return (false);
	if (line_split[4])
		return (false);
	return (true);
}
