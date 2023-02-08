/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:12:29 by odessein          #+#    #+#             */
/*   Updated: 2023/02/07 19:26:19 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

bool	in_the_way(t_xyz point, t_vect rayvec, t_xyz origin)
{
	t_vect	vect;

	vect[0] = point.x - origin.x;
	vect[1] = point.y - origin.y;
	vect[2] = point.z - origin.z;
	if (norm_of_vector(vect) > norm_of_vector(rayvec))
		return (false);
	return (true);
}

void	get_rayvec_light(t_objects *objs, t_xyz point, t_vect *rayvec, int i)
{
	(*rayvec)[0] = objs->li[i].position.x - point.x;
	(*rayvec)[1] = objs->li[i].position.y - point.y;
	(*rayvec)[2] = objs->li[i].position.z - point.z;
}

//check_no_shadow checks if the point is illuminated from our point of view
//it checks if there is a way from the camera to the light
//it also checks if the closest intersection is before the point resulting
//in a shadow or if it is after the point resulting in an illuminated point
bool	check_no_shadow(t_disp_point intersection, t_disp_point initial,
			t_objects *objs, int i)
{
	t_vect			rayvec;
	int				way_to_the_light;

	way_to_the_light = 0;
	way_to_the_light = intersect_self(objs, initial, i);
	if (way_to_the_light == -1)
		return (false);
	get_rayvec_light(objs, initial.intersec_point, &rayvec, i);
	if (intersection.intersec_point.x != -1
		&& intersection.intersec_point.y != -1
		&& intersection.intersec_point.z != -1
		&& in_the_way(intersection.intersec_point,
			rayvec, initial.intersec_point))
		return (true);
	else if (way_to_the_light == 0)
		return (true);
	return (false);
}
