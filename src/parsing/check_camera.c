/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:41:11 by odessein          #+#    #+#             */
/*   Updated: 2023/01/03 16:15:26 by mbelrhaz         ###   ########.fr       */
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
	if (value > 180 || value < 0)
		return (false);
	return (true);
}

bool	check_camera(char **line_split, t_must_have *all_element)
{
	if (!(line_split[0] && (line_split[0][0] == 'C'
			|| line_split[0][0] == 'c') && !line_split[0][1])
			|| ((line_split[0] && (line_split[0][0] == 'C'
			|| line_split[0][0] == 'c')
			&& !line_split[0][1]) && all_element->camera))
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
