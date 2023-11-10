/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_float_construction.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:02:34 by odessein          #+#    #+#             */
/*   Updated: 2023/01/04 15:26:16 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static int	loop_on_number(char **line)
{
	int	i;

	i = 0;
	while (**line && ft_isdigit(**line))
	{
		i++;
		(*line)++;
	}
	return (i);
}

bool	check_float_construction(char *line)
{
	char	*save;
	int		i;

	save = line;
	i = loop_on_number(&line);
	if (i == 10)
	{
		if (!check_int_max(save))
			return (false);
		line = save;
		return (true);
	}
	if (!(*line) && i < 11)
		return (true);
	if ((*line == '.' && i < 11))
		line++;
	else
		return (false);
	i = loop_on_number(&line);
	if (i > 3 || i == 0)
		return (false);
	line = save;
	return (true);
}
