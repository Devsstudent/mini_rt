/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:05:05 by odessein          #+#    #+#             */
/*   Updated: 2022/12/22 20:32:08 by mbelrhaz         ###   ########.fr       */
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
	res.x_pow_one = vect_plan[0] * rayline.x.t + vect_plan[1] * rayline.y.t + vect_plan[2] * rayline.z.t;
	res.c = vect_plan[0] * (rayline.x.c - p_plan.x)
					+ vect_plan[1] * (rayline.y.c - p_plan.y)
					+ vect_plan[2] * (rayline.z.c - p_plan.z);
	//res.c = vect_plan[0] * p_plan.x + vect_plan[1] * p_plan.y + vect_plan[2] * p_plan.z - (rayline.x.t * rayline.x.c + rayline.y.t * rayline.y.c + rayline.z.t * rayline.z.c);
	return (res);
}

static bool	one_solu_plan(t_solution *solu, t_equation eq, t_line_eq equation)
{
	float	solution;

	solu->sol_one = true;
	solu->sol_one = false;
	solution = -1 * eq.c / eq.x_pow_one;
	solu->one.x = equation.x.c + equation.x.t * solution;
	solu->one.y = equation.y.c + equation.y.t * solution;
	solu->one.z = equation.z.c + equation.z.t * solution;
	return (true);
}

static t_solution	solution_plan(t_equation eq, t_line_eq equation, bool *error)
{
	t_solution	solution;

	if (!init_solution(&solution))
	{
		*error = true;
		//return NULL ?
		return (solution);
	}
	if (eq.x_pow_one == 0)
		return (solution);
	else
	{
		//printf("coco\n");
		if (!one_solu_plan(&solution, eq, equation))
			*error = true;
	}
	return (solution);
}

bool	get_plane(t_objects *obj, t_viewplan *viewplan, t_solution_list **list, t_vect rayvec)
{
	t_line_eq	rayline;
	t_equation	quadratic;
	bool		err;
	t_solution		solu;
	int			i;

	(void) viewplan;
	i = 0;
	while (i < obj->nb_pl)
	{
		err = false;
		rayline = get_rayline_eq(rayvec, obj->cam->position);
		quadratic = get_quadra_plan_equation(rayline, obj->pl[i]);
		solu = solution_plan(quadratic, rayline, &err);
		if (err)
			return (false);
		if (solu.sol_one && !list_add(list, new_elem(solu, obj->pl[i].color, PL)))
			return (false);
		i++;
	}
	return (true);
}
