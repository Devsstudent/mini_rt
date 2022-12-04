/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <mbelrhaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:56:41 by odessein          #+#    #+#             */
/*   Updated: 2022/12/04 19:56:22 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	brows_line(char *line, int *i)
{
	*i = 0;
	while (line[*i] && ft_isdigit(line[*i]))
	{
		(*i)++;
	}
	if (*i > 3)
		return (false);
	return (true);
}

bool	check_rgb(char *line)
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
	while (*line)
	{
		if (!brows_line(line, &i))
			return (false);
		value = ft_atoi(line);
		if (value < 0 || value > 255)
			return (false);
		line = line + i;
		if (*line == '\0')
			break ;
		if (*line != ',' && turn < 2)
			return (false);
		if (*line == '\0')
			break ;
		line++;
		turn++;
		if (turn > (int) size/3)
			break ;
	}
	line = save;
	return (true);
}
