/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 20:25:38 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/07 00:33:03 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	build_plane(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = count_obj(triple_arr, "pl");
	objects->nb_pl = size;
	if (size == 0)
		return (true);
	objects->pl = malloc(sizeof(t_plane) * size);
	if (!objects->pl)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "pl", i))
		{
			if (!fill_plane(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	build_cylinder(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = count_obj(triple_arr, "cy");
	objects->nb_cy = size;
	if (size == 0)
		return (true);
	objects->cy = malloc(sizeof(t_cylinder) * size);
	if (!objects->cy)
		return (false);
	objects->nb_cy = size;
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "cy", i))
		{
			if (!fill_cylinder(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	build_sphere(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = count_obj(triple_arr, "sp");
	if (size == 0)
		return (true);
	objects->sp = malloc(sizeof(t_sphere) * size);
	if (!objects->sp)
		return (false);
	objects->nb_sp = size;
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "sp", i))
		{
			if (!fill_sphere(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	build_camera(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	objects->cam = malloc(sizeof(t_camera));
	if (!objects->cam)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "C", i))
		{
			if (!fill_camera(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	build_ambient_light(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	objects->amb = malloc(sizeof(t_ambient_light));
	if (!objects->amb)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "A", i))
		{
			if (!fill_ambient_light(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
