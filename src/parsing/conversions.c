/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 20:22:32 by mbelrhaz          #+#    #+#             */
/*   Updated: 2022/12/09 16:08:42 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	convert_to_float(float *val, char *arr)
{
	int		i;
	int		j;
	int		dot;
	char	*nb;

	i = 0;
	j = 0;
	dot = 0;
	nb = malloc(sizeof(char) * (ft_strlen(arr) + 1));
	if (!nb)
	{
		return (false);
	}
	while (arr[i])
	{
		if (arr[i] == '.')
		{
			dot = 1;
			if (arr[i + 1] && arr[i + 2] != '\0')
				dot++;
			i++;
			continue ;
		}
		nb[j] = arr[i];
		j++;
		i++;
	}
	nb[j] = '\0';
	if (dot == 1)
		*val = (float)(ft_atoi(nb)) / 10.0;
	else if (dot == 2)
		*val = (float)(ft_atoi(nb)) / 100.0;
	else
		*val = ft_atoi(nb);
	return (free(nb), true);
}

float	convert_to_float_bis(char *arr, bool *check)
{
	int		i;
	int		j;
	int		dot;
	char	*nb;
	float	val;

	i = 0;
	j = 0;
	dot = 0;
	nb = malloc(sizeof(char) * (ft_strlen(arr) + 1));
	if (!nb)
	{
		*check = true;
		return (0);
	}
	while (arr[i])
	{
		if (arr[i] == '.')
		{
			dot = 1;
			if (arr[i + 1] && arr[i + 2] != '\0')
				dot++;
			i++;
			continue ;
		}
		nb[j] = arr[i];
		j++;
		i++;
	}
	nb[j] = '\0';
	if (dot == 1)
		val = (float)(ft_atoi(nb)) / 10.0;
	else if (dot == 2)
		val = (float)(ft_atoi(nb)) / 100.0;
	else
		val = (float) ft_atoi(nb);
	return (free(nb), val);
}

bool	convert_to_vect_float(t_vect *val, char *arr, char *arr1, char *arr2)
{
	bool	check;

	check = false;
	(*val)[0] = convert_to_float_bis(arr, &check);
	if (check)
		return (false);
	(*val)[1] = convert_to_float_bis(arr1, &check);
	if (check)
		return (false);
	(*val)[2] = convert_to_float_bis(arr2, &check);
	if (check)
		return (false);
	return(true);
}

bool	convert_to_rgb(t_rgb *rgb, char *arr)
{
	char	**rgb_arr;

	rgb_arr = ft_split(arr, ',');
	if (!rgb_arr)
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

bool	convert_to_vect(t_vect *xyz, char *arr)
{
	char	**xyz_arr;

	xyz_arr = ft_split(arr, ',');
	if (!xyz_arr)
		return (false);
	if (!convert_to_vect_float(&xyz[0], xyz_arr[0], xyz_arr[1], xyz_arr[2]))
		return (free_double_arr(xyz_arr), false);
	return (free_double_arr(xyz_arr), true);
}

bool	convert_to_orientation(t_vect *xyz, char *arr)
{
	char	**xyz_arr;

	xyz_arr = ft_split(arr, ',');
	if (!xyz_arr)
		return (false);
	if (!convert_to_vect_float(xyz, xyz_arr[0], xyz_arr[1], xyz_arr[2]))
		return (free_double_arr(xyz_arr), false);
	return (free_double_arr(xyz_arr), true);
}

