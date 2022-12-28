/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:53:22 by mbelrhaz          #+#    #+#             */
/*   Updated: 2022/12/28 23:47:43 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_equation	get_quadra_cylinder_equation(t_line_eq rayline, t_cylinder cylinder)
{
	t_equation	res;
	float		radius;
	t_vect		vec_cyl;
	t_xyz		origin;
	float		a, b, c;
	float		i, j, k;
	float		xm, ym, zm;
	float		xp, yp, zp;

	origin = cylinder.position;
	vec_cyl = cylinder.vec_direction;
	radius = cylinder.diameter / 2.0;
	a = vec_cyl[0];
	b = vec_cyl[1];
	c = vec_cyl[2];
	i = rayline.x.t;
	j = rayline.y.t;
	k = rayline.z.t;
	xp = rayline.x.c;
	yp = rayline.y.c;
	zp = rayline.z.c;
	xm = origin.x;
	ym = origin.y;
	zm = origin.z;
	//a of the equation
	res.x_pow_two = powf(k, 2) * (powf(b, 2) + powf(a, 2)) + powf(i, 2) 
* (powf(c, 2) + powf(b, 2)) + powf(j, 2) * (powf(c, 2) + powf(a, 2)) - 2 * 
b * c * k * j - 2 * a * c * i * k - 2 * a * b * j * i;

	//b of the equation
	res.x_pow_one = 2 * k * zp * (powf(b, 2) + powf(a, 2)) + 2 * j * yp
* (powf(c, 2) + powf(a, 2)) + 2 * i * xp * (powf(c, 2) + powf(b, 2)) + k
* (-2 * powf(b, 2) * zm + 2 * b * c * ym + 2 * a * c * xm - 2 * powf(a, 2) * zm)
 + j * (2 * b * c * zm - 2 * powf(c, 2) * ym - 2 * powf(a, 2) * ym + 2 * a * b 
* xm) + i * (-2 * powf(c, 2) * xm + 2 * a * c * zm + 2 * a * b * ym - 2 
* powf(b, 2) * xm) - 2 * b * c * (k * yp + j * zp) - 2 * a * c 
* (i * zp + k * xp) - 2 * a * b * (j * xp + i * yp);

	//c of the equation
	res.c = -1 * powf(radius, 2) * (powf(a, 2) + powf(b, 2) + powf(c, 2))
+ powf(b, 2) * (powf(zm, 2) + powf(xm, 2)) + powf(c, 2) * (powf(ym, 2) + powf(xm, 2)) + powf(a, 2) * (powf(zm, 2) + powf(ym, 2)) - 2 * b * c * zm * ym 
- 2 * a * c * zm * xm - 2 * a * b * ym * xm + powf(zp, 2) * (powf(b, 2) + powf(a, 2)) + powf(yp, 2) * (powf(c, 2) + powf(a, 2)) + powf(xp, 2) * (powf(c, 2) + powf(b, 2))
+ zp * (-2 * powf(b, 2) * zm + 2 * b * c * ym + 2 * a * c * xm - 2 
* powf(a, 2) * zm) + yp * (2 * b * c * zm - 2 * ym * powf(c, 2) - 2 * powf(a, 2)
* ym + 2 * a * b * xm) + xp * (-2 * powf(c, 2) * xm + 2 * a * c * zm + 2 * a * b * ym - 2 * powf(b, 2) * xm) - 2 * b * c * zp * yp - 2 * a * c * xp * zp - 2 * a * b * yp * xp;

	return (res);
}

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
			if (norm_of_vector(create_vector(solu->two, origin)) > distance_max)
				solu->sol_two = false;
		}
		if (norm_of_vector(create_vector(solu->one, origin)) > distance_max)
		{
			solu->sol_one = false;
			if (solu->sol_two)
				copy_sol_two_in_one(solu);
		}
	}
}

bool	get_cylinder(t_objects *obj, t_solution_list **list, t_line_eq rayline, int i_to_exclude)
{
	t_equation	quadratic;
	bool		err;
	t_solution	solu;
	int			i;

	i = 0;
	while (i < obj->nb_cy)
	{
		if (i == i_to_exclude)
		{
			i++;
			continue ;
		}
		err = false;
		quadratic = get_quadra_cylinder_equation(rayline, obj->cy[i]);
		printf("a = %f b = %f c = %f, i = %d\n", quadratic.x_pow_two, quadratic.x_pow_one, quadratic.c, i);
		solu = solution(quadratic, rayline, &err);
		if (!solu.sol_one && !solu.sol_two)
			printf("meh\n");
		if (err)
			return (false);
		check_solution(&solu, obj->cy[i]);
		if (solu.sol_one && !list_add(list, new_elem(solu, obj->cy[i].color, CY, i)))
			return (false);
		i++;
	}
	return (true);
}

bool	get_specific_cylinder(t_objects *obj, t_solution_list **list, t_line_eq rayline, int i_to_view)
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
	if (solu.sol_one && !list_add(list, new_elem(solu, obj->cy[i_to_view].color, CY, i_to_view)))
		return (false);
	return (true);
}
