/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:06:05 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 15:01:26 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_ambient(char **line_split, t_must_have *all_elem)
{
	bool	first;
	bool	second;
	float	value;

	first = line_split[0] && line_split[0][0] == 'A' && !line_split[0][1];
	second = line_split[1] && line_split[1][0] && ft_isdigit(line_split[1][0])
		&& line_split[1][1] && line_split[1][1] == '.' && line_split[1][2]
		&& ft_isdigit(line_split[1][2]) && !line_split[1][3];
	if (!first || (first && all_elem->ambient))
		return (false);
	if (!second)
		return (false);
	else if (!convert_to_float(&value, line_split[1]))
		return (false);
	if (value < 0 || value > 1)
		return (false);
	if (!check_rgb(line_split[2]))
		return (false);
	if (line_split[3])
		return (false);
	all_elem->ambient = true;
	return (true);
}
