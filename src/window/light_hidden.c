/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_hidden.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:08:34 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/20 16:46:26 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

static bool	light_hidden_in_plane(t_objects *objs, t_line_eq rayline,
		t_vect rayvec)
{
	int				j;
	t_sol_li		list;
	t_disp_point	intersection;

	init_sol_li(&list);
	j = 0;
	while (j < objs->nb_pl)
	{
		if (!get_specific_plane(objs, &list, rayline, j))
			return (free_list(&list), true); //see what happens when gsc is 0
		intersection = get_intersection(&list, objs->cam->position);
		if (list.head != NULL && list.head->solution.sol_one
			&& in_the_way(intersection.intersec_point, rayvec,
			objs->cam->position))
		{
			return (free_list(&list), true);
		}
		free_list(&list); 
		j++;
	}
	return (false);
}

static bool	light_hidden_in_sphere(t_objects *objs, t_line_eq rayline,
		t_vect rayvec)
{
	int				j;
	t_sol_li		list;
	t_disp_point	intersection;

	init_sol_li(&list);
	j = 0;
	while (j < objs->nb_sp)
	{
		if (!get_specific_sphere(objs, &list, rayline, j))
			return (free_list(&list), true); //see what happens when gsc is 0
		intersection = get_intersection(&list, objs->cam->position);
		if (list.head != NULL && list.head->solution.sol_one
			&& in_the_way(intersection.intersec_point, rayvec,
			objs->cam->position))
		{
			return (free_list(&list), true);
		}
		free_list(&list); 
		j++;
	}
	return (false);
}

static bool	light_hidden_in_cylinder(t_objects *objs, t_line_eq rayline,
		t_vect rayvec)
{
	int				j;
	t_sol_li		list;
	t_disp_point	intersection;

	init_sol_li(&list);
	j = 0;
	while (j < objs->nb_cy)
	{
		if (!get_specific_cylinder(objs, &list, rayline, j))
			return (free_list(&list), true); //see what happens when gsc is 0
		intersection = get_intersection(&list, objs->cam->position);
		if (list.head != NULL && list.head->solution.sol_one
			&& in_the_way(intersection.intersec_point, rayvec,
			objs->cam->position))
		{
			return (free_list(&list), true);
		}
		free_list(&list); 
		j++;
	}
	return (false);
}

void	is_light_hidden(t_objects *objs)
{
	int			i;
	t_line_eq	rayline;
	t_vect		rayvec;

	i = 0;
	while (i < objs->nb_li)
	{
		rayvec[0] = objs->li[i].position.x - objs->cam->position.x;
		rayvec[1] = objs->li[i].position.y - objs->cam->position.y;
		rayvec[2] = objs->li[i].position.z - objs->cam->position.z;
		rayline = get_rayline_eq(rayvec, objs->cam->position);
		if (light_hidden_in_plane(objs, rayline, rayvec)
			|| light_hidden_in_sphere(objs, rayline, rayvec)
			|| light_hidden_in_cylinder(objs, rayline, rayvec))
		{
			objs->li[i].hidden = true;
		}
		i++;
	}
}
