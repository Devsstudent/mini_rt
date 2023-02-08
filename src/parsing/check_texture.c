/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:20:43 by odessein          #+#    #+#             */
/*   Updated: 2023/02/08 13:53:55 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	check_path(char *path)
{
	size_t	size;

	if (!path)
		return (false);
	size = ft_strlen(path);
	if (size >= 2 && !ft_strncmp(path, "da", 3))
		return (true);
	else if (size > 4 && (path[size - 1] != 'm' || path[size - 2] != 'p'
			|| path[size - 3] != 'x' || path[size - 4] != '.'))
		return (false);
	else if (size < 4)
		return (false);
	if (access(path, F_OK) == -1 || open(path, O_RDONLY) == -1)
		return (false);
	return (true);
}

bool	check_texture(t_obj_texture *tex, char *path, t_objects *objs)
{
	if (!path)
		return (false);
	if (!ft_strncmp(path, "da", 3))
			tex->tex = DAM;
	else
	{
		tex->img = mlx_xpm_file_to_image(objs->mlx->mlx,
				path, &tex->width, &tex->height);
		if (!tex->img)
		{
			ft_putstr_fd("Error\nError occured while opening the image, \
check your file\n", 2);
			return (false);
		}
		tex->tex = TEX;
		tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
				&tex->line_size, &tex->endian);
	}
	return (true);
}
