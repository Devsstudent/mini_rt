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

void	free_objs(t_objects *objs)
{
	free(objs->sp);
	free(objs->li);
	free(objs->cy);
	free(objs->pl);
	free(objs->cam);
	free(objs->amb);
}
//we should need free exit funct
///void	free_exit()


