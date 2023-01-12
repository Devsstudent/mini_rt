/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:53:48 by odessein          #+#    #+#             */
/*   Updated: 2022/12/04 21:31:35 by mbelrhaz         ###   ########.fr       */
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
	if (obj->cy)
		free(obj->cy);
	if (obj->pl)
		free(obj->pl);
	if (obj->sp)
		free(obj->sp);
	if (obj->li)
		free(obj->li);
	free(obj->cam);
	free(obj->amb);
	free(obj->mlx);
}

void	free_list_exit(t_objects *objss, t_sol_li *list)
{
	free_list(list);
	free_exit(objss);
}

t_disp_point	error_intersec(void)
{
	t_disp_point	res;

	res.err = true;
	return (res);
}


//we should need free exit funct
///void	free_exit()


