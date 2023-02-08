/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objs_system_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:43:36 by odessein          #+#    #+#             */
/*   Updated: 2023/02/08 13:33:35 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

bool	fill_obj_systems(t_objects *objs)
{
	int	i;

	i = 0;
	if (!fill_cam_system(objs))
		return (false);
	while (i < objs->nb_pl)
		if (!fill_pl_system(objs, i++))
			return (false);
	i = 0;
	while (i < objs->nb_sp)
		if (!fill_sp_system(objs, i++))
			return (false);
	i = 0;
	while (i < objs->nb_cy)
		if (!fill_cy_system(objs, i++))
			return (false);
	return (true);
}
