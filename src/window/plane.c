/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:05:05 by odessein          #+#    #+#             */
/*   Updated: 2023/01/11 15:12:40 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_equation	get_quadra_plan_equation(t_line_eq rayline, t_plane plane)
{
	t_equation	res;
	t_vect		vect_plan;
	t_xyz		p_plan;

	vect_plan = plane.vec_direction;
	p_plan = plane.position;
	res.x_pow_two = 0;
	res.x_pow_one = vect_plan[0] * rayline.x.t + vect_plan[1]
		* rayline.y.t + vect_plan[2] * rayline.z.t;
	res.c = vect_plan[0] * (rayline.x.c - p_plan.x)
		+ vect_plan[1] * (rayline.y.c - p_plan.y)
		+ vect_plan[2] * (rayline.z.c - p_plan.z);
	return (res);
}

static bool	one_solu_plan(t_solution *solu, t_equation eq, t_line_eq equation)
{
	float	solution;

	solution = -1 * eq.c / eq.x_pow_one;
	if (solution < 0.0)
		return (false);
	solu->sol_one = true;
	solu->sol_two = false;
	solu->one.x = equation.x.c + equation.x.t * solution;
	solu->one.y = equation.y.c + equation.y.t * solution;
	solu->one.z = equation.z.c + equation.z.t * solution;
	return (true);
}

static t_solution	solution_plan(t_equation eq, t_line_eq equation,
			bool *error)
{
	t_solution	solution;

	if (!init_solution(&solution))
	{
		*error = true;
		return (solution);
	}
	if (eq.x_pow_one == 0)
	{
		return (solution);
	}
	else
	{
		if (!one_solu_plan(&solution, eq, equation))
			return (solution);
	}
	return (solution);
}

bool	get_plane(t_objects *obj, t_sol_li *list, t_line_eq rayline)
{
	t_equation	quadratic;
	bool		err;
	t_solution	solu;
	int			i;

	i = 0;
	while (i < obj->nb_pl)
	{
		err = false;
		quadratic = get_quadra_plan_equation(rayline, obj->pl[i]);
		solu = solution_plan(quadratic, rayline, &err);
		if (err)
			return (false);
		if (solu.sol_one
			&& !list_add(list, new_elem(solu, obj->pl[i].color, PL, i)))
			return (false);
		i++;
	}
	return (true);
}

bool	get_specific_plane(t_objects *obj, t_sol_li *list,
			t_line_eq rayline, int i_to_view)
{
	t_equation	quadratic;
	bool		err;
	t_solution	solu;

	err = false;
	quadratic = get_quadra_plan_equation(rayline, obj->pl[i_to_view]);
	solu = solution_plan(quadratic, rayline, &err);
	if (err)
		return (false);
	if (solu.sol_one && !list_add(list,
			new_elem(solu, obj->pl[i_to_view].color, PL, i_to_view)))
		return (false);
	return (true);
}
