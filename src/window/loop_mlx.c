/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:12:33 by odessein          #+#    #+#             */
/*   Updated: 2022/12/12 16:43:44 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

int	close_window(t_mlx_info *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

int	hook_press(int keycode, t_mlx_info *mlx)
{
	if (keycode == ESC)
		close_window(mlx);
	return (0);
}

int	hook_release(int keycode, t_mlx_info *mlx)
{
	(void)(keycode);
	(void) mlx;
	return (0);
}

bool	window(t_objects *objs)
{
	objs->mlx->mlx = mlx_init();
	if (!objs->mlx->mlx)
		return (false);
	objs->mlx->win = mlx_new_window(objs->mlx->mlx, 780, 540, "mini_rt :)");
	if (!objs->mlx->win)
		return (false);
	mlx_loop_hook(objs->mlx->mlx, &(render_window), objs);
	mlx_hook(objs->mlx->win, 33, 1L << 1, &(close_window), objs->mlx);
	mlx_hook(objs->mlx->win, 2, 1L << 1, &(hook_release), objs->mlx);
	mlx_hook(objs->mlx->win, 2, 1L << 0, &(hook_press), objs->mlx);
	mlx_loop(objs->mlx->mlx);
	return (true);
}
