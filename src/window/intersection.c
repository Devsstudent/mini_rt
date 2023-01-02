/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:08:35 by odessein          #+#    #+#             */
/*   Updated: 2023/01/02 17:26:00 by mbelrhaz         ###   ########.fr       */
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

t_disp_point	fill_list_intersection(t_solution_list **list, t_xyz start_point)
{
	t_solution_list	*buff;
	t_disp_point	disp_point;
	float			distance;

	disp_point.intersec_point.x = -1;
	disp_point.intersec_point.y = -1;
	disp_point.intersec_point.z = -1;
	distance = -1;
	buff = *list;
	while (buff != NULL)
	{
		if (buff->solution.sol_one)
		{
			if (is_closer(buff->solution.one, start_point, &distance))
			{
				disp_point.intersec_point = buff->solution.one;
				disp_point.color = buff->color;
				disp_point.type = buff->type;
				disp_point.obj_id = buff->obj_id;
			}
		}
		if (buff->solution.sol_two)
		{
			if (is_closer(buff->solution.two, start_point, &distance))
			{
				disp_point.intersec_point = buff->solution.two;
				disp_point.color = buff->color;
				disp_point.type = buff->type;
				disp_point.obj_id = buff->obj_id;
			}
		}
		buff = buff->next;
	}
	return (disp_point);
}

/*bool	get_pixel_color(int *color, t_disp_point disp_p, t_objects *objs)
{
	int			i;
//	t_vect		dir_vec;
//	t_line_eq	rayline;
//	t_rgb		rgb;

	i = 0;
//	rgb.R = 255;
//	rgb.G = 255;
//	rgb.B = 255;
	*color = create_color(disp_p.color);
	//Add the ambient color;
	// *color = create_color(ambient)
	while (i < objs->nb_li)
	{
	//	dir_vec[0] = objs->li[i].position.x - disp_p.intersec_point.x;
	//	dir_vec[1] = objs->li[i].position.y - disp_p.intersec_point.y;
	//	dir_vec[2] = objs->li[i].position.z - disp_p.intersec_point.z;
//		rayline = get_rayline_eq(dir_vec, disp_p.intersec_point);
	//	if (check_shadow(rayline, objs))
	//		add_color(color, rgb);
	//	else
	//		add_color(color, objs->li[i].color);
		i++;
	}
	return (true);
}*/

bool	is_closer(t_xyz intersec, t_xyz start_point, float *final_distance)
{
	float	distance;

	distance = (powf(start_point.x - intersec.x, 2) + powf(start_point.y - intersec.y, 2) + powf(start_point.z - intersec.z, 2)) / 2;
	if (distance >= -0.001 && distance <= 0.001)
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
	//printf("buff : %f new : %f\n", *final_distance, distance);
	return (false);
}
