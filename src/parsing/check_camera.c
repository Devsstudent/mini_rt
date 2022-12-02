/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:41:11 by odessein          #+#    #+#             */
/*   Updated: 2022/12/02 16:54:08 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_fov(char *line)
{
	int	i;
	int	value;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (false);
		if (i > 3)
			return (false);
		i++;
	}
	value = ft_atoi(line);
	if (value > 180	|| value < 0)
		return (false);
	return (true);
}

bool	check_camera(char **line_split, t_must_have *all_element)
{
	bool	first;

	first = line_split[0] && (line_split[0][0] == 'C' || line_split[0][0] == 'c')
				&& !line_split[0][1];
	if (!first || (first && all_element->camera))
		return (false);
	if (!check_coordinate(line_split[1]))
		return (false);
	if (!check_coordinate_direction(line_split[2]))
		return (false);
	if (!check_fov(line_split[3]))
		return (false);
	if (line_split[4])
		return (false);
	all_element->camera = true;
	return (true);
}
