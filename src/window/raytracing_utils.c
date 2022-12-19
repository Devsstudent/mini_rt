/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:06:16 by odessein          #+#    #+#             */
/*   Updated: 2022/12/19 12:06:40 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_vect	multp(t_vect vector, int t)
{
	t_vect	res;

	res = vector * (float) t;
	return (res);
}

t_line_eq	get_rayline_eq(t_vect vec_line, t_xyz start_point)
{
	t_line_eq	res;

	res.x.c = start_point.x;
	res.x.t = vec_line[0];
	res.y.c = start_point.y;
	res.y.t = vec_line[1];
	res.z.c = start_point.z;
	res.z.t = vec_line[2];
	return (res);
}

t_vect	get_vector(t_vect up_left, t_vect hori, t_vect verti)
{
	t_vect	res;

	res = up_left + hori + verti;
	return (res);
}

t_vect	get_up_left(t_vect hori, t_vect verti, t_vect orient)
{
	t_vect	h_v_o;

	h_v_o = hori * (WIN_W / 2) + verti * (WIN_H / 2) + orient;
	return (h_v_o);
}
