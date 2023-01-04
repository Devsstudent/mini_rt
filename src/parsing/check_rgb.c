/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <mbelrhaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:56:41 by odessein          #+#    #+#             */
/*   Updated: 2023/01/04 15:15:05 by odessein         ###   ########.fr       */
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

bool	loop_check_rgb(char *line, int *i, long *value, int *turn)
{
	size_t	size;

	size = ft_strlen(line);
	while (*line)
	{
		if (!brows_line(line, i))
			return (false);
		*value = ft_atoi(line);
		if (*value < 0 || *value > 255 || *value > (long) INT_MAX)
			return (false);
		line = line + *i;
		if (*line == '\0')
			break ;
		if (*line != ',' && *turn < 2)
			return (false);
		if (*line == '\0')
			break ;
		line++;
		(*turn)++;
		if (*turn > (int) size / 3)
			break ;
	}
	return (true);
}

bool	check_rgb(char *line)
{
	long	value;
	int		i;
	int		turn;
	char	*save;

	if (!line)
		return (false);
	value = -1;
	turn = 0;
	save = line;
	if (!loop_check_rgb(line, &i, &value, &turn))
		return (false);
	line = save;
	return (true);
}
