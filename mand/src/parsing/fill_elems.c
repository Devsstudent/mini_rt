/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 20:29:06 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/24 15:08:51 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

bool	fill_ambient_light(char **arr, int j, t_objects *objects)
{
	if (!convert_to_float(&objects->amb[j].ratio, arr[1]))
		return (false);
	if (!convert_to_rgb(&objects->amb[j].color, arr[2]))
		return (false);
	return (true);
}

bool	fill_camera(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->cam[j].position, arr[1]))
		return (false);
	if (!convert_to_orientation(&objects->cam[j].vec_direction, arr[2]))
		return (false);
	objects->cam[j].fov = ft_atoi(arr[3]);
	return (true);
}

bool	fill_light(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->li[j].position, arr[1]))
		return (false);
	if (!convert_to_float(&objects->li[j].ratio, arr[2]))
		return (false);
	if (!convert_to_rgb(&objects->li[j].color, arr[3]))
		return (false);
	return (true);
}

bool	fill_sphere(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->sp[j].position, arr[1]))
		return (false);
	if (!convert_to_float(&objects->sp[j].diameter, arr[2]))
		return (false);
	if (!convert_to_rgb(&objects->sp[j].color, arr[3]))
		return (false);
	return (true);
}

bool	fill_plane(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->pl[j].position, arr[1]))
		return (false);
	if (!convert_to_orientation(&objects->pl[j].vec_direction, arr[2]))
		return (false);
	if (!convert_to_rgb(&objects->pl[j].color, arr[3]))
		return (false);
	//if (ft_strncmp(arr[4], "1", 2))
	//	objects->pl[j].chess = true;
	return (true);
}
