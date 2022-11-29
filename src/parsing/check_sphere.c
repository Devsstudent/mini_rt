/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:46:08 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 18:02:20 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_float_construction(char *line)
{
	char	*save;
	int		i;

	while (*line && ft_isdigit(line))
	{
		line++;
		i++;
	}
	if (*line == '.' && i < 10 && /*check_int_max*/)
		line++;
	else
		return (false);
	i = 0;
	while (*line && ft_isdigit(line))
	{
		i++;
		line++;
	}
	if (i > 2)
		return (false);
	line = save;
	return (true);
}

bool	check_sphere(char **line_split, t_must_have *all_elem)
{
	bool	first;
	float	value;
	bool	third;

	first = line_split[0] && line_split[0][0] == 's' && !line_split[0][1] && line_split[0][1] && line_split[0][1] == 'h' && !line_split[0][2];
	if (!first)
		return (free_split_return_false(line_split));
	if (!check_coordinate(line_split[1]))
		return (free_split_return_false(line_split));
	if (!check_float_construction(line_split[2]))
		return (free_split_return_false(line_split));
	if (!convert_to_float(&value, line_split[2]))
		return (free_split_return_false(line_split));
	if (value >  340282346638528859811704183484516925440 || value < -340282346638528859811704183484516925440)
		return (free_split_return_false(line_split));
	if (!check_rgb(line_split[3])
		return (free_split_return_false(line_split));
	if (line_split[4])
		return (free_split_return_false(line_split));
	all_element->object = true;
	return (true);
}
