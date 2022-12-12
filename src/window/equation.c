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

float	one_solu(t_equation eq)
{
	return ((-eq.x_pow_two / (2 * eq.x_pow_one)));
}

float	first_solut(t_equation eq, float res)
{
	float	a;

	a = (-eq.x_pow_one + sqrtf(res));
	if (a == 0)
		return (0);
	float	b;
	b = a / (2 * eq.x_pow_two);
	return (b);
}

float	second_solu(t_equation eq, float res)
{
	float	a;

	a = (-eq.x_pow_one - sqrtf(res));
	if (a == 0)
		return (0);
	float	b;
	b = a / (2 * eq.x_pow_two);
	return (b);
}

bool	solution(t_equation eq)
{
	float	res;

	res = (eq.x_pow_one * eq.x_pow_one) - 4 * (eq.x_pow_two * eq.c);
	if (res < 0)
		return (false);
	else if (res == 0)
		return (true);
		//1 soltion
	else
		return (true);
		//2 solution
	return (false);
}
