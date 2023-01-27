/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_store_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:54:12 by odessein          #+#    #+#             */
/*   Updated: 2023/01/27 10:38:22 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "texture.h"

bool	open_store_texture(t_objects *objs)
{
	int	i;
	int	w;
	int	h;

	i = 0;
	objs->mlx->texture->textures = malloc(sizeof(t_detail) * nb_textures);
	while (i < nb_textures)
	{
		objs->texture->textures[i] = mlx_xpm_file_to_image(objs->mlx->mlx, objs->texture.paths[i], &(objs->mlx->texture->textures[i].width, &(objs->mlx->texture->textures[i].height)));
		if (objs->texture->textures[i])
		{
			free_double_arr(objs->texture.paths);
			return (false);
		}
		i++;
	}
	free_double_arr(objs->texture.paths);
	return (true);
}
