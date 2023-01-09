/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:12:31 by odessein          #+#    #+#             */
/*   Updated: 2023/01/09 15:59:14 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

t_vect	apply_rotation(t_vect initial, t_axis axis, int angle)
{
	t_vect	res;
	double	_cos;
	double	_sin;

	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	_sin = sin(((float) angle) * (PI / 180));
	_cos = cos(((float) angle) * (PI / 180));
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
	return (res);
}
