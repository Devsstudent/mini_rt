/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coordinate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:00:43 by odessein          #+#    #+#             */
/*   Updated: 2023/01/04 14:46:08 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	brows_line(char *line, int *i)
{
	bool	test;
	char	*save;

	test = false;
	*i = 0;
	save = line;
	if (line[*i] == '-' || line[*i] == '+')
	{
		test = true;
		(*i)++;
	}
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if ((*i > 10 && !test) || (*i > 11 && test))
		return (false);
	if (!check_int_max(save))
		return (false);
	if (line[*i] == '.')
		(*i)++;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	return (true);
}

bool	loop_check_coord_dir(char *line, float *value, int *turn, int *i)
{
	size_t	size;

	size = ft_strlen(line);
	while (line)
	{
		if (!brows_line(line, i))
			return (false);
		if (!convert_to_float(value, line))
			return (false);
		if (*value < -1 || *value > 1)
			return (false);
		line = line + *i;
		if (!*line)
			break ;
		if (*line != ',' && *turn < 2)
			return (false);
		if (*turn > (int) size / 3)
			break ;
		if (!*line)
			break ;
		(*turn)++;
		line++;
	}
	return (true);
}

bool	check_coordinate_direction(char *line)
{
	char	*save;
	int		i;
	int		turn;
	float	value;

	turn = 0;
	i = 0;
	save = line;
	if (!loop_check_coord_dir(line, &value, &turn, &i))
		return (false);
	line = save;
	return (true);
}

bool	loop_check_coord(char *line, float *value, int *turn, int *i)
{
	size_t	size;

	size = ft_strlen(line);
	while (line)
	{
		if (!brows_line(line, i))
			return (false);
		if (!convert_to_float(value, line))
			return (false);
		if (*value > (float) INT_MAX || *value < (float) INT_MIN)
			return (false);
		line = line + *i;
		if (!*line)
			break ;
		if (*line != ',' && *turn < 2)
			return (false);
		if (!*line)
			break ;
		(*turn)++;
		line++;
		if (*turn > ((int) size / 3))
			break ;
	}
	return (true);
}

bool	check_coordinate(char *line)
{
	int		i;
	int		turn;
	float	value;
	char	*save;

	turn = 0;
	value = 0;
	save = line;
	if (!loop_check_coord(line, &value, &turn, &i))
		return (false);
	line = save;
	return (true);
}
