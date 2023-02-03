/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:53:48 by odessein          #+#    #+#             */
/*   Updated: 2023/02/03 14:57:37 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

void	error_msg(char *str)
{
	if (!str)
		return ;
	write(2, str, ft_strlen(str));
}

void	free_exit(void *objs)
{
	if (objs)
		close_window((t_objects *) objs);
	exit(0);
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
	if (obj->cam)
		free(obj->cam);
	if(obj->amb)
		free(obj->amb);
}

void	free_list_exit(t_objects *objs, t_sol_li *list)
{
	free_list(list);
	free_exit(objs);
}

t_disp_point	error_intersec(void)
{
	t_disp_point	res;

	res.err = true;
	return (res);
}
