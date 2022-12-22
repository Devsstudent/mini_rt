/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:27:37 by odessein          #+#    #+#             */
/*   Updated: 2022/12/22 20:18:22 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	one_solu(t_solution *solu, t_equation eq, t_line_eq equation)
{
	float	delta;

	//cense etre -b / 2a, pas delta donc
	//delta = powf(eq.x_pow_one, 2)  - 4 * (eq.x_pow_two * eq.c);
	delta = (-1 * eq.x_pow_one) / (2 * eq.x_pow_two);
	solu->sol_one = true;
	solu->sol_two = false;
	solu->one.x = equation.x.c + equation.x.t * delta;
	solu->one.y = equation.y.c + equation.y.t * delta;
	solu->one.z = equation.z.c + equation.z.t * delta;
//	float	distance;
//	distance = (powf(-10 - solu->one.x, 2) + powf(15 - solu->one.y, 2) + powf(-100 - solu->one.z, 2)) / 2;
//	printf("dist plan %f\n", distance);
	return (true);
}

bool	two_solu(t_solution *solu, t_equation eq, t_line_eq equation)
{
	float	a;
	float	b;
	float	delta;

	if (!eq.x_pow_one || !eq.x_pow_two)
		return (false);
	delta = (eq.x_pow_one * eq.x_pow_one) - 4 * (eq.x_pow_two * eq.c);
	a = (-eq.x_pow_one - sqrtf(delta)) / (2 * eq.x_pow_two);
	solu->sol_one = true;
	solu->sol_two = true;
	solu->one.x = equation.x.c + equation.x.t * a;
	solu->one.y = equation.y.c + equation.y.t * a;
	solu->one.z = equation.z.c + equation.z.t * a;
	b = (-eq.x_pow_one + sqrtf(delta)) / (2 * eq.x_pow_two);
	solu->two.x = equation.x.c + equation.x.t * b;
	solu->two.y = equation.y.c + equation.y.t * b;
	solu->two.z = equation.z.c + equation.z.t * b;
	float	distance;
	distance = (powf(-10 - solu->one.x, 2) + powf(15 - solu->one.y, 2) + powf(-100 - solu->one.z, 2)) / 2;
//	printf("dist ?%f\n", distance);
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
		//return NULL ?
		return (solution);
	}
	delta = powf(eq.x_pow_one, 2) - 4 * (eq.x_pow_two * eq.c);
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
