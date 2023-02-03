/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:12:33 by odessein          #+#    #+#             */
/*   Updated: 2023/02/03 15:29:17 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "window.h"

int	close_window(t_objects *objs)
{
	mlx_destroy_image(objs->mlx->mlx, objs->mlx->img);
	mlx_destroy_window(objs->mlx->mlx, objs->mlx->win);
	free_objs(objs);
	mlx_destroy_display(objs->mlx->mlx);
	free(objs->mlx->mlx);
	free(objs->mlx);
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

void	window(t_objects *objs)
{
	mlx_loop_hook(objs->mlx->mlx, &(render_window), objs);
	mlx_hook(objs->mlx->win, 33, 1L << 1, &(close_window), objs);
	mlx_hook(objs->mlx->win, 2, 1L << 1, &(hook_release), objs->mlx);
	mlx_hook(objs->mlx->win, 2, 1L << 0, &(hook_press), objs);
	mlx_loop(objs->mlx->mlx);
}
