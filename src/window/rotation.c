/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:12:31 by odessein          #+#    #+#             */
/*   Updated: 2023/01/09 18:29:20 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

t_vect	apply_rotation(t_vect initial, t_axis axis, int angle)
{
	t_vect	res;
	double	_cos;
	double	_sin;
	if (angle < 0)
	{
		angle = angle * -1;
		_sin = -sin(((float) angle) * (PI / 180));
		_cos = -cos(((float) angle) * (PI / 180));
	}
	else
	{
		_sin = -sin(((float) angle) * (PI / 180));
		_cos = -cos(((float) angle) * (PI / 180));
	}
	if (axis == X)
	{
		res[0] = initial[0];
		res[1] = initial[1] * _cos - initial[2] * _sin;
		res[2] = initial[1] * _sin + initial[2] * _cos;
	}
	else if (axis == Y)
	{
		res[0] = initial[2] * _sin +  initial[0] * _cos;
		res[1] = initial[1];
		res[2] = initial[1] * _cos - initial[0] * _sin;
	}
	else if (axis == Z)
	{
		res[0] = initial[0] * _cos - initial[1] * _sin;
		res[1] = initial[0] * _sin + initial[1] * _cos;
		res[2] = initial[2];
	}
	else
		printf("AHAHAHHA ERROR TO HANDLE :)\n");
	printf("%f, %f, %f\n", res[0], res[1], res[2]);
	return (res);
}

t_xyz	apply_rotation_pos(t_xyz initial, t_axis axis, int angle)
{
	t_xyz	res;
	double	_cos;
	double	_sin;

	res.x = 0;
	res.y = 0;
	res.z = 0;
	_sin = sin(((float) angle) * (PI / 180));
	_cos = cos(((float) angle) * (PI / 180));
	if (axis == X)
	{
		res.x = initial.x;
		res.y = initial.y * _cos - initial.z * _sin;
		res.z = initial.y * _sin + initial.z * _cos;
	}
	else if (axis == Y)
	{
		res.x = initial.z * _sin +  initial.x * _cos;
		res.y = initial.y;
		res.z = initial.y * _cos - initial.x * _sin;
	}
	else if (axis == Z)
	{
		res.x = initial.x * _cos - initial.y * _sin;
		res.y = initial.x * _sin + initial.y * _cos;
		res.z = initial.z;
	}
	else
		printf("AHAHAHHA ERROR TO HANDLE :)\n");
	return (res);
}
