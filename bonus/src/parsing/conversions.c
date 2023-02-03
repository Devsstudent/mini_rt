/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 20:22:32 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/01 19:59:52 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	convert_to_rgb(t_rgb *rgb, char *arr)
{
	char	**rgb_arr;

	rgb_arr = ft_split(arr, ',');
	if (!rgb_arr)
		return (false);
	if (!rgb_arr[0] || !rgb_arr[1] || !rgb_arr[2])
		return (false);
	rgb->R = ft_atoi(rgb_arr[0]);
	rgb->G = ft_atoi(rgb_arr[1]);
	rgb->B = ft_atoi(rgb_arr[2]);
	return (free_double_arr(rgb_arr), true);
}

bool	convert_to_xyz(t_xyz *xyz, char *arr)
{
	char	**xyz_arr;

	xyz_arr = ft_split(arr, ',');
	if (!xyz_arr)
		return (false);
	if (!convert_to_float(&xyz->x, xyz_arr[0]))
		return (free_double_arr(xyz_arr), false);
	if (!convert_to_float(&xyz->y, xyz_arr[1]))
		return (free_double_arr(xyz_arr), false);
	if (!convert_to_float(&xyz->z, xyz_arr[2]))
		return (free_double_arr(xyz_arr), false);
	return (free_double_arr(xyz_arr), true);
}
