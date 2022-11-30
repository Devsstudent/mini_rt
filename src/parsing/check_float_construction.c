/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_float_construction.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:02:34 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 22:22:10 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_float_construction(char *line)
{
	char	*save;
	int		i;

	save = line;
	i = 0;
	while (*line && ft_isdigit(*line))
	{
		line++;
		i++;
	}
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
	i = 0;
	while (*line && ft_isdigit(*line))
	{
		i++;
		line++;
	}
	if (i > 3 || i == 0)
		return (false);
	line = save;
	return (true);
}
