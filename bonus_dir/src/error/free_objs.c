/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:45:48 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/06 22:51:50 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "error.h"

void	free_objs(t_objects *obj)
{
	if (obj->nb_cy)
		free(obj->cy);
	if (obj->nb_pl)
		free(obj->pl);
	if (obj->nb_sp)
		free(obj->sp);
	if (obj->nb_li)
		free(obj->li);
	free(obj->cam);
	free(obj->amb);
}
