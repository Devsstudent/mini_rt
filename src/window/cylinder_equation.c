/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_equation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:09:22 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/10 23:45:45 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

/*
	res->x_pow_two = powf(k, 2) * (powf(b, 2) + powf(a, 2)) + powf(i, 2)
* (powf(c, 2) + powf(b, 2)) + powf(j, 2) * (powf(c, 2) + powf(a, 2)) - 2 *
b * c * k * j - 2 * a * c * i * k - 2 * a * b * j * i;
	res.x_pow_one = 2 * k * zp * (powf(b, 2) + powf(a, 2)) + 2 * j * yp
* (powf(c, 2) + powf(a, 2)) + 2 * i * xp * (powf(c, 2) + powf(b, 2)) + k
* (-2 * powf(b, 2) * zm + 2 * b * c * ym + 2 * a * c * xm
- 2 * powf(a, 2) * zm) + j * (2 * b * c * zm - 2
* powf(c, 2) * ym - 2 * powf(a, 2) * ym + 2 * a * b
* xm) + i * (-2 * powf(c, 2) * xm + 2 * a * c * zm + 2 * a * b * ym - 2
* powf(b, 2) * xm) - 2 * b * c * (k * yp + j * zp) - 2 * a * c
* (i * zp + k * xp) - 2 * a * b * (j * xp + i * yp);
	res.c = -1 * powf(radius, 2) * (powf(a, 2) + powf(b, 2) + powf(c, 2))
+ powf(b, 2) * (zm_2 + xm_2) + powf(c, 2) * (ym_2 + xm_2)
+ powf(a, 2) * (zm_2 + ym_2) - 2 * b * c * zm * ym
- 2 * a * c * zm * xm - 2 * a * b * ym * xm + powf(zp, 2)
* (powf(b, 2) + powf(a, 2)) + powf(yp, 2) * (powf(c, 2) + powf(a, 2))
+ powf(xp, 2) * (powf(c, 2) + powf(b, 2))
+ zp * (-2 * powf(b, 2) * zm + 2 * b * c * ym + 2 * a * c * xm - 2
* powf(a, 2) * zm) + yp * (2 * b * c * zm - 2 * ym * powf(c, 2) - 2
* powf(a, 2) * ym + 2 * a * b * xm) + xp * (-2 * powf(c, 2)
* xm + 2 * a * c * zm + 2 * a * b
* ym - 2 * powf(b, 2) * xm) - 2 * b * c * zp * yp - 2 * a
* c * xp * zp - 2 * a * b * yp * xp;
*/

void	get_quadra_a(t_cy_eq cy, t_equation *res)
{
	res->x_pow_two = cy.k_2 * (cy.b_2 + cy.a_2) + cy.i_2 * (cy.c_2 + cy.b_2)
		+ cy.j_2 * (cy.c_2 + cy.a_2) - 2 * cy.b * cy.c * cy.k * cy.j
		- 2 * cy.a * cy.c * cy.i * cy.k - 2 * cy.a * cy.b * cy.j * cy.i;
}

void	get_quadra_b(t_cy_eq cy, t_equation *res)
{
	res->x_pow_one = 2 * cy.k * cy.zp * (cy.b_2 + cy.a_2) + 2 * cy.j * cy.yp
		* (cy.c_2 + cy.a_2) + 2 * cy.i * cy.xp * (cy.c_2 + cy.b_2) + cy.k
		* (-2 * cy.b_2 * cy.zm + 2 * cy.b * cy.c * cy.ym + 2 * cy.a
			* cy.c * cy.xm - 2 * cy.a_2 * cy.zm) + cy.j * (2 * cy.b * cy.c
			* cy.zm - 2 * cy.c_2 * cy.ym - 2 * cy.a_2 * cy.ym + 2 * cy.a
			* cy.b * cy.xm) + cy.i * (-2 * cy.c_2 * cy.xm + 2 * cy.a * cy.c
			* cy.zm + 2 * cy.a * cy.b * cy.ym - 2 * cy.b_2 * cy.xm) - 2
		* cy.b * cy.c * (cy.k * cy.yp + cy.j * cy.zp) - 2 * cy.a
		* cy.c * (cy.i * cy.zp + cy.k * cy.xp) - 2 * cy.a * cy.b
		* (cy.j * cy.xp + cy.i * cy.yp);
}

