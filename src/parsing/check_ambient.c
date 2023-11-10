/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:06:05 by odessein          #+#    #+#             */
/*   Updated: 2023/01/03 16:43:00 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_ambient(char **line_split, t_must_have *all_elem)
{
	float	value;

	if (!(line_split[0] && (line_split[0][0] == 'A' || line_split[0][0] == 'a')
			&& !line_split[0][1]))
		return (false);
	else if (all_elem->ambient)
		return (false);
	if (!(line_split[1] && line_split[1][0] && ft_isdigit(line_split[1][0])
			&& line_split[1][1] && line_split[1][1] == '.' && line_split[1][2]
			&& ft_isdigit(line_split[1][2]) && !line_split[1][3]))
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
