/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:34:49 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 11:41:27 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	init_all_elem(t_must_have *all_elem)
{
	all_elem->ambient = false;
	all_elem->camera = false;
	all_elem->object = false;
}

bool	check_all_elem(t_must_have all_elem)
{
	if (!all_elem.ambient || !all_elem.camera || !all_elem.object)
		return (false);
	return (true);
}
