/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_edit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:04:54 by odessein          #+#    #+#             */
/*   Updated: 2023/01/06 17:25:05 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "edit.h"

bool	ask_cy(t_objects *objs)
{
	t_type	type;
	long	nb;
	t_edit		edit_info;
	t_cylinder	*cy;

	if (objs->nb_cy == 0)
	{
		//I guess i the end we should INVALID MAP if not 1 cylinder & 1 sphere & 1 plane
		ft_putstr_fd("No cylinder sorry :(\n", 1);
		return (true);
	}
	type = CY;
	nb = 0;
	while (nb > INT_MAX || nb > objs->nb_cy || nb <= 0)
		nb = get_input_nb("Which cylinder do you want to select ?\n");
	cy = &objs->cy[nb];
	edit_info = get_edit(type);
	if (edit_info.action == RESIZE)
		cy->height = edit_info.height;
	if (edit_info.action == RESIZE_WIDTH)
		cy->height = edit_info.width;
	return (true);
}
