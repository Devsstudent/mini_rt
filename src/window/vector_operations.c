/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:27:49 by mbelrhaz          #+#    #+#             */
/*   Updated: 2022/12/14 18:38:51 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

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

t_xyz	get_screen_unit_hor_vect(t_xyz vect_d, t_xyz vect_w, int fov)
{
	float	norm_d;
	t_xyz	normed_w;
	t_xyz	unit_w;
	float	desired_norm;

	norm_d = norm_of_vector(vect_d);
	//tan() takes an angle in radians, conversion is necessary
	desired_norm = (tan((fov * PI / 180.0) / 2) / norm_d);
	normed_w = normalize_vector(vect_w);
	unit_w.x = normed_w.x * desired_norm / (float)(WIN_W * 2.0);
	unit_w.y = normed_w.y * desired_norm / (float)(WIN_W * 2.0);
	unit_w.z = normed_w.z * desired_norm / (float)(WIN_W * 2.0);
	return (unit_w);
}

t_xyz	get_screen_unit_vert_vect(t_xyz unit_w, t_xyz vect_h)
{
	float	desired_norm;
	t_xyz	normed_h;
	t_xyz	unit_h;

	desired_norm = norm_of_vector(unit_w);
	normed_h = normalize_vector(vect_h);
	unit_h.x = normed_h.x * desired_norm;
	unit_h.y = normed_h.y * desired_norm;
	unit_h.z = normed_h.z * desired_norm;
	return (unit_h);
}
