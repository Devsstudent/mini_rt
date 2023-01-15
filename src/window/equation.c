/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:27:37 by odessein          #+#    #+#             */
/*   Updated: 2023/01/15 22:05:50 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	one_solu(t_solution *solu, t_equation eq, t_line_eq equation)
{
	float	delta;

	delta = (-1 * eq.x_pow_one) / (2 * eq.x_pow_two);
	if (delta < 0.0)
		return (true);
	solu->sol_one = true;
	solu->sol_two = false;
	solu->one.x = equation.x.c + equation.x.t * delta;
	solu->one.y = equation.y.c + equation.y.t * delta;
	solu->one.z = equation.z.c + equation.z.t * delta;
	return (true);
}

void	copy_solu_two_in_one(t_solution *solu)
{
	solu->sol_one = true;
	solu->sol_two = false;
	solu->one.x = solu->two.x;
	solu->one.y = solu->two.y;
	solu->one.z = solu->two.z;
}

bool	two_solu(t_solution *solu, t_equation eq, t_line_eq equation)
{
	float	a;
	float	b;
	float	delta;

	if (!eq.x_pow_two)
		return (false);
	delta = (eq.x_pow_one * eq.x_pow_one) - 4 * (eq.x_pow_two * eq.c);
	a = (-eq.x_pow_one - sqrtf(delta)) / (2 * eq.x_pow_two);
	solu->sol_one = true;
	solu->sol_two = true;
	solu->one.x = equation.x.c + equation.x.t * a;
	solu->one.y = equation.y.c + equation.y.t * a;
	solu->one.z = equation.z.c + equation.z.t * a;
	b = (-eq.x_pow_one + sqrtf(delta)) / (2 * eq.x_pow_two);
	if (a < 0.0)
		solu->sol_one = false;
	if (b < 0.0)
		solu->sol_two = false;
	solu->two.x = equation.x.c + equation.x.t * b;
	solu->two.y = equation.y.c + equation.y.t * b;
	solu->two.z = equation.z.c + equation.z.t * b;
	if (solu->sol_one == false && solu->sol_two == true)
		copy_solu_two_in_one(solu);
	return (true);
}

bool	init_solution(t_solution *solution)
{
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
		return (solution);
	}
	delta = eq.x_pow_one * eq.x_pow_one - 4 * (eq.x_pow_two * eq.c);
	if (delta < 0)
		return (solution);
	else if (delta == 0 || eq.x_pow_two == 0)
	{
		if (!one_solu(&solution, eq, equation))
			*error = true;
	}
	else
	{
		if (!two_solu(&solution, eq, equation))
			*error = true;
	}
	return (solution);
}
