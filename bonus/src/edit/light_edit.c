/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:06:19 by odessein          #+#    #+#             */
/*   Updated: 2023/02/05 20:41:32 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

void	apply_action_li(t_edit edit_info, t_light *li)
{
	if (edit_info.action == TRANSLATE)
	{
		li->position.x = edit_info.coord.x;
		li->position.y = edit_info.coord.y;
		li->position.z = edit_info.coord.z;
	}
}

bool	ask_li(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit	edit_info;
	t_light	*li;
	bool	exit_request;

	if (objs->nb_li == 0)
		return (ft_putstr_fd("No lights sorry :(\n", 1), true);
	type = LI;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_li || nb <= 0)
	{
		nb = get_input_nb_int("Which light do you want to select ?\n",
				&exit_request);
		if (exit_request == true)
			return (false);
	}
	edit_info = get_edit(type, &exit_request);
	if (exit_request == true)
		return (false);
	li = &objs->li[nb - 1];
	apply_action_li(edit_info, li);
	return (true);
}
