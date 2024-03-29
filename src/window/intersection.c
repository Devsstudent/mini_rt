/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:08:35 by odessein          #+#    #+#             */
/*   Updated: 2023/01/29 20:11:05 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_xyz	get_point(t_xyz	intersec, t_vect rayvec, t_xyz start_point)
{
	t_xyz	res;

	res.x = start_point.x + rayvec[0] * intersec.x;
	res.y = start_point.y + rayvec[1] * intersec.y;
	res.z = start_point.z + rayvec[2] * intersec.z;
	return (res);
}

static void	fill_disp_point(t_solution_elem *buff,
			t_disp_point *disp_point, bool two)
{
	ft_memset(disp_point, 0, sizeof(*disp_point));
	if (!two)
		disp_point->intersec_point = buff->solution.one;
	else
		disp_point->intersec_point = buff->solution.two;
	disp_point->color = buff->color;
	disp_point->type = buff->type;
	disp_point->tex = buff->tex;
	disp_point->obj_id = buff->obj_id;
}

t_disp_point	get_intersection(t_sol_li *list,
					t_xyz start_point)
{
	t_solution_elem	*buff;
	t_disp_point	disp_point;
	float			distance;

	disp_point.intersec_point.x = -1;
	disp_point.intersec_point.y = -1;
	disp_point.intersec_point.z = -1;
	disp_point.err = false;
	distance = -1;
	buff = list->head;
	while (buff != NULL)
	{
		if (buff->solution.sol_one)
			if (is_closer(buff->solution.one, start_point, &distance))
				fill_disp_point(buff, &disp_point, 0);
		if (buff->solution.sol_two)
			if (is_closer(buff->solution.two, start_point, &distance))
				fill_disp_point(buff, &disp_point, 1);
		buff = buff->next;
	}
	return (disp_point);
}

bool	is_closer(t_xyz intersec, t_xyz start_point, float *final_distance)
{
	float	distance;

	distance = ((start_point.x - intersec.x) * (start_point.x - intersec.x)
			+ (start_point.y - intersec.y) * (start_point.y - intersec.y)
			+ (start_point.z - intersec.z) * (start_point.z - intersec.z)) / 2;
	if (distance >= -0.1 && distance <= 0.1)
		return (false);
	if (*final_distance == -1)
	{
		*final_distance = distance;
		return (true);
	}
	else if (distance < *final_distance)
	{
		*final_distance = distance;
		return (true);
	}
	return (false);
}
