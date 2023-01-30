/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:36:13 by odessein          #+#    #+#             */
/*   Updated: 2023/01/30 21:37:06 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

bool	fill_cylinder(char **arr, int j, t_objects *objects)
{
	ft_memset(&objects->cy[j], 0, sizeof(objects->cy[j]));
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
	if (arr[6] && !check_texture(&objects->cy[j].tex, arr[6], j, CY))
		return (false);
	objects->cy[j].xm_2[0] = objects->cy[j].position.x
		* objects->cy[j].position.x;
	objects->cy[j].xm_2[1] = objects->cy[j].position.y
		* objects->cy[j].position.y;
	objects->cy[j].xm_2[2] = objects->cy[j].position.z
		* objects->cy[j].position.z;
	objects->cy[j].abc_2[0] = objects->cy[j].vec_direction[0]
		* objects->cy[j].vec_direction[0];
	objects->cy[j].abc_2[1] = objects->cy[j].vec_direction[1]
		* objects->cy[j].vec_direction[1];
	objects->cy[j].abc_2[2] = objects->cy[j].vec_direction[2]
		* objects->cy[j].vec_direction[2];
	objects->cy[j].radius = objects->cy[j].diameter / 2.0;
	objects->cy[j].radius_2 = objects->cy[j].radius * objects->cy[j].radius;
	return (true);
}
