/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:27:37 by odessein          #+#    #+#             */
/*   Updated: 2022/12/12 15:14:16 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	one_solu(t_solution *solu, t_equation eq, t_line_eq equation)
{
	float	delta;

	if (!eq.x_pow_one)
		return (false);
	delta = (-eq.x_pow_two / (2 * eq.x_pow_one));
	solu->sol_one = true;
	solu->sol_two = false;
	solu->one->x = equation.x.c + equation.x.t * delta;
	solu->one->y = equation.y.c + equation.y.t * delta;
	solu->one->z = equation.z.c + equation.z.t * delta;
	return (true);
}

bool	two_solu(t_solution *solu, t_equation eq, t_line_eq equation)
{
	float	a;
	float	b;
	float	delta;

	delta = (-eq.x_pow_two / (2 * eq.x_pow_one));
	if (!eq.x_pow_one || !eq.x_pow_two)
		return (false);
	a = (-eq.x_pow_one - sqrtf(delta)) / (2 * eq.x_pow_two);
	solu->sol_one = true;
	solu->sol_two = true;
	solu->one->x = equation.x.c + equation.x.t * a;
	solu->one->y = equation.y.c + equation.y.t * a;
	solu->one->z = equation.z.c + equation.z.t * a;
	b = (-eq.x_pow_one + sqrtf(delta)) / (2 * eq.x_pow_two);
	solu->two->x = equation.x.c + equation.x.t * b;
	solu->two->y = equation.y.c + equation.y.t * b;
	solu->two->z = equation.z.c + equation.z.t * b;
	return (true);
}

static bool	init_solution(t_solution *solution)
{
	solution->one = malloc(sizeof(t_xyz));
	if (!solution->one)
		return (false);
	solution->two = malloc(sizeof(t_xyz));
	if (!solution->two)
		return (false);
	solution->sol_one = false;
	solution->sol_two = false;
	return (true);
}

t_solution	solution(t_equation eq, t_line_eq equation, bool *error)
{
	float		delta;
	t_solution	solution;

	if (!init_solution(&solution))
	{
		*error = true;
		//return NULL ?
		return (solution);
	}
	delta = (eq.x_pow_one * eq.x_pow_one) - 4 * (eq.x_pow_two * eq.c);
	if (delta < 0)
		return (solution);
	else if (delta == 0)
	{
		if (!one_solu(&solution, eq, equation))
			*error = true;
	}
	else
		if (!two_solu(&solution, eq, equation))
			*error = true;
		//2 solution
	return (solution);
}
