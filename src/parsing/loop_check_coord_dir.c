/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_check_coord_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:21:15 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 20:27:38 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

static bool	brows_and_convert(char *line, float *value, int *i)
{
	if (!brows_line_coord(line, i))
		return (false);
	if (!convert_to_float(value, line))
		return (false);
	if (*value < -1 || *value > 1)
		return (false);
	return (true);
}

bool	loop_check_coord_dir(char *line, float *value, int *turn, int *i)
{
	size_t	size;

	size = ft_strlen(line);
	while (line)
	{
		brows_and_convert(line, value, i);
		line = line + *i;
		if (!*line)
		{
			if (*turn < 2)
				return (false);
			break ;
		}
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
