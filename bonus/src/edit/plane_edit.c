/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:05:40 by odessein          #+#    #+#             */
/*   Updated: 2023/02/05 20:40:47 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

void	apply_action_pl(t_edit edit_info, t_plane *pl)
{
	if (edit_info.action == TRANSLATE)
	{
		pl->position.x = edit_info.coord.x;
		pl->position.y = edit_info.coord.y;
		pl->position.z = edit_info.coord.z;
	}
	else if (edit_info.action == ROTATE)
	{
		pl->vec_direction = apply_rotation(pl->vec_direction,
				edit_info.axis, edit_info.angle);
		pl->vec_width = apply_rotation(pl->vec_width,
				edit_info.axis, edit_info.angle);
		pl->vec_height = apply_rotation(pl->vec_height,
				edit_info.axis, edit_info.angle);
	}
}

bool	ask_pl(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit	edit_info;
	t_plane	*pl;
	bool	exit_request;

	exit_request = false;
	if (objs->nb_pl == 0)
		return (ft_putstr_fd("No planes, sorry :(\n", 1), true);
	nb = 0;
	type = PL;
	while (nb > INT_MAX || nb > objs->nb_pl || nb <= 0)
	{
		nb = get_input_nb_int("Which plane do you want to select ?\n",
				&exit_request);
		if (exit_request == true)
			return (false);
	}
	edit_info = get_edit(type, &exit_request);
	if (exit_request == true)
		return (false);
	pl = &objs->pl[nb - 1];
	apply_action_pl(edit_info, pl);
	return (true);
}
