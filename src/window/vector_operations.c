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

t_vect	get_opposite_vector(t_vect vector)
{
	t_vect	res;

	res[0] = -vector[0];
	res[1] = -vector[1];
	res[2] = -vector[2];
	return (res);
}

t_vect	vector_product(t_vect vector_1, t_vect vector_2)
{
	t_vect	res;

	res[0] = vector_1[0] * vector_2[0] - vector_1[0] * vector_2[0];
	res[1] = vector_1[1] * vector_2[1] - vector_1[1] * vector_2[1];
	res[2] = vector_1[2] * vector_2[2] - vector_1[2] * vector_2[2];
	return (res);
}

float	norm_of_vector(t_vect vector)
{
	float	res;

	res = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
	return (res);
}

t_vect	normalize_vector(t_vect vector)
{
	t_vect	res;
	float	norm;

	norm = norm_of_vector(vector);
	res[0] = vector[0] * (1.0 / norm);
	res[1] = vector[1] * (1.0 / norm);
	res[2] = vector[2] * (1.0 / norm);
	return (res);
}

t_vect	get_screen_unit_hor_vect(t_vect vect_d, t_vect vect_w, int fov)
{
	float	norm_d;
	t_vect	normed_w;
	t_vect	unit_w;
	float	desired_norm;

	norm_d = norm_of_vector(vect_d);
	//tan() takes an angle in radians, conversion is necessary
	desired_norm = (tan((fov * PI / 180.0) / 2) / norm_d);
	normed_w = normalize_vector(vect_w);
	unit_w[0] = normed_w[0] * desired_norm / (float)(WIN_W * 2.0);
	unit_w[1] = normed_w[1] * desired_norm / (float)(WIN_W * 2.0);
	unit_w[2] = normed_w[2] * desired_norm / (float)(WIN_W * 2.0);
	return (unit_w);
}

t_vect	get_screen_unit_vert_vect(t_vect unit_w, t_vect vect_h)
{
	float	desired_norm;
	t_vect	normed_h;
	t_vect	unit_h;

	desired_norm = norm_of_vector(unit_w);
	normed_h = normalize_vector(vect_h);
	unit_h[0] = normed_h[0] * desired_norm;
	unit_h[1] = normed_h[1] * desired_norm;
	unit_h[2] = normed_h[2] * desired_norm;
	return (unit_h);
}
