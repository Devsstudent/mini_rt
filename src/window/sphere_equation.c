/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_equation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:05:56 by odessein          #+#    #+#             */
/*   Updated: 2023/01/10 16:15:33 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static void	fill_vec_from_z(t_vect *vertical, t_vect original_pos)
{
	(*vertical)[1] = (-((2) * original_pos[0]) / original_pos[2]
			- ((4 * original_pos[1]) / original_pos[2]));
	(*vertical)[0] = 2;
	(*vertical)[2] = 4;
}

static void	fill_vec_from_y(t_vect *vertical, t_vect original_pos)
{
	(*vertical)[2] = (-((2) * original_pos[0]) / original_pos[2]
			- ((4 * original_pos[1]) / original_pos[2]));
	(*vertical)[0] = 2;
	(*vertical)[1] = 4;
}

static void	fill_vec_from_x(t_vect *vertical, t_vect original_pos)
{
	(*vertical)[0] = (-((2) * original_pos[0]) / original_pos[2]
			- ((4 * original_pos[1]) / original_pos[2]));
	(*vertical)[1] = 2;
	(*vertical)[2] = 4;
}

t_vect	get_vec_vertical(t_vect original_pos)
{
	t_vect	res;

	ft_memset(&res, 0, sizeof(res));
	if (original_pos[0] == 0 && original_pos[1] == 0 && original_pos[2] == 0)
	{
		ft_putstr_fd("Not possible to get the orthogonal vector\n", 2);
		return (res);
	}
	if (original_pos[0] == 0 && original_pos[1] == 0 && original_pos[2] > 0)
	{
		res[1] = 1;
		return (res);
	}
	if (original_pos[2] != 0)
		fill_vec_from_z(&res, original_pos);
	else if (original_pos[1] != 0)
		fill_vec_from_y(&res, original_pos);
	else if (original_pos[0] != 0)
		fill_vec_from_x(&res, original_pos);
	return (res);
}

t_vect	get_vec_horizontal(t_vect v_director, t_vect v_ortho)
{
	t_vect	res;

	if (v_director[0] == 0 && v_director[1] == 0 && v_director[2] > 0
		&& v_ortho[0] == 0 && v_ortho[1] > 0 && v_ortho[2] == 0)
	{
		res[0] = 1;
		res[1] = 0;
		res[2] = 0;
	}
	res[0] = v_director[1] * v_ortho[2] - v_director[2] * v_ortho[1];
	res[1] = v_director[2] * v_ortho[0] - v_director[0] * v_ortho[2];
	res[2] = v_director[0] * v_ortho[1] - v_director[1] * v_ortho[0];
	return (res);
}
