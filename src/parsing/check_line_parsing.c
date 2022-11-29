/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:26:25 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 12:27:59 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_element_line(char **lines)
{
	int			i;
	t_must_have	all_elem;

	i = 0;
	init_all_elem(&all_elem);
	while (lines[i])
	{
		if (check_ambient(split_func_condition(line[i], ft_is_space), &all_elem))
			return (false);
		if (check_camera(lines[i], &all_elem))
			return (false);
		if (!loop_light(lines, &i, &all_elem))
			return (false);
		if (!loop_plane(lines, &i, &all_elem))
			return (false);
		if (!loop_sphere(lines, &i, &all_elem))
			return (false);
		if (!loop_cylindre(lines, &i, &all_elem))
			return (false);
	}
	if (!check_all_elem(all_elem))
		return (false);
	return (true);
}

bool	loop_light(char **lines, int *i, t_must_have *all_elem)
{
	while (lines[*i] && lines[*i][0] == 'L' && is_tab(lines[*i][1]))
	{
		if (!check_light(lines[i++]))
			return (false);
	}
	return (true);
}

bool	loop_place(char **lines, int *i, t_must_have *all_elem)
{
		while (lines[*i] && lines[*i][0] == 'p' && line[*i][1] == 'l' && !lines[*i][2])
		{
			all_elem->object = true;
			if (!check_plane(lines[*i]))
				return (false);
		}
		return (true);
}

bool	loop_sphere(char **lines, int *i, t_must_have *all_elem)
{
		while (lines[*i] && lines[*i][0] == 's' && line[*i][1] == 'p' && !lines[*i][2])
		{
			all_elem->object = true;
			if (!check_sphere(lines[*i]))
				return (false);
		}
		return (true);
}

bool	loop_cylindre(char **lines, int *i,  t_must_have *all_elem)
{
		while (lines[*i] && lines[*i][0] == 'c' && line[*i][1] == 'y' && !lines[*i][2])
		{
			all_elem->object = true;
			if (!check_cylinder(lines[*i]))
				return (false);
		}
		return (true);
}
