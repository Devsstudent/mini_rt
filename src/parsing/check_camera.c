/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:41:11 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 17:52:49 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	brows_line(char *line, int *i)
{
	*i = 0;
	if (line[*i] == '-' || line[*i] == '+')
		(*i)++;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (*i > 9)
		//check_int_max_int_minvalue
		return (false);
	if (line[*i] == '.')
		(*i)++;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	return (true);
}

bool	check_coordinate_direction(char *line)
{
	int		i;
	int		turn;
	float	value;
	char	*save;

	save = line;
	turn = 0;
	while (line)
	{
		if (!brows_line(line, &i))
			return (false);
		if (!convert_to_float(&value, line))
			return (false);
		if (value < -1 || value > 1)
			return (false);
		line = line + i;
		if (*line != ',' && turn < 2)
			return (false);
		turn++;
		line++;
	}
	line = save;
	return (true);
}

bool	check_coordinate(char *line)
{
	int		i;
	int		turn;
	float	value;
	char	*save;

	turn = 0;
	while (line)
	{
		if (!brows_line(line, &i))
			return (false);
		if (!convert_to_float(&value, line))
			return (false);
		//DEFINE ?
		//HOW TO CHECK OVERFLOW ..
		//SIZE MAX + check each character
		if (value >  340282346638528859811704183484516925440 || value < -340282346638528859811704183484516925440)
			return (false);
		line = line + i;
		if (*line != ',' && turn < 2)
			return (false);
		turn++;
		line++;
	}
	line = save;
	return (true);
}

bool	check_camera(char **line_split, t_must_have *all_element)
{
	bool	first;

	first = line_split[0] && line_split[0][0] == 'C' && !line_split[0][1];
	if (!first || (first && all_elem->camera))
		return (free_split_return_false(line_split));
	if (!check_coordinate(line_split[1]))
		return (free_split_return_false(line_split));
	if (!check_coordinate_direction(line_split[2]))
		return (free_split_return_false(line_split));
	if (!line_split[3])
		return (free_split_return_false(line_split));
	all_element->camera = true;
	return (true);
}
