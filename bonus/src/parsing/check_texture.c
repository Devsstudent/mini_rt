/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:20:43 by odessein          #+#    #+#             */
/*   Updated: 2023/01/31 12:34:17 by odessein         ###   ########.fr       */
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
	if (access(path, F_OK) == -1)
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
			tex->img = mlx_xpm_file_to_image(objs->mlx->mlx, path, &tex->width, &tex->height);
			tex->tex = TEX;
	}
	return (true);
}
