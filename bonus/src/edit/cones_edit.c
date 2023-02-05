/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:22:49 by odessein          #+#    #+#             */
/*   Updated: 2023/02/05 23:37:13 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

static void	apply_action_co(t_edit edit_info, t_cone *co)
{
	if (edit_info.action == RESIZE)
		co->height = edit_info.height;
	else if (edit_info.action == RESIZE_WIDTH)
		co->radius = edit_info.width;
	else if (edit_info.action == TRANSLATE)
	{
		co->position.x = edit_info.coord.x;
		co->position.y = edit_info.coord.y;
		co->position.z = edit_info.coord.z;
	}
	else if (edit_info.action == ROTATE)
	{
		co->vec_dir = apply_rotation(co->vec_dir, edit_info.axis,
				edit_info.angle);
		co->vec_width = apply_rotation(co->vec_width, edit_info.axis,
				edit_info.angle);
		co->vec_depth = apply_rotation(co->vec_depth, edit_info.axis,
				edit_info.angle);
	}
}

bool	ask_co(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit	edit_info;
	t_cone	*co;
	bool	exit_request;

	exit_request = false;
	if (objs->nb_co == 0)
		return (ft_putstr_fd("No cones sorry :(\n", 1), true);
	type = CO;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_co || nb <= 0)
	{
		nb = get_input_nb_int("✴️  Which cone do you want to select ?\n",
				&exit_request);
		if (exit_request == true)
			return (false);
	}
	co = &objs->co[nb - 1];
	edit_info = get_edit(type, &exit_request);
	if (exit_request == true)
		return (false);
	apply_action_co(edit_info, co);
	return (true);
}
