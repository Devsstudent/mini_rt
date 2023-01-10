/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:50:44 by odessein          #+#    #+#             */
/*   Updated: 2023/01/09 15:31:16 by odessein         ###   ########.fr       */
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
}

bool	ask_sp(t_objects *objs)
{
	t_type		type;
	long		nb;
	t_sphere	*sp;
	t_edit		edit_info;

	type = SP;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_sp || nb <= 0)
		nb = get_input_nb("Which sphere do you want to select ?\n");
	edit_info = get_edit(type);
	sp = &objs->sp[nb - 1];
	apply_action_sp(edit_info, sp);
	return (true);
}
