/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:20:43 by odessein          #+#    #+#             */
/*   Updated: 2023/01/30 21:37:46 by odessein         ###   ########.fr       */
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

bool	check_texture(t_obj_texture *tex, char *path, int i, t_type type)
{
	if (!path)
		return (false);
	tex->path = NULL;
	if (!ft_strncmp(path, "da", 3))
			tex->tex = DAM;
	else
	{
			tex->tex = TEX;
			tex->path = path;
			tex->type = type;
			tex->id = i;
	}
	return (true);
}
