/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:12:33 by odessein          #+#    #+#             */
/*   Updated: 2022/12/06 10:20:55 by odessein         ###   ########.fr       */
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

bool	window(t_objects *objs, t_mlx_info *mlx)
{
	(void) objs;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (false);
	//window size to define depending on fov etc ??
	mlx->win = mlx_new_window(mlx->mlx, 1920, 1080, "mini_rt :)");
	if (!mlx->win)
		return (false);
	mlx_hook(mlx->win, 33, 1L << 1, &(close_window), mlx);
	mlx_hook(mlx->win, 2, 1L << 1, &(hook_release), mlx);
	mlx_hook(mlx->win, 2, 1L << 0, &(hook_press), mlx);
	mlx_loop(mlx->mlx);
	return (true);
}
