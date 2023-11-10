/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:23:20 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/03 16:38:46 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	init_build_light(int *i, int *j, char id[2], char ***triple_arr)
{
	int	size;

	*i = 0;
	*j = 0;
	size = count_obj(triple_arr, id);
	if (size == 0)
	{
		id[0] = 'l';
		size = count_obj(triple_arr, id);
	}
	return (size);
}

bool	build_light(char ***triple_arr, t_objects *objects)
{
	int		i;
	int		j;
	int		size;
	char	id[2];

	id[0] = 'L';
	id[1] = '\0';
	size = init_build_light(&i, &j, id, triple_arr);
	objects->li = malloc(sizeof(t_light) * size);
	objects->nb_li = size;
	if (!objects->li)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, id, i))
		{
			if (!fill_light(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
