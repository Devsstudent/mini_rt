/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:00:39 by odessein          #+#    #+#             */
/*   Updated: 2023/02/07 00:07:45 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

void	check_solution_cone(t_solution *solu, t_cone cone)
{
	float	distance_max;
	t_xyz	origin;

	origin = cone.position;
	distance_max = sqrtf(cone.radius * cone.radius + cone.height * cone.height);
	if (solu->sol_one || solu->sol_two)
	{
		if (solu->sol_two)
		{
			if (norm_of_vector(create_vector(solu->two, origin)) > distance_max
				|| scalar_product(create_vector(origin, solu->two)
					, cone.vec_dir) < 0)
				solu->sol_two = false;
		}
		if (norm_of_vector(create_vector(solu->one, origin)) > distance_max
			|| scalar_product(create_vector(origin, solu->one)
				, cone.vec_dir) < 0)
		{
			solu->sol_one = false;
			if (solu->sol_two)
				copy_sol_two_in_one(solu);
		}
	}
}

bool	get_cones(t_objects *obj, t_sol_li *list, t_line_eq rayline)
{
	t_equation		quadra;
	bool			err;
	t_solution		solu;
	int				i;
	t_new_elem_info	info;

	i = 0;
	while (i < obj->nb_co)
	{
		err = false;
		quadra = get_quadra_cone_equation(rayline, obj->co[i]);
		solu = solution(quadra, rayline, &err);
		if (err)
			return (false);
		fill_info(&info, obj->co[i].color, i, obj->co[i].tex);
		info.type = CO;
		check_solution_cone(&solu, obj->co[i]);
		get_disc_cone(obj, list, rayline, i);
		if (solu.sol_one
			&& !list_add(list, new_elem(solu, info)))
			return (false);
		i++;
	}
	return (true);
}

bool	get_specific_cone(t_objects *obj, t_sol_li *list,
			t_line_eq rayline, int i_to_view)
{
	t_equation		quadra;
	bool			err;
	t_solution		solu;
	t_new_elem_info	info;

	err = false;
	quadra = get_quadra_cone_equation(rayline, obj->co[i_to_view]);
	solu = solution(quadra, rayline, &err);
	if (err)
		return (false);
	fill_info(&info, obj->co[i_to_view].color,
		i_to_view, obj->co[i_to_view].tex);
	info.type = CO;
	check_solution_cone(&solu, obj->co[i_to_view]);
	get_disc_cone(obj, list, rayline, i_to_view);
	if (solu.sol_one && !list_add(list,
			new_elem(solu, info)))
		return (false);
	return (true);
}
