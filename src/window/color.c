/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:03:54 by odessein          #+#    #+#             */
/*   Updated: 2022/12/28 23:42:42 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	create_color(t_rgb rgb, float RGB[3])
{
	int	color;
	t_color	color_conv;

	color_conv.rgb = rgb;
	color_conv.rgb.T = 0;
	color_conv.rgb.R = (uint8_t)trunc((float)color_conv.rgb.R * RGB[0]);
	color_conv.rgb.G = (uint8_t)trunc((float)color_conv.rgb.G * RGB[0]);
	color_conv.rgb.B = (uint8_t)trunc((float)color_conv.rgb.B * RGB[0]);
	color = color_conv.color;
	return (color);
}

void	ambient_light_quo(t_objects *objs, float RGB[3])
{
	RGB[0] = (float)objs->amb->color.R * objs->amb->ratio / 255.0;
	RGB[1] = (float)objs->amb->color.G * objs->amb->ratio / 255.0;
	RGB[2] = (float)objs->amb->color.B * objs->amb->ratio / 255.0;
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
	//should not just be PL but is there a way from the camera to the light that does't intersect object,
	// so it should be a specific object, we should know which one, keep it in memory
	//the thing it intersects has a max value, if not, it's alright
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
	rayvec[2] = objs->li[0].position.z - objs->cam->position.z;
	rayline = get_rayline_eq(rayvec, objs->cam->position);
	if (point.type == SP && !get_specific_sphere(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	if (point.type == PL && !get_specific_plane(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	if (point.type == CY && !get_specific_cylinder(objs, &list, rayline, point.obj_id))
		return (free_list(&list), -1);
	intersection = fill_list_intersection(&list, objs->cam->position);
	if (list != NULL && list->solution.sol_one && in_the_way(intersection.intersec_point, rayvec, objs->cam->position))
		return (free_list(&list), 0);
	free_list(&list);
	return (1);
}

void	compute_RGB(t_objects *objs, float distance, float RGB[3])
{
	float	ratio;

	ratio = objs->li[0].ratio - distance / 1000.0;
	if (ratio < 0.0)
		ratio = 0.0;
	RGB[0] += (float)objs->li[0].color.R * ratio / 255.0;
	RGB[1] += (float)objs->li[0].color.G * ratio / 255.0;
	RGB[2] += (float)objs->li[0].color.B * ratio / 255.0;
	if (RGB[0] > 1.0)
		RGB[0] = 1.0;
	if (RGB[1] > 1.0)
		RGB[1] = 1.0;
	if (RGB[2] > 1.0)
		RGB[2] = 1.0;
}

void	get_rayvec_light(t_objects *objs, t_xyz point, t_vect *rayvec, int i)
{
	(*rayvec)[0] = objs->li[i].position.x - point.x;
	(*rayvec)[1] = objs->li[i].position.y - point.y;
	(*rayvec)[2] = objs->li[i].position.z - point.z;
}

bool	add_light(t_disp_point disp_p, t_objects *objs, float RGB[3])
{
	t_line_eq		rayline;
	t_solution_list	*list;
	t_vect			rayvec;
	int				way_to_the_light;
	int				obj_id_sphere;
	int				obj_id_plane;
	int				obj_id_cylinder;
	t_disp_point	intersection;
	int		i;

	i = 0;
	while (i < objs->nb_li)
	{
		list = malloc(sizeof(t_solution_list));
		if (!list)
			return (false);
		list = NULL;
		way_to_the_light = 0;
		get_rayvec_light(objs, disp_p.intersec_point, &rayvec, i);
		//du coup il faut connaitre lui meme
		//ca revient au meme probleme
		//lets go
		//le probleme se pose lorsqu'il s'intersecte avec lui-meme
		rayline = get_rayline_eq(rayvec, disp_p.intersec_point);
		obj_id_plane = -1;
		obj_id_sphere = -1;
		obj_id_cylinder = -1;
		if (disp_p.type == PL)
			obj_id_plane = disp_p.obj_id; 
		else if (disp_p.type == SP)
			obj_id_sphere = disp_p.obj_id;
		else
			obj_id_cylinder = disp_p.obj_id;
		if (!get_sphere(objs, &list, rayline, obj_id_sphere))
			return (false);
		if (!get_plane(objs, &list, rayline, obj_id_plane))
			return (false);
		if (!get_cylinder(objs, &list, rayline, obj_id_cylinder))
			return (false);
		intersection = fill_list_intersection(&list, disp_p.intersec_point);
		//we can put it outside, cause if intersect self in one setting, so no good ?
		way_to_the_light = intersect_self(objs, disp_p, i);
		if (way_to_the_light == -1)
			return (false);
		//les -1 pas bien parce que ca pourrait etre -1
		if (list != NULL && in_the_way(intersection.intersec_point, rayvec, disp_p.intersec_point))
			return (true);
		else if (way_to_the_light == 0)
				return (true);
		//there is a way to the light, now let's calculate the distance the compute the intensity of the light
		//distance between disp_p and light
		//distance is norm of rayvec
		compute_RGB(objs, norm_of_vector(rayvec), RGB);
		free_list(&list);
		i++;
	}
	return (true);
}

bool	get_pixel_color(int *color, t_disp_point disp_p, t_objects *objs)
{
	t_rgb	color_rgb;
	float	RGB[3];

	RGB[0] = 0;
	RGB[1] = 0;
	RGB[2] = 0;
	color_rgb.R = disp_p.color.R;
	color_rgb.G = disp_p.color.G;
	color_rgb.B = disp_p.color.B;
	ambient_light_quo(objs, RGB);
	add_light(disp_p, objs, RGB);
	*color = create_color(color_rgb, RGB);
	return (true);
}
