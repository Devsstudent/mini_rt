/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:08:35 by odessein          #+#    #+#             */
/*   Updated: 2022/12/19 13:29:29 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_xyz	fill_list_intersection(t_objects *objs, t_solution_list **list)
{
	t_solution_list	*buff;
	t_xyz			start_point;
	t_xyz			closest_point;
	float			distance;

	closest_point.x = -1;
	closest_point.y = -1;
	closest_point.z = -1;
	distance = -1;
	start_point = objs->cam->position;	
	buff = *list;
	while (buff != NULL)
	{
		if (buff->solution.sol_one)
		{
			printf("??\n");
			if (is_closer(&closest_point, buff->solution.one, start_point, &distance))
				closest_point = *buff->solution.one;
		}
		if (buff->solution.sol_two)
			if (is_closer(&closest_point, buff->solution.two, start_point, &distance))
				closest_point = *buff->solution.two;
		buff = buff->next;
	}
	return (closest_point);
}

bool	get_pixel_color(int *color, t_xyz intersec_point, t_objects *objs)
{
	int	i;
	t_vect	dir_vec;
	t_line_eq	rayline;

	i = 0;
	//Add the ambient color;
	//*color = create_color(ambient)
	while (i < objs->nb_li)
	{
		dir_vec[0] = objs->li[i].position.x - intersec_point.x;
		dir_vec[1] = objs->li[i].position.y - intersec_point.y;
		dir_vec[2] = objs->li[i].position.z - intersec_point.z;
		rayline = get_rayline_eq(dir_vec, intersec_point);
		if (check_shadow(rayline, objs))
			add_color(color, 255, 255 ,255);
		else
			add_color(color, objs->li[i].color.R, objs->li[i].color.G, objs->li[i].color.B);
		i++;
	}
	return (true);
}

bool	is_closer(t_xyz *closest, t_xyz *intersec, t_xyz start_point, float *final_distance)
{
	float	distance;

	(void) closest;
	distance = (powf(start_point.x - intersec->x, 2) + powf(start_point.y - intersec->y, 2) + powf(start_point.z - intersec->z, 2)) / 2;
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
