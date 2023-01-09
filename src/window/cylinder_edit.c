/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_edit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:54 by odessein          #+#    #+#             */
/*   Updated: 2023/01/09 15:30:54 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

void	apply_action_cy(t_edit edit_info, t_cylinder *cy)
{
	if (edit_info.action == RESIZE)
		cy->height = edit_info.height;
	else if (edit_info.action == RESIZE_WIDTH)
	{
		cy->diameter = edit_info.width;
		cy->radius = cy->diameter / 2.0;
		cy->radius_2 = cy->radius * cy->radius;
	}
	else if (edit_info.action == TRANSLATE)
	{
		cy->position.x = edit_info.coord.x;
		cy->xm_2[0] = cy->position.x * cy->position.x;
		cy->position.y = edit_info.coord.y;
		cy->xm_2[1] = cy->position.y * cy->position.y;
		cy->position.z = edit_info.coord.z;
		cy->xm_2[2] = cy->position.z * cy->position.z;
	}
	else if (edit_info.action == ROTATE)
		cy->vec_direction = apply_rotation(cy->vec_direction, edit_info.axis, edit_info.angle);
}

bool	ask_cy(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit		edit_info;
	t_cylinder	*cy;

	if (objs->nb_cy == 0)
	{
		//I guess i the end we should INVALID MAP if not 1 cylinder & 1 sphere & 1 plane
		ft_putstr_fd("No cylinder sorry :(\n", 1);
		return (true);
	}
	type = CY;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_cy || nb <= 0)
		nb = get_input_nb("Which cylinder do you want to select ?\n");
	cy = &objs->cy[nb - 1];
	edit_info = get_edit(type);
	apply_action_cy(edit_info, cy);
	return (true);
}
