/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:51 by odessein          #+#    #+#             */
/*   Updated: 2022/12/27 23:32:50 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	loop_rendering(t_objects *objs, t_viewplan view_plan)
{
	int	i;

	i = 0;
	if (first > 0)
		return (true);
	while (i < WIN_H)
	{
		if (!loop_line(objs, &view_plan, i))
			return (false);
		i++;
	}
	mlx_put_image_to_window(objs->mlx->mlx, objs->mlx->win, objs->mlx->img, 0, 0);
	first++;
	return (true);
}

//Mettre i et j dans la structure objs pour que ca respecte la norme
bool	resolve_equation(t_objects *objs, t_solution_list **list, t_vect rayvec, int j, int i)
{
	int				color;
	t_line_eq		rayline;
	t_disp_point	intersec_point;

	rayline = get_rayline_eq(rayvec, objs->cam->position);
	color = 0;
	if (!get_sphere(objs, list, rayline, -1))
		return (false);
	if (!get_plane(objs, list, rayline, -1))
		return (false);
	intersec_point = fill_list_intersection(list, objs->cam->position);
	if (intersec_point.intersec_point.x == -1 && intersec_point.intersec_point.y == -1 && intersec_point.intersec_point.z == -1)
		return (true);
	if (!get_pixel_color(&color, intersec_point, objs))
		return (false);
	if (list && (*list) && (*list)->solution.sol_one)
	{
		//mlx_pixel_put(objs->mlx->mlx, objs->mlx->win,j, i, color);
		img_pixel_put(objs->mlx, j, i, color);
	}
	//loop on elem checking equation;
	free_list(list);
	return (true);
}

	//If solution , find the closest one of the camera then check light then putpixel of color combo
	//if (!get_ligth(objs, view_plan, list, rayvec))
		
	//Light_ray for each intersection (not the second of the sphere) to define color
	//If one intersection on the sphere (Edge) we could make a combo of pixel arround 
	//Stop check_intersecton after a plan .

bool	loop_line(t_objects *objs, t_viewplan *view_plan, int i)
{
	int				j;
	t_solution_list			*list;
	t_vect			rayvec;

	j = 0;
	list = malloc(sizeof(t_solution_list));
	if (!list)
		return (false);
	list = NULL;
	while (j < WIN_W)
	{
		rayvec = get_vector(view_plan->up_left, multp(get_opposite_vector(view_plan->hori), j), multp(get_opposite_vector(view_plan->verti), i));
		if (!resolve_equation(objs, &list, rayvec, j, i))
			return (false);
		j++;
	}
	return (true);
}

//STOCKER LES POINTS D'intersection dans une liste chainee ?

//FUNCTION A DECOUPER :
/*
void	loop(t_mlx_info *mlx, t_vect hori, t_vect verti, t_xyz start_point, t_vect orient, t_objectss *objs)
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
*/

