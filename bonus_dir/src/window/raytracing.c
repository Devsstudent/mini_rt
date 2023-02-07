/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:33:51 by odessein          #+#    #+#             */
/*   Updated: 2023/02/06 23:55:32 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	loop_rendering(t_objects *objs, t_viewplan view_plan)
{
	int	i;

	i = 0;
	while (i < WIN_H)
	{
		if (!loop_line(objs, &view_plan, i))
			return (false);
		i++;
	}
	mlx_put_image_to_window(objs->mlx->mlx, objs->mlx->win,
		objs->mlx->img, 0, 0);
	return (true);
}

bool	loop_line(t_objects *objs, t_viewplan *view_plan, int i)
{
	int				j;
	t_sol_li		list;
	t_vect			rayvec;
	t_i_j			i_j;

	j = 0;
	while (j < WIN_W)
	{
		init_sol_li(&list);
		i_j.i = i;
		i_j.j = j;
		rayvec = get_vector(view_plan->up_left,
				multp(get_opposite_vector(view_plan->hori), j),
				multp(get_opposite_vector(view_plan->verti), i));
		if (!resolve_equation(objs, &list, rayvec, i_j))
			return (false);
		j++;
	}
	return (true);
}
