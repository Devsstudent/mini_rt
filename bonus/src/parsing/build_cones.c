/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:00:02 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 18:08:19 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

bool	build_cones(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = count_obj(triple_arr, "co");
	objects->co = malloc(sizeof(t_cone) * size);
	if (!objects->co)
		return (false);
	objects->nb_co = size;
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "co", i))
		{
			if (!fill_cones(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}