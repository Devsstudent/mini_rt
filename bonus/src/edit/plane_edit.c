/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:05:40 by odessein          #+#    #+#             */
/*   Updated: 2023/01/26 23:56:24 by mbelrhaz         ###   ########.fr       */
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

	if (objs->nb_pl == 0)
	{
		ft_putstr_fd("No planes, sorry : ( \n", 1);
		return (true);
	}
	nb = 0;
	type = PL;
	while (nb > INT_MAX || nb > objs->nb_pl || nb <= 0)
		nb = get_input_nb("Which plane do you want to select ?\n");
	edit_info = get_edit(type);
	pl = &objs->pl[nb - 1];
	apply_action_pl(edit_info, pl);
	return (true);
}
