/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:03:54 by odessein          #+#    #+#             */
/*   Updated: 2023/01/03 17:34:19 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	create_color(t_rgb rgb, float rgb_val[3])
{
	int		color;
	t_color	color_conv;

	color_conv.rgb = rgb;
	color_conv.rgb.T = 0;
	color_conv.rgb.R = (uint8_t)trunc((float)color_conv.rgb.R * rgb_val[0]);
	color_conv.rgb.G = (uint8_t)trunc((float)color_conv.rgb.G * rgb_val[1]);
	color_conv.rgb.B = (uint8_t)trunc((float)color_conv.rgb.B * rgb_val[2]);
	color = color_conv.color;
	return (color);
}

void	ambient_light_quo(t_objects *objs, float rgb[3])
{
	rgb[0] = (float)objs->amb->color.R * objs->amb->ratio / 255.0;
	rgb[1] = (float)objs->amb->color.G * objs->amb->ratio / 255.0;
	rgb[2] = (float)objs->amb->color.B * objs->amb->ratio / 255.0;
}

bool	in_the_way(t_xyz point, t_vect rayvec, t_xyz origin)
{
	t_vect	vect;

	vect[0] = point.x - origin.x;
	vect[1] = point.y - origin.y;
	vect[2] = point.z - origin.z;
	if (norm_of_vector(vect) > norm_of_vector(rayvec))
		return (false);
	return (true);
}

int	intersect_self(t_objects *objs, t_disp_point point, int i)
{
	t_line_eq		rayline;
	t_solution_list	*list;
	t_vect			rayvec;
	t_disp_point	intersection;

	list = malloc(sizeof(t_solution_list));
	if (!list)
		return (false);
	list = NULL;
	rayvec[0] = objs->li[i].position.x - objs->cam->position.x;
	rayvec[1] = objs->li[i].position.y - objs->cam->position.y;
	rayvec[2] = objs->li[i].position.z - objs->cam->position.z;
	rayline = get_rayline_eq(rayvec, objs->cam->position);
	if (point.type == SP
		&& !get_specific_sphere(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	if (point.type == PL
		&& !get_specific_plane(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	if (point.type == CY
		&& !get_specific_cylinder(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	intersection = fill_list_intersection(&list, objs->cam->position);
	if (list != NULL && list->solution.sol_one
		&& in_the_way(intersection.intersec_point, rayvec, objs->cam->position))
		return (free_list(&list), 0);
	free_list(&list);
	return (1);
}

void	compute_rgb(t_objects *objs, float distance, float rgb[3], int i)
{
	float	ratio;

	ratio = objs->li[i].ratio - distance / 1000.0;
	if (ratio < 0.0)
		ratio = 0.0;
	rgb[0] += (float)objs->li[i].color.R * ratio / 255.0;
	rgb[1] += (float)objs->li[i].color.G * ratio / 255.0;
	rgb[2] += (float)objs->li[i].color.B * ratio / 255.0;
	if (rgb[0] > 1.0)
		rgb[0] = 1.0;
	if (rgb[1] > 1.0)
		rgb[1] = 1.0;
	if (rgb[2] > 1.0)
		rgb[2] = 1.0;
}

void	get_rayvec_light(t_objects *objs, t_xyz point, t_vect *rayvec, int i)
{
	(*rayvec)[0] = objs->li[i].position.x - point.x;
	(*rayvec)[1] = objs->li[i].position.y - point.y;
	(*rayvec)[2] = objs->li[i].position.z - point.z;
}

t_disp_point	error_intersec(void)
{
	t_disp_point	res;

	res.err = true;
	return (res);
}

t_disp_point	check_light_shadow(t_disp_point disp_p, t_objects *objs,
					int i, t_solution_list *list)
{
	t_line_eq		rayline;
	t_vect			rayvec;

	get_rayvec_light(objs, disp_p.intersec_point, &rayvec, i);
	rayline = get_rayline_eq(rayvec, disp_p.intersec_point);
	if (!get_sphere(objs, &list, rayline, -1))
		return (error_intersec());
	if (!get_plane(objs, &list, rayline, -1))
		return (error_intersec());
	if (!get_cylinder(objs, &list, rayline, -1))
		return (error_intersec());
	return (fill_list_intersection(&list, disp_p.intersec_point));
}

bool	check_no_shadow(t_disp_point intersection, t_disp_point initial,
			t_objects *objs, int i)
{
	t_vect			rayvec;
	int				way_to_the_light;

	way_to_the_light = 0;
	way_to_the_light = intersect_self(objs, initial, i);
	if (way_to_the_light == -1)
		return (false);
	get_rayvec_light(objs, initial.intersec_point, &rayvec, i);
	if (intersection.intersec_point.x != -1
		&& intersection.intersec_point.y != -1
		&& intersection.intersec_point.z != -1
		&& in_the_way(intersection.intersec_point, rayvec, initial.intersec_point))
		return (true);
	else if (way_to_the_light == 0)
		return (true);
	return (false);
}

bool	loop_light(t_disp_point disp_p, t_objects *objs, float rgb[3])
{
	int					i;
	t_solution_list		*list;
	t_disp_point		intersection;
	t_vect				rayvec;

	i = -1;
	while (++i < objs->nb_li)
	{
		list = malloc(sizeof(t_solution_list));
		if (!list)
			return (false);
		list = NULL;
		intersection = check_light_shadow(disp_p, objs, i, list);
		if (intersection.err)
			return (free_list(&list), false);
		if (check_no_shadow(intersection, disp_p, objs, i))
		{
			(free_list(&list));
			continue ;
		}
		get_rayvec_light(objs, disp_p.intersec_point, &rayvec, i);
		compute_rgb(objs, norm_of_vector(rayvec), rgb, i);
		free_list(&list);
	}
	return (true);
}

bool	get_pixel_color(int *color, t_disp_point disp_p, t_objects *objs)
{
	t_rgb	color_rgb;
	float	rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	color_rgb.R = disp_p.color.R;
	color_rgb.G = disp_p.color.G;
	color_rgb.B = disp_p.color.B;
	ambient_light_quo(objs, rgb);
	loop_light(disp_p, objs, rgb);
	*color = create_color(color_rgb, rgb);
	return (true);
}
