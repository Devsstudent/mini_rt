/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:05:40 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 17:25:54 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

bool	ask_pl(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit		edit_info;

	nb = 0;
	type = PL;
	while (nb > INT_MAX || nb > objs->nb_pl || nb <= 0)
		nb = get_input_nb("Which plane do you want to select ?\n");
	edit_info = get_edit(type);
	(void) edit_info;
	return (true);
}
