/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:26:25 by odessein          #+#    #+#             */
/*   Updated: 2022/11/28 16:59:06 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_element_line(char **lines)
{
	int	i;
	int	semantics;

	i = 0;
	semantics = 0;
	while (lines[i])
	{
		if (i == 0 && !check_ambient(lines[i], &semantics))
			return (false);
		if (i == 1 && !check_camera(lines[i], &semantics))
			return (false);
		if (!loop_light(lines, &i, &semantics))
			return (false);
		if (!loop_plane(lines, &i, &semantics))
			return (false);
		if (!loop_sphere(lines, &i, &semantics))
			return (false);
		if (!loop_cylindre(lines, &i, &semantics))
			return (false);
	}
	if (semantics < 6)
		return (false);
	return (true);
}

bool	loop_light(char **lines, int *i, int *semantics)
{
	while (lines[*i] && lines[*i][0] == 'L' && is_tab(lines[*i][1]))
	{
		(*semantics)++;
		if (!check_light(lines[i++]))
			return (false);
	}
	return (true);
}

bool	loop_place(char **lines, int *i, int *semantics)
{
		while (lines[*i] && lines[*i][0] == 'p' && line[*i][1] == 'l' && !lines[*i][2])
		{
			(*semantics)++;
			if (!check_plane(lines[*i]))
				return (false);
		}
		return (true);
}

bool	loop_sphere(char **lines, int *i, int *semantics)
{
		while (lines[*i] && lines[*i][0] == 's' && line[*i][1] == 'p' && !lines[*i][2])
		{
			(*semantics)++;
			if (!check_sphere(lines[*i]))
				return (false);
		}
		return (true);
}

bool	loop_cylindre(char **lines, int *i, int *semantics)
{
		while (lines[*i] && lines[*i][0] == 'c' && line[*i][1] == 'y' && !lines[*i][2])
		{
			(*semantics)++;
			if (!check_cylinder(lines[*i]))
				return (false);
		}
		return (true);
}
