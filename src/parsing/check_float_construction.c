/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_float_construction.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:02:34 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 15:06:15 by odessein         ###   ########.fr       */
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
	if (*line == '.' && i < 10 /* && check_int_max*/)
		line++;
	else
		return (false);
	i = 0;
	while (*line && ft_isdigit(*line))
	{
		i++;
		line++;
	}
	if (i > 2)
		return (false);
	line = save;
	return (true);
}
