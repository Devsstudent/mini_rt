/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:12:33 by odessein          #+#    #+#             */
/*   Updated: 2023/01/11 19:30:15 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

int	close_window(t_objects *objs)
{
	mlx_destroy_image(objs->mlx->mlx, objs->mlx->img);
	mlx_destroy_window(objs->mlx->mlx, objs->mlx->win);
	mlx_destroy_display(objs->mlx->mlx);
	free(objs->mlx->mlx);
	free_objs(objs);
	exit(0);
	return (0);
}

int	hook_press(int keycode, t_objects *objs)
{
	if (keycode == ESC)
		close_window(objs);
	if (keycode == E)
	{
		mlx_destroy_image(objs->mlx->mlx, objs->mlx->img);
		objs->mlx->img = mlx_new_image(objs->mlx->mlx, WIN_W, WIN_H);
		if (!objs->mlx->img)
			free_exit(objs);
		objs->edited = false;
		edit_objs(objs);
	}
	return (0);
}

int	hook_release(int keycode, t_mlx_info *mlx)
{
	(void)(keycode);
	(void) mlx;
	return (0);
}

void	img_pixel_put(t_mlx_info *mlx, int j, int i, int color)
{
	char	*data_img;
	int		addon ;

	data_img = mlx->data;
	addon = (j * (mlx->bpp / 8)) + (i * mlx->line_size);
	*(unsigned int *)(data_img + addon) = color;
}

bool	window(t_objects *objs)
{
	objs->mlx->mlx = mlx_init();
	objs->edited = false;
	if (!objs->mlx->mlx)
		return (false);
	objs->mlx->win = mlx_new_window(objs->mlx->mlx, 780, 540, "mini_rt :)");
	if (!objs->mlx->win)
		return (false);
	objs->mlx->img = mlx_new_image(objs->mlx->mlx, WIN_W, WIN_H);
	if (!objs->mlx->img)
		return (false);
	objs->mlx->data = mlx_get_data_addr(objs->mlx->img, &objs->mlx->bpp,
			&objs->mlx->line_size, &objs->mlx->endian);
	mlx_loop_hook(objs->mlx->mlx, &(render_window), objs);
	mlx_hook(objs->mlx->win, 33, 1L << 1, &(close_window), objs);
	mlx_hook(objs->mlx->win, 2, 1L << 1, &(hook_release), objs->mlx);
	mlx_hook(objs->mlx->win, 2, 1L << 0, &(hook_press), objs);
	mlx_loop(objs->mlx->mlx);
	return (true);
}
