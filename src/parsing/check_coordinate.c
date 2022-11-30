/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coordinate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:00:43 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 14:58:24 by odessein         ###   ########.fr       */
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
	save = line;
	while (line)
	{
		if (!brows_line(line, &i))
			return (false);
		if (!convert_to_float(&value, line))
			return (false);
		//DEFINE ?
		//HOW TO CHECK OVERFLOW ..
		//SIZE MAX + check each character
		if (value > (float) INT_MAX || value < (float) INT_MIN)
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