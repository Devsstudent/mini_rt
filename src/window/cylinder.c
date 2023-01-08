/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <mbelrhaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:53:22 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/08 21:12:29 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	copy_sol_two_in_one(t_solution *solu)
{
	solu->sol_one = true;
	solu->sol_two = false;
	solu->one.x = solu->two.x;
	solu->one.y = solu->two.y;
	solu->one.z = solu->two.z;
}

void	check_solution(t_solution *solu, t_cylinder cylinder)
{
	float	radius;
	float	half_height;
	float	distance_max;
	t_xyz	origin;

	origin = cylinder.position;
	radius = cylinder.diameter / 2.0;
	half_height = cylinder.height / 2.0;
	distance_max = sqrtf(powf(radius, 2) + powf(half_height, 2));
	if (solu->sol_one || solu->sol_two)
	{
		if (solu->sol_two)
		{
			if (norm_of_vector(create_vector(solu->two, origin))
				> distance_max)
				solu->sol_two = false;
		}
		if (norm_of_vector(create_vector(solu->one, origin))
			> distance_max)
		{
			solu->sol_one = false;
			if (solu->sol_two)
				copy_sol_two_in_one(solu);
		}
	}
}

bool	get_cylinder(t_objects *obj, t_solution_list **list,
	t_line_eq rayline)
{
	t_equation	quadratic;
	bool		err;
	t_solution	solu;
	int			i;

	i = 0;
	while (i < obj->nb_cy)
	{
		err = false;
		quadratic = get_quadra_cylinder_equation(rayline, obj->cy[i]);
		solu = solution(quadratic, rayline, &err);
		if (err)
			return (false);
		check_solution(&solu, obj->cy[i]);
		get_disc(obj, list, rayline, i);
		if (solu.sol_one
			&& !list_add(list, new_elem(solu, obj->cy[i].color, CY, i)))
			return (false);
		i++;
	}
	return (true);
}

bool	get_specific_cylinder(t_objects *obj, t_solution_list **list,
	t_line_eq rayline, int i_to_view)
{
	t_equation	quadratic;
	bool		err;
	t_solution	solu;

	err = false;
	quadratic = get_quadra_cylinder_equation(rayline, obj->cy[i_to_view]);
	solu = solution(quadratic, rayline, &err);
	if (err)
		return (false);
	check_solution(&solu, obj->cy[i_to_view]);
	get_disc(obj, list, rayline, i_to_view);
	if (solu.sol_one && !list_add(list,
			new_elem(solu, obj->cy[i_to_view].color, CY, i_to_view)))
		return (false);
	return (true);
}
