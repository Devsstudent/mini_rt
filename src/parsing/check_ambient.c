/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:06:05 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 17:45:28 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	brows_line(char *line, int *i)
{
	*i = 0;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (*i > 3)
		return (false);
	return (true);
}

static bool	check_rgb(char *line)
{
	int		value;
	int		i;
	int		turn;
	char	*save;
	size_t	size;

	if (!line)
		return (false);
	size = ft_strlen(line);
	turn = 0;
	save = line;
	while (line)
	{
		if (!brows_line(line, &i))
			return (false);
		value = ft_atoi(line);
		if (value < 0 || value > 255)
			return (false);
		line = line + i;
		if (*line != ',' && turn < 2)
			return (false);
		line++;
		turn++;
		if (turn > size/3)
			break ;
	}
	line = save;
	return (true);
}

bool	check_ambient(char **line_split, t_must_have *all_elem)
{
	bool	first;
	bool	second;
	bool	third;
	float	value;

	first = line_split[0] && line_split[0][0] == 'A' && !line_split[0][1];
	second = line_split[1] && line_split[1][0] && ft_isdigit(line_split[1][0])
		&& line_split[1][1] && line_split[1][1] == '.' && line_split[1][2]
		&& ft_isdigit(line_split[1][2]) && !line_split[1][3];
	if (!first || (first && all_elem->ambient))
		return (free_split_return_false(line_split));
	if (!second)
		return (free_split_return_false(line_split));
	else if (!convert_to_float(&value, line_split[1]))
		return (free_split_return_false(line_split));
	if (value < 0 || value > 1)
		return (free_split_return_false(line_split));
	if (!check_rgb(line_split[2])
		return (free_split_return_false(line_split));
	if (line_split[3])
		return (free_split_return_false(line_split));
	all_elem->ambient = true;
	return (true);
}