void	get_quadra_c(t_cy_eq cy, t_equation *res)
{
	res->c = -1 * cy.r_2 * (cy.a_2 + cy.b_2 + cy.c_2) + cy.b_2
		* (cy.zm_2 + cy.xm_2) + cy.c_2 * (cy.ym_2 + cy.xm_2) + cy.a_2
		* (cy.zm_2 + cy.ym_2) - 2 * cy.b * cy.c * cy.zm * cy.ym
		- 2 * cy.a * cy.c * cy.zm * cy.xm - 2 * cy.a * cy.b * cy.ym
		* cy.xm + cy.zp_2 * (cy.b_2 + cy.a_2) + cy.yp_2
		* (cy.c_2 + cy.a_2) + cy.xp_2 * (cy.c_2 + cy.b_2) + cy.zp
		* (-2 * cy.b_2 * cy.zm + 2 * cy.b * cy.c * cy.ym + 2 * cy.a
			* cy.c * cy.xm - 2 * cy.a_2 * cy.zm) + cy.yp * (2 * cy.b
			* cy.c * cy.zm - 2 * cy.ym * cy.c_2 - 2 * cy.a_2 * cy.ym
			+ 2 * cy.a * cy.b * cy.xm) + cy.xp * (-2 * cy.c_2 * cy.xm
			+ 2 * cy.a * cy.c * cy.zm + 2 * cy.a * cy.b * cy.ym
			- 2 * cy.b_2 * cy.xm) - 2 * cy.b * cy.c * cy.zp * cy.yp
		- 2 * cy.a * cy.c * cy.xp * cy.zp - 2 * cy.a * cy.b
		* cy.yp * cy.xp;
}

void	fill_cy_eq_ray(t_line_eq rayline, t_cy_eq *cy_eq)
{
	cy_eq->i = rayline.x.t;
	cy_eq->j = rayline.y.t;
	cy_eq->k = rayline.z.t;
	cy_eq->i_2 = rayline.x.t2;
	cy_eq->j_2 = rayline.y.t2;
	cy_eq->k_2 = rayline.z.t2;
	cy_eq->xp = rayline.x.c;
	cy_eq->yp = rayline.y.c;
	cy_eq->zp = rayline.z.c;
	cy_eq->xp_2 = rayline.x.c2;
	cy_eq->yp_2 = rayline.y.c2;
	cy_eq->zp_2 = rayline.z.c2;
}

t_equation	get_quadra_cylinder_equation(t_line_eq rayline,
	t_cylinder cylinder)
{
	t_equation	res;
	t_cy_eq		cy_eq;

	cy_eq.r = cylinder.radius;
	cy_eq.r_2 = cylinder.radius_2;
	cy_eq.a = cylinder.vec_direction[0];
	cy_eq.b = cylinder.vec_direction[1];
	cy_eq.c = cylinder.vec_direction[2];
	cy_eq.a_2 = cylinder.abc_2[0];
	cy_eq.b_2 = cylinder.abc_2[1];
	cy_eq.c_2 = cylinder.abc_2[2];
	cy_eq.xm = cylinder.position.x;
	cy_eq.ym = cylinder.position.y;
	cy_eq.zm = cylinder.position.z;
	cy_eq.xm_2 = cylinder.xm_2[0];
	cy_eq.ym_2 = cylinder.xm_2[1];
	cy_eq.zm_2 = cylinder.xm_2[2];
	fill_cy_eq_ray(rayline, &cy_eq);
	get_quadra_a(cy_eq, &res);
	get_quadra_b(cy_eq, &res);
	get_quadra_c(cy_eq, &res);
	return (res);
}
