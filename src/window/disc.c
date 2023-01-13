/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:27:23 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/13 14:18:54 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_equation	get_quadra_disc_equation(t_line_eq rayline, t_cylinder cylinder,
		int i, t_xyz *p_disc, float *radius)
{
	t_equation	res;
	t_vect		vect_disc;
	float		height;

	*radius = cylinder.diameter / 2.0;
	if (i == 0)
		i = 1.0;
	else
		i = -1.0;
	height = cylinder.height / 2.0;
	vect_disc = normalize_vector(cylinder.vec_direction);
	p_disc->x = cylinder.position.x + i * height * vect_disc[0];
	p_disc->y = cylinder.position.y + i * height * vect_disc[1];
	p_disc->z = cylinder.position.z + i * height * vect_disc[2];
	res.x_pow_two = 0;
	res.x_pow_one = vect_disc[0] * rayline.x.t + vect_disc[1] * rayline.y.t
		+ vect_disc[2] * rayline.z.t;
	res.c = vect_disc[0] * (rayline.x.c - p_disc->x)
		+ vect_disc[1] * (rayline.y.c - p_disc->y)
		+ vect_disc[2] * (rayline.z.c - p_disc->z);
	return (res);
}

static bool	one_solu_disc(t_solution *solu, t_equation eq, t_line_eq equation,
		t_xyz p_disc, float radius)
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
	if (norm_of_vector(create_vector(p_disc, solu->one)) > radius)
		solu->sol_one = false;
	return (true);
}

static t_solution	solution_disc(t_equation eq, t_line_eq equation,
		bool *error, t_xyz p_disc, float radius)
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
		if (!one_solu_disc(&solution, eq, equation, p_disc, radius))
			return (solution);
	}
	return (solution);
}

bool	get_disc(t_objects *obj, t_sol_li *list, t_line_eq rayline,
		int i)
{
	bool		err;
	t_solution	solu;
	t_xyz		p_disc;
	float		radius;
	int			j;

	j = 0;
	while (j < 2)
	{
		err = false;
		solu = solution_disc(get_quadra_disc_equation(rayline, obj->cy[i],
					j, &p_disc, &radius), rayline, &err, p_disc, radius);
		if (err)
			return (false);
		if (solu.sol_one
			&& !list_add(list, new_elem(solu, obj->cy[i].color, CY, i)))
			return (false);
		j++;
	}
	return (true);
}
