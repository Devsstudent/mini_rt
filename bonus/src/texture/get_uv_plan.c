/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:25:18 by odessein          #+#    #+#             */
/*   Updated: 2023/01/26 13:37:25 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "texture.h"

void	get_uv_plan(t_plane *pl)
{
	pl->uv.v = normalize_vector(get_vec_vertical(pl->vec_direction));
	pl->uv.u = normalize_vector(get_vec_horizontal(pl->vec_direction, pl->uv.v));
}

//On part la position du point du plan et on applique comme si c'etati le centre de l'image.
