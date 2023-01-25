/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:10:17 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 12:34:55 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "matrix.h"

t_matrix	get_mx_rotate(float angle)
{
	t_matrix	mx;

	angle = angle * M_PI / 180;
	mx[0][0] = 1;
	mx[1][1] = cosf(angle);
	mx[2][1] = sinf(angle);
	mx[2][2] = cosf(angle);
	mx[1][2] = -sinf(angle);
	mx[3][3] = 1;
}

t_matrix	get_my_rotate(float angle)
{
	t_matrix	my;

	angle = angle * M_PI / 180;
	my[0][0] = cosf(angle);
	my[0][2] = sinf(angle);
	my[1][2] = 1;
	my[2][0] = cosf(angle);
	my[3][3] = 1;
}

t_matrix	get_mz_rotate(void)
{
	t_matrix	mz;

	angle = angle * M_PI / 180;
	mz[0][0] = cosf(angle);
	mz[0][1] = -sinf(angle);
	mz[1][0] = sinf(angle);
	mz[1][1] = cosf(angle);
	mz[2][2] = 1;
	mz[3][3] = 1;
}
