/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:51 by odessein          #+#    #+#             */
/*   Updated: 2022/12/16 19:17:34 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

t_vect	multp(t_vect vector, int t)
{
	t_vect	res;

	res = vector * (float) t;
	return (res);
}

t_line_eq	get_rayline_eq(t_vect vec_line, t_xyz start_point)
{
	t_line_eq	res;

	res.x.c = start_point.x;
	res.x.t = vec_line[0];
	res.y.c = start_point.y;
	res.y.t = vec_line[1];
	res.z.c = start_point.z;
	res.z.t = vec_line[2];
	return (res);
}

t_vect	get_vector(t_vect up_left, t_vect hori, t_vect verti)
{
	t_vect	res;

	res = up_left + hori + verti;
	return (res);
}

t_vect	get_up_left(t_vect hori, t_vect verti, t_vect orient)
{
	t_vect	h_v_o;

	h_v_o = hori * (WIN_W / 2) + verti * (WIN_H / 2) + orient;
	return (h_v_o);
}

bool	loop_rendering(t_object *objs, t_viewplan view_plan)
{
	int			i;
	t_vect		ver

	i = 0;
	while (i < WIN_H)
	{
		if (!loop_line(objs, view_plan))
			return (false);
		i++;
	}
	return (true);
}

bool	get_sphere(t_object obj, t_viewplan *viewplpan, t_solution_list *list, t_vect rayvec)
{
	t_line_eq	rayline;
	t_equation	quadratic;
	bool		err;
	t_solution		solu;

	err = false;
	rayline = get_rayline_eq(rayvec, obj->cam->positon);
	quadratic = get_quadra_sphere_equation(rayline, obj);
	solu = solution(quadratic, rayline, &err)
	if (err)
		return (false);
	if (!list_add(list, new_elem(SP, solu)))
		return (false);
	return (true);
}

bool	get_plane(t_object obj, t_viewplan *viewplpan, t_solution_list *list, t_vect rayvec)
{
	t_line_eq	rayline;
	t_equation	quadratic;
	bool		err;
	t_solution		solu;

	err = false;
	rayline = get_rayline_eq(rayvec, obj->cam->positon);
	quadratic = get_quadra_plane_equation(rayline, obj);
	solu = solution(quadratic, rayline, &err)
	if (err)
		return (false);
	if (!list_add(list, new_elem(SP, solu)))
		return (false);
	return (true);
}
/*
bool	get_cy(t_obj_cy cy, t_viewplan *viewplpan, t_solution_list *list, t_vect rayvec)
{
	return (true);
}
*/

//Get all quadratic equaton solution and fill the structure solution
bool	resolve_equation(t_object *objs, t_viewplan *view_plan, t_solution_list *list, t_vect rayvec)
{
	if (!get_sphere(objs, view_plan, list, rayvec))
		return (false);
	if (!get_plan(objs, view_plan, list, rayvec))
		return (false);
	//get_cy(objs->cy, view_plan, list, rayvec);
	//loop on elem checking equation;
	return (true);
}

//

bool	check_intersection(t_viewplan view_plan, t_object *objs, t_solution_list list)
{
	//If solution , find the closest one of the camera then check light then putpixel of color combo
	//if (!get_ligth(objs, view_plan, list, rayvec))
		
	//Light_ray for each intersection (not the second of the sphere) to define color
	//If one intersection on the sphere (Edge) we could make a combo of pixel arround 
	//Stop check_intersecton after a plan .
	return (true);
}

bool	loop_line(t_object *objs, t_viewplan view_plan, int i)
{
	int				j;
	t_solution_list	list;
	t_vect			rayvec;

	j = 0;
	while (j < WIN_W)
	{
		rayvec = get_vector(vect_up_left, multp(get_opposite_vector(view_plan->hori), j), multp(get_opposite_vector(view_plan->verti), i);
		if (!resolve_equation(objs, view_plan, &list, rayvec))
			return (false);
		if (!check_intersection(view_plan, objs, list))
			return (false);
		j++;
	}
	return (true);
}

//STOCKER LES POINTS D'intersection dans une liste chainee ?

//FUNCTION A DECOUPER :
void	loop(t_mlx_info *mlx, t_vect hori, t_vect verti, t_xyz start_point, t_vect orient, t_objects *objs)
{
	t_vect		rayvec;
	t_line_eq	rayline;
	t_equation	quadra;
	t_solution	solu;
	bool		err;

			rayline = get_rayline_eq(rayvec, start_point);
			quadra = get_quadra_plan_equation(rayline, objs);
			err = false;
			solu = solution(quadra, rayline, &err);
			if (err)
				return ;
			if (solu.one || solu.two)
				img_pixel_put(mlx, j, i, mlx_get_color_value(mlx->mlx, 0xABCDEF));
			free(solu.one);
			free(solu.two);
			quadra = get_quadra_sphere_equation(rayline, objs);
			err = false;
			solu = solution(quadra, rayline, &err);
			if (err)
				return ;
			if (solu.sol_one || solu.sol_two)
				img_pixel_put(mlx, j, i, mlx_get_color_value(mlx->mlx, 0x9AE));
			//transposer dans l'equation de l'objet les x,y,z line
			j++;
			free(solu.one);
			free(solu.two);
		}
		i++;
	}
	mlx_put_image_to_window(objs->mlx->mlx, objs->mlx->win, objs->mlx->img, 0, 0);
}

t_equation	get_quadra_plan_equation(t_line_eq rayline, t_objects *objs)
{
	t_equation	res;
	t_vect		vect_plan;
	t_xyz		p_plan;

	vect_plan = objs->pl->vec_direction;
	p_plan = objs->pl->position;
	res.x_pow_two = 0;
	res.x_pow_one = rayline.x.t * vect_plan[0] + rayline.y.t * vect_plan[1] + rayline.z.t * vect_plan[2];
	res.c = vect_plan[0] * p_plan.x + vect_plan[1] * p_plan.y + vect_plan[2] * p_plan.z - (rayline.x.t * rayline.x.c + rayline.y.t * rayline.y.c + rayline.z.t * rayline.z.c);
	return (res);
}

t_equation	get_quadra_sphere_equation(t_line_eq rayline, t_objects *objs)
{
	t_equation	res;
	t_xyz		origin;
	float		rayon;

	origin = objs->sp->position;
	rayon = objs->sp->diameter / 2.0;
	res.x_pow_two = powf(rayline.x.t, 2) + powf(rayline.y.t, 2) + powf(rayline.z.t, 2);
	res.x_pow_one = 2  * (rayline.x.t * (rayline.x.c - origin.x) + rayline.y.t * (rayline.y.c - origin.y) + rayline.z.t * (rayline.z.c - origin.z));
	res.c = powf(origin.x, 2) + powf(origin.y, 2) + powf(origin.z, 2) + powf(rayline.x.c, 2) + powf(rayline.y.c, 2) + powf(rayline.z.c, 2) - 2 * (rayline.x.c * origin.x + rayline.y.c * origin.y + rayline.z.c * origin.z) - powf(rayon, 2);
	return (res);
}
