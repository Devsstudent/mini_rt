/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:27:49 by mbelrhaz          #+#    #+#             */
/*   Updated: 2022/12/10 21:57:25 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

t_xyz	get_orthogonal_vect(t_xyz vector)
{
	float	unknow;
	t_xyz	res;

	res.x = 0;
	res.y = 0;
	res.z = 0;
	if (vector.x == 0 && vector.y == 0 && original_pos.z == 0)
	{
		ft_putstr_fd(2, "Not possible to get the orthogonal vector\n");
		return (res);
	}
	if (vector.z != 0)
	{
		unknow = vector.z;
		res.z = (-((2) * vector.x) / original_pos.z - (( 4 * original_pos.y) / original_pos.z));
		res.x = 2;
		res.y = 4;
	}
	else if (vector.y != 0)
	{
		res.y = (-((2) * vector.x) / original_pos.y - (( 4 * original_pos.z) / original_pos.y));
		res.x = 2;
		res.z = 4;
	}
	else if (vector.x != 0)
	{
		res.x = (-((2) * vector.y) / original_pos.x - (( 4 * original_pos.z) / original_pos.x));
		res.y = 2;
		res.z = 4;
	}
	return (res);
}

t_xyz	get_opposite_vector(t_xyz vector)
{
	t_xyz	res;

	res.x = -vector.x;
	res.y = -vector.y;
	res.z = -vector.z;
	return (res);
}

t_xyz	vector_product(t_xyz vector_1, t_xyz vector_2)
{
	t_xyz	res;

	res.x = vector_1.y * vector_2.z - vector_1.z * vector_2.y;
	res.y = vector_1.z * vector_2.x - vector_1.x * vector_2.z;
	res.z = vector_1.x * vector_2.y - vector_1.y * vector_2.x;
	return (res);
}

float	norm_of_vector(t_xyz vector)
{
	float	res;

	res = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return (res);
}

t_xyz	normalize_vector(t_xyz vector)
{
	t_xyz	res;
	float	norm;

	norm = norm_of_vector(vector);
	res.x = vector.x * (1.0 / norm);
	res.y = vector.y * (1.0 / norm);
	res.z = vector.z * (1.0 / norm);
	return (res);
}

t_xyz	get_screen_unit_hor_vect(t_xyz vect_d, t_xyz vect_w, int fov, int screen_width)
{
	float	norm_d;
	t_xyz	normed_w;
	t_xyz	unit_w;
	float	desired_norm;

	norm_d = norm_of_vector(vect_d);
	desired_norm = tan(fov) / norm_d;
	normed_w = normalize_vector(vect_w);
	unit_w.x = normed_w.x * desired_norm / (float)screen_width;
	unit_w.y = normed_w.y * desired_norm / (float)screen_width;
	unit_w.z = normed_w.z * desired_norm / (float)screen_width;
	return (unit_w);
}

void	normalizing(t_xyz *vector, float vector_norm, float window_scale)
{
	if (window_scale == 0 || vector_norm == 0)
	{
		ft_putstr_fd("Error dividing by zero in normalizing\n", 2);
		return ;
	}
	vector->x = (vector->x / (window_scale * vector_norm));
	vector->y = (vector->y / (window_scale * vector_norm));
	vector->z = (vector->z / (window_scale * vector_norm));
}


