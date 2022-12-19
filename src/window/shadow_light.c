/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:12:29 by odessein          #+#    #+#             */
/*   Updated: 2022/12/19 13:09:59 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_shadow(t_line_eq rayline, t_objects *objs)
{
	bool		err;

	err = false;
	//free_exit if err
	if (check_sphere_between(rayline, objs, &err))
		return (true);
	if (!check_plan_between(rayline, objs, &err))
		return (true);
	return (false);
}

bool	check_sphere_between(t_line_eq rayline, t_objects *objs, bool *err)
{
	t_equation	quadratic;
	int			i;
	t_solution	solu;

	i = 0;
	while (i < objs->nb_sp)
	{
		quadratic = get_quadra_sphere_equation(rayline, objs->sp[i]);
		solu = solution(quadratic, rayline, err);
		if (err)
			return (false);
		if (solu.sol_one)
			return (true);
		i++;
	}
	return (false);
}

bool	check_plan_between(t_line_eq rayline, t_objects *objs, bool *err)
{
	t_equation	quadratic;
	int			i;
	t_solution	solu;

	i = 0;
	while (i < objs->nb_sp)
	{
		quadratic = get_quadra_plan_equation(rayline, objs->pl[i]);
		solu = solution(quadratic, rayline, err);
		if (err)
			return (false);
		if (solu.sol_one)
			return (true);
		i++;
	}
	return (false);
}
