/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:03:54 by odessein          #+#    #+#             */
/*   Updated: 2022/12/27 21:48:51 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

int	create_color(t_rgb rgb, float RGB[3])
{
	int	color;

	color = 0;
	color |= (int)trunc((float)rgb.R * RGB[0]);
	color = color << 8;
	color |= (int)trunc((float)rgb.G * RGB[1]);
	color = color << 8;
	color |= (int)trunc((float)rgb.B * RGB[2]);
	return (color);
}

void	add_color(int *color, t_rgb rgb)
{
	*color = (*color << 16 & ((*color << 16) / 2 + rgb.R / 2));
	*color = (*color << 8 & ((*color << 8) / 2 + rgb.G / 2));
	*color = (*color << 0 & ((*color << 0) / 2 + rgb.B / 2));
}

void	ambient_light_quo(t_objects *objs, float RGB[3])
{
	RGB[0] = (float)objs->amb->color.R * objs->amb->ratio / 255.0;
	RGB[1] = (float)objs->amb->color.G * objs->amb->ratio / 255.0;
	RGB[2] = (float)objs->amb->color.B * objs->amb->ratio / 255.0;
}

int	intersect_plane(t_objects *objs)
{
	//should not just be PL but is there a way from the camera to the light that does't intersect said object,
	// so it should be a specific object, we should know which one, keep it in memory
	t_line_eq		rayline;
	t_solution_list	*list;
	t_vect			rayvec;
	t_disp_point	intersection;

	list = malloc(sizeof(t_solution_list));
	if (!list)
		return (false);
	list = NULL;
	rayvec[0] = objs->li[0].position.x - objs->cam->position.x;
	rayvec[1] = objs->li[0].position.y - objs->cam->position.y;
	rayvec[2] = objs->li[0].position.z - objs->cam->position.z;
	rayline = get_rayline_eq(rayvec, objs->cam->position);
	if (!get_sphere(objs, &list, rayline, 0))
		return (-1);
	if (!get_plane(objs, &list, rayline, 0))
		return (-1);
	intersection = fill_list_intersection(objs, &list);
	if (intersection.intersec_point.x != -1 && intersection.intersec_point.y != - 1 && intersection.intersec_point.z != -1 && intersection.type == PL)
		return (0);
	free_list(&list);
	return (1);
}

void	compute_RGB(t_objects *objs, float distance, float RGB[3])
{
	//a chaque 100, -0.1, donc diviser par mille
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

bool	add_light(t_disp_point disp_p, t_objects *objs, float RGB[3])
{
	t_line_eq		rayline;
	t_xyz			point;
	t_solution_list	*list;
	t_vect			rayvec;
	int				way_to_the_light;
	t_disp_point	intersection;

	list = malloc(sizeof(t_solution_list));
	if (!list)
		return (false);
	list = NULL;
	way_to_the_light = 0;
	point = disp_p.intersec_point;
	rayvec[0] = objs->li[0].position.x - point.x;
	rayvec[1] = objs->li[0].position.y - point.y;
	rayvec[2] = objs->li[0].position.z - point.z;
	//du coup il faut connaitre lui meme
	//ca revient au meme probleme
	//lets go
	//le probleme se pose lorsqu'il s'intersecte avec lui-meme
	rayline = get_rayline_eq(rayvec, point);
	if (!get_sphere(objs, &list, rayline, disp_p.obj_id))
		return (false);
	if (!get_plane(objs, &list, rayline, disp_p.obj_id))
		return (false);
	intersection = fill_list_intersection(objs, &list);
	//way_to_the_light = intersect_plane(objs);
	//if (way_to_the_light == -1)
	//	return (false);
	//les -1 pas bien parce que ca pourrait etre -1
	if (list != NULL)
	{
		return (true);
	}
	/*else
	{
		if (disp_p.type == PL)
		{
			if (way_to_the_light == 0)
				return (true);
		}
	}*/
	//there is a way to the light, now let's calculate the distance the compute the intensity of the light
	//distance between disp_p and light
	//distance is norm of rayvec
	compute_RGB(objs, norm_of_vector(rayvec), RGB);
	free_list(&list);
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
