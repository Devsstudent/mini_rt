/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:12:31 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 20:28:39 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

static void	axis_x(void *new_vec, double _cos, double _sin, t_vect initial)
{
	t_vect	*res;

	res = (t_vect *) new_vec;
	(*res)[0] = initial[0];
	(*res)[1] = initial[1] * _cos - initial[2] * _sin;
	(*res)[2] = initial[1] * _sin + initial[2] * _cos;
}

static void	axis_y(void *new_vec, double _cos, double _sin, t_vect initial)
{
	t_vect	*res;

	res = (t_vect *) new_vec;
	(*res)[0] = initial[2] * _sin + initial[0] * _cos;
	(*res)[1] = initial[1];
	(*res)[2] = initial[2] * _cos - initial[0] * _sin;
}

static void	axis_z(void *new_vec, double _cos, double _sin, t_vect initial)
{
	t_vect	*res;

	res = (t_vect *) new_vec;
	(*res)[0] = initial[0] * _cos - initial[1] * _sin;
	(*res)[1] = initial[0] * _sin + initial[1] * _cos;
	(*res)[2] = initial[2];
}

t_vect	apply_rotation(t_vect initial, t_axis axis, int angle)
{
	t_vect	res;
	double	_cos;
	double	_sin;

	_sin = sin(((float) angle) * (M_PI / 180));
	_cos = cos(((float) angle) * (M_PI / 180));
	memset(&res, 0, sizeof(res));
	if (axis == X)
		axis_x(&res, _cos, _sin, initial);
	else if (axis == Y)
		axis_y(&res, _cos, _sin, initial);
	else if (axis == Z)
		axis_z(&res, _cos, _sin, initial);
	else
		printf("AHAHAHHA ERROR TO HANDLE :)\n");
	return (res);
}
