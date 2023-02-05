/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:50:44 by odessein          #+#    #+#             */
/*   Updated: 2023/02/05 23:36:40 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

void	apply_action_sp(t_edit edit_info, t_sphere *sp)
{
	if (edit_info.action == RESIZE)
		sp->diameter = edit_info.diameter;
	else if (edit_info.action == TRANSLATE)
	{
		sp->position.x = edit_info.coord.x;
		sp->position.y = edit_info.coord.y;
		sp->position.z = edit_info.coord.z;
	}
	else if (edit_info.action == ROTATE)
	{
		sp->vec_depth = apply_rotation(sp->vec_depth,
				edit_info.axis, edit_info.angle);
		sp->vec_width = apply_rotation(sp->vec_width,
				edit_info.axis, edit_info.angle);
		sp->vec_height = apply_rotation(sp->vec_height,
				edit_info.axis, edit_info.angle);
	}
}

bool	ask_sp(t_objects *objs)
{
	t_type		type;
	long		nb;
	t_sphere	*sp;
	t_edit		edit_info;
	bool		exit_request;

	exit_request = false;
	if (objs->nb_sp == 0)
		return (ft_putstr_fd("No sphere sorry :(\n", 1), true);
	type = SP;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_sp || nb <= 0)
	{
		nb = get_input_nb_int("✴️  Which sphere do you want to select ?\n",
				&exit_request);
		if (exit_request == true)
			return (false);
	}
	edit_info = get_edit(type, &exit_request);
	if (exit_request == true)
		return (false);
	sp = &objs->sp[nb - 1];
	apply_action_sp(edit_info, sp);
	return (true);
}
