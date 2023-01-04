/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:36:13 by odessein          #+#    #+#             */
/*   Updated: 2023/01/04 15:37:29 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

bool	fill_cylinder(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->cy[j].position, arr[1]))
		return (false);
	if (!convert_to_orientation(&objects->cy[j].vec_direction, arr[2]))
		return (false);
	if (!convert_to_float(&objects->cy[j].diameter, arr[3]))
		return (false);
	if (!convert_to_float(&objects->cy[j].height, arr[4]))
		return (false);
	if (!convert_to_rgb(&objects->cy[j].color, arr[5]))
		return (false);
	return (true);
}
