/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:34:49 by odessein          #+#    #+#             */
/*   Updated: 2023/01/10 15:21:43 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	init_all_elem(t_must_have *all_elem)
{
	all_elem->ambient = false;
	all_elem->camera = false;
	all_elem->object = false;
	all_elem->light_maj = false;
	all_elem->light = false;
}

bool	check_all_elem(t_must_have all_elem)
{
	if (!all_elem.ambient || !all_elem.camera || !all_elem.object)
		return (false);
	return (true);
}
