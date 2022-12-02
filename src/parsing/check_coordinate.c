/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coordinate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:00:43 by odessein          #+#    #+#             */
/*   Updated: 2022/12/02 16:35:40 by odessein         ###   ########.fr       */
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
	if ((*i > 10 && !test)|| (*i > 11 && test))
		return (false);
	if (!check_int_max(save))
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
	size_t	size;

	save = line;
	size = ft_strlen(line);
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
		if (turn > (int) size / 3)
			break ;
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
	size_t	size;

	turn = 0;
	size = ft_strlen(line);
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
		if (turn > ((int) size / 3))
			break ;
	}
	line = save;
	return (true);
}
