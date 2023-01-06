/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:50:44 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 19:39:50 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

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
	if (edit_info.action == RESIZE)
		sp->diameter = edit_info.diameter;
//	apply_action_sp(edit_info, &objs->sp[nb]);
	return (true);
}
