/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:27:49 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/10 16:21:27 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

t_vect	vector_product(t_vect vector_1, t_vect vector_2)
{
	t_vect	res;

	res = vector_1 * vector_2 - vector_1 * vector_2;
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
	res = vector * ((float)(1.0 / norm));
	return (res);
}

t_vect	get_screen_unit_hor_vect(t_vect vect_d, t_vect vect_w, int fov)
{
	float	norm_d;
	t_vect	normed_w;
	t_vect	unit_w;
	float	desired_norm;

	norm_d = norm_of_vector(vect_d);
	desired_norm = (tan((fov * PI / 180.0) / 2) / norm_d);
	normed_w = normalize_vector(vect_w);
	unit_w = normed_w * (desired_norm / (float)(WIN_W * 2.0));
	return (unit_w);
}

t_vect	get_screen_unit_vert_vect(t_vect unit_w, t_vect vect_h)
{
	float	desired_norm;
	t_vect	normed_h;
	t_vect	unit_h;

	desired_norm = norm_of_vector(unit_w);
	normed_h = normalize_vector(vect_h);
	unit_h = normed_h * desired_norm;
	return (unit_h);
}
