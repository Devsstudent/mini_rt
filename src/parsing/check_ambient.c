/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:06:05 by odessein          #+#    #+#             */
/*   Updated: 2022/11/28 17:14:25 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_ambient(char *line, int *semantic)
{
	int		i;
	bool	ratio;

	i = 0;
	ratio = false;
	if (line && line[0] != 'A' && !is_space(line[1]))
		return (false);
	while (line[i])
	{
		if (is_space(line[i]))
		{
			i++;
			continue ;
		}
		if (is_digit(line[i]) && !ratio)
		{
			ratio = true;
			if (line[i + 1] && line[i + 1] != '.')
				return (false);
			if (line[i + 2] && !is_digit(line[i + 2]))
				return (false);
		}
		else if (is_digit(line[i])
	}
}
