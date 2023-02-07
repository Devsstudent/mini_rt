/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:36:58 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/02/06 22:51:21 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	free_cy(t_objects *objs, t_cylinder *cy)
{
	int	i;

	i = 0;
	while (i < objs->nb_cy)
	{
		if (cy[i].tex.tex == TEX)
			mlx_destroy_image(objs->mlx->mlx, cy[i].tex.img);
		i++;
	}
	free(cy);
}

void	free_pl(t_objects *objs, t_plane *pl)
{
	int	i;

	i = 0;
	while (i < objs->nb_pl)
	{
		if (pl[i].tex.tex == TEX)
			mlx_destroy_image(objs->mlx->mlx, pl[i].tex.img);
		i++;
	}
	free(pl);
}

void	free_sp(t_objects *objs, t_sphere *sp)
{
	int	i;

	i = 0;
	while (i < objs->nb_sp)
	{
		if (sp[i].tex.tex == TEX)
			mlx_destroy_image(objs->mlx->mlx, sp[i].tex.img);
		i++;
	}
	free(sp);
}

void	free_co(t_objects *objs, t_cone *co)
{
	int	i;

	i = 0;
	while (i < objs->nb_co)
	{
		if (co[i].tex.tex == TEX)
			mlx_destroy_image(objs->mlx->mlx, co[i].tex.img);
		i++;
	}
	free(co);
}

void	free_objs(t_objects *obj)
{
	if (obj->nb_cy)
		free_cy(obj, obj->cy);
	if (obj->nb_pl)
		free_pl(obj, obj->pl);
	if (obj->nb_sp)
		free_sp(obj, obj->sp);
	if (obj->nb_li)
		free(obj->li);
	if (obj->nb_co)
		free_co(obj, obj->co);
	free(obj->cam);
	free(obj->amb);
}
