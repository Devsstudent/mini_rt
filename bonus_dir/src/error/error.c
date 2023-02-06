/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:53:48 by odessein          #+#    #+#             */
/*   Updated: 2023/02/06 22:44:59 by mbelrhaz         ###   ########.fr       */
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
