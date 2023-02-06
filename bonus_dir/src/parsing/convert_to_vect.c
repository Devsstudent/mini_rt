/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_vect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:31:03 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/04 17:48:31 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

static void	remove_dot(char *arr, char *nb, int *dot)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i])
	{
		if (arr[i] == '.')
		{
			*dot = 1;
			if (arr[i + 1] && arr[i + 2] != '\0')
				(*dot)++;
			i++;
			continue ;
		}
		nb[j] = arr[i];
		j++;
		i++;
	}
	nb[j] = '\0';
}

float	convert_to_float_bis(char *arr, bool *check)
{
	int		dot;
	char	*nb;
	float	val;

	dot = 0;
	nb = malloc(sizeof(char) * (ft_strlen(arr) + 1));
	if (!nb)
	{
		*check = true;
		return (0);
	}
	remove_dot(arr, nb, &dot);
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
	return (true);
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
