/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:34:52 by odessein          #+#    #+#             */
/*   Updated: 2023/02/01 20:43:11 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static bool	fill_normal_specular(t_disp_point intersec,
				t_objects *objs, t_vect *normal)
{
	if (intersec.type == SP)
		*normal = normalize_vector(get_normal_vect_sp(intersec, objs));
	else if (intersec.type == PL)
		*normal = normalize_vector(get_normal_vect_pl(intersec, objs));
	else if (intersec.type == CY)
		*normal = normalize_vector(get_normal_vect_cy(intersec, objs));
	else if (intersec.type == DI)
		*normal = normalize_vector(get_normal_vect_di(intersec, objs, 1));
	else if (intersec.type == CO_DI)
		*normal = normalize_vector(get_normal_vect_di(intersec, objs, 0));
	else if (intersec.type == CO)
		*normal = normalize_vector(get_normal_vect_co(intersec, objs));
	else
		return (false);
	return (true);
}

float	get_specular(t_vect light_vec, t_disp_point intersec, t_objects *objs)
{
	int		shy;
	float	ks;
	t_vect	view_line;
	t_vect	normal;
	t_vect	reflected;

	ft_memset(&normal, 0, sizeof(normal));
	if (!fill_normal_specular(intersec, objs, &normal))
		return (false);
	ks = 0.4;
	shy = 9;
	reflected = normalize_vector(2 * (scalar_product(normal,
					normalize_vector(light_vec)) * normal)
			- normalize_vector(light_vec));
	view_line = normalize_vector(create_vector(intersec.intersec_point,
				objs->cam->position));
	return (ks * pow(fmax(scalar_product(view_line, reflected), 0), shy));
}
