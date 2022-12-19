/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:51 by odessein          #+#    #+#             */
/*   Updated: 2022/12/19 13:22:22 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	loop_rendering(t_objects *objs, t_viewplan view_plan)
{
	int			i;

	i = 0;
	while (i < WIN_H)
	{
		if (!loop_line(objs, &view_plan, i))
			return (false);
		i++;
	}
	return (true);
}

/*
bool	get_cy(t_obj_cy cy, t_viewplan *viewplpan, t_solution_list *list, t_vect rayvec)
{
	return (true);
}
*/

//Get all quadratic equaton solution and fill the structure solution

//Mettre i et j dans la structure objs pour que ca respecte la norme
bool	resolve_equation(t_objects *objs, t_viewplan *view_plan, t_solution_list **list, t_vect rayvec, int j, int i)
{
	int		color;
	t_xyz	intersec_point;

	color = create_color(objs->amb->color.R, objs->amb->color.G, objs->amb->color.B);
	if (!get_sphere(objs, view_plan, list, rayvec))
		return (false);
	if (!get_plane(objs, view_plan, list, rayvec))
		return (false);
	intersec_point = fill_list_intersection(objs, list);
	if (intersec_point.x == -1 && intersec_point.y == -1 && intersec_point.z == -1)
		return (false);
	//We got the point where to check the color
	//So lets get the equation from it to lights
	if (!get_pixel_color(&color, intersec_point, objs))
		return (false);
	if (list && (*list) && (*list)->solution.sol_one)
		img_pixel_put(objs->mlx, j, i, mlx_get_color_value(objs->mlx->mlx, color));
	//get_cy(objs->cy, view_plan, list, rayvec);
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
		if (!resolve_equation(objs, view_plan, &list, rayvec, j, i))
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

