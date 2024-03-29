/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cones_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:58:06 by odessein          #+#    #+#             */
/*   Updated: 2023/02/07 00:06:24 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

bool	fill_cones(char **arr, int j, t_objects *objs)
{
	ft_memset(&objs->co[j], 0, sizeof(objs->co[j]));
	if (!convert_to_xyz(&objs->co[j].position, arr[1]))
		return (false);
	if (!convert_to_orientation(&objs->co[j].vec_dir, arr[2]))
		return (false);
	if (!convert_to_float(&objs->co[j].radius, arr[3]))
		return (false);
	if (!convert_to_float(&objs->co[j].height, arr[4]))
		return (false);
	if (!convert_to_rgb(&objs->co[j].color, arr[5]))
		return (false);
	if (arr[6] && !check_texture(&objs->co[j].tex, arr[6], objs))
		return (false);
	return (true);
}
