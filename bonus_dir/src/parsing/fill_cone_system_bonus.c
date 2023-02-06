/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cone_system_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:29:46 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/06 20:32:15 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

bool	fill_co_system(t_objects *objs, int i)
{
	t_cone	*co;

	co = &(objs->co[i]);
	if (!co->vec_dir[0] && !co->vec_dir[1]
		&& !co->vec_dir[2])
		return (false);
	co->vec_height = normalize_vector(co->vec_dir);
	co->vec_width = normalize_vector(get_vec_vertical(co->vec_height));
	co->vec_depth = normalize_vector(get_vec_horizontal(co->vec_height,
				co->vec_width));
	return (true);
}
