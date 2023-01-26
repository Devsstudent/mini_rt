/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:22:49 by odessein          #+#    #+#             */
/*   Updated: 2023/01/26 09:32:23 by odessein         ###   ########.fr       */
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
		co->vec_dir = apply_rotation(co->vec_dir, edit_info.axis,
			edit_info.angle);
}

bool	ask_co(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit	edit_info;
	t_cone	*co;

	if (objs->nb_co == 0)
	{
		ft_putstr_fd("No cones sorry :(\n", 1);
		return (true);
	}
	type = CO;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_co || nb <= 0)
		nb = get_input_nb("Which cone do you want to select ?\n");	
	co = &objs->co[nb - 1];
	edit_info = get_edit(type);
	apply_action_co(edit_info, co);
	return (true);
}
