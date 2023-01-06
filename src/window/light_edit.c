/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:06:19 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 17:25:42 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

bool	ask_li(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit		edit_info;

	type = LI;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_li || nb <= 0)
		nb = get_input_nb("Which light do you want to select ?\n");
	edit_info = get_edit(type);
	(void) edit_info;
	return (true);
}
