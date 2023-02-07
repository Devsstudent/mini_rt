/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:21:10 by odessein          #+#    #+#             */
/*   Updated: 2023/01/14 21:56:04 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

float	scalar_product(t_vect one, t_vect two)
{
	return (one[0] * two[0] + one[1] * two[1] + one[2] * two[2]);
}

t_vect	create_vector(t_xyz one, t_xyz two)
{
	t_vect	res;

	res[0] = two.x - one.x;
	res[1] = two.y - one.y;
	res[2] = two.z - one.z;
	return (res);
}

t_vect	get_opposite_vector(t_vect vector)
{
	t_vect	res;

	res = -vector;
	return (res);
}
