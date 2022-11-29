/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:37:21 by mbelrhaz          #+#    #+#             */
/*   Updated: 2022/11/29 16:43:07 by mbelrhaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_double_arr(char **double_arr)
{
	int	i;

	i = 0;
	while (double_arr[i])
	{
		free(double_arr[i]);
		i++;
	}
	free(double_arr);
}

void	free_triple_arr(char ***triple_arr)
{
	int	i;

	i = 0;
	while (triple_arr[i])
	{
		free_double_arr(triple_arr[i]);
		i++;
	}
	free(triple_arr);
}

char	***create_triple_arr(char **lines)
{
	char	***triple_arr;
	int		i;
	int		size;

	i = 0;
	while (lines[i])
		i++;
	triple_arr = malloc(sizeof(char **) * (i + 1));
	if (!triple_arr)
		return (free_double_arr(lines), NULL);
	size = i;
	i = 0;
	while (i < size)
	{
		triple_arr[i] = ft_split(line[i], ' ');
		if (triple_arr[i] == NULL)
			return (free_triple_arr(triple_arr), free_double_arr(lines), NULL);
		i++;
	}
	triple_arr[i] = NULL;
	return (free_double_arr(lines), triple_arr);
}

bool	match_obj(char ***triple_arr, char *type)
{
	if (triple_arr[i][0][0] == type[0] && triple_arr[i][0][1] == type[1])
		return (true);
	return (false);
}

int	count_obj(char ***triple_arr, char *type)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, type))
			size++;
		i++;
	}
	return (size);
}

bool	convert_to_float(float *val, char *arr)
{
	int		i;
	int		j;
	int		dot;
	char	*nb;

	i = 0;
	j = 0;
	dot = 0;
	nb = malloc(sizeof(char) * (ft_strlen(arr) + 1));
	if (!nb)
		return (false);
	while (arr[i])
	{
		if (arr[i] == '.')
		{
			dot = 1;
			if (arr[i + 1] && arr[i + 2] != '\0')
				dot++;
			i++;
			continue ;
		}
		nb[j] = arr[i];
		j++;
		i++;
	}
	nb[j] = '\0';
	if (dot == 1)
		*val = (float)(ft_atoi(nb)) / 10.0;
	else if (dot == 2)
		*val = (float)(ft_atoi(nb)) / 100.0;
	else
		*val = ft_atoi(nb);
	return (free(nb), true);
}

void	convert_to_rgb(t_rgb *rgb, char *arr)
{
	char	rgb_arr[3][4];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		rgb_arr[i][0] = arr[j++];
		rgb_arr[i][1] = arr[j++];
		rgb_arr[i][2] = arr[j++];
		rgb_arr[i][3] = '\0';
		j++;
		i++;
	}
	rgb->R = ft_atoi(rgb_arr[0]);
	rgb->G = ft_atoi(rgb_arr[1]);
	rgb->B = ft_atoi(rgb_arr[2]);
}

bool	convert_to_xyz(t_xyz *xyz, char *arr)
{
	char	**xyz_arr;
	int		i;

	i = 0;
	xyz_arr = ft_split(arr, ',');
	if (!xyz_arr)
		return (false);
	if (!convert_to_float(&xyz->x), xyz_arr[0])
		return (free_double_arr(xyz_arr), false);
	if (!convert_to_float(&xyz->y), xyz_arr[1])
		return (free_double_arr(xyz_arr), false);
	if (!convert_to_float(&xyz->z), xyz_arr[2])
		return (free_double_arr(xyz_arr), false);
	return (free_double_arr(xyz_arr), true);
}

bool	convert_to_orientation(t_orientation *xyz, char *arr)
{
	char	**xyz_arr;
	int		i;

	i = 0;
	xyz_arr = ft_split(arr, ',');
	if (!xyz_arr)
		return (false);
	if (!convert_to_float(&xyz->x), xyz_arr[0])
		return (free_double_arr(xyz_arr), false);
	if (!convert_to_float(&xyz->y), xyz_arr[1])
		return (free_double_arr(xyz_arr), false);
	if (!convert_to_float(&xyz->z), xyz_arr[2])
		return (free_double_arr(xyz_arr), false);
	return (free_double_arr(xyz_arr), true);
}

bool	fill_ambient_light(char **arr, int j, t_objects *objects)
{
	if (!convert_to_float(&objects->amb[j].ratio, arr[1]))
		return (false);
	convert_to_rgb(&objects->amb[j].color, arr[2]);
	return (true);
}

bool	fill_camera(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->cam[j].position, arr[1]))
		return (false);
	if (!convert_to_orientation(&objects->cam[j].vec_direction, arr[2]))
		return (false);
	objects->cam[j].fov = ft_atoi(arr[3]);
	return (true);
}

bool	fill_light(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->li[j].position, arr[1]))
		return (false);
	if (!convert_to_float(&objects->li[j].ratio, arr[2]))
		return (false);
	convert_to_rgb(&objects->li[j].color, arr[3]);
	return (true);
}

bool	fill_sphere(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->sp[j].position, arr[1]))
		return (false);
	if (!convert_to_float(&objects->sp[j].diameter, arr[2]))
		return (false);
	convert_to_rgb(&objects->sp[j].color, arr[3]);
	return (true);
}

bool	fill_plane(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->pl[j].position, arr[1]))
		return (false);
	if (!convert_to_orientation(&objects->pl[j].vec_direction, arr[2]))
		return (false);
	convert_to_rgb(&objects->pl[j].color, arr[3]);
	return (true);
}

bool	fill_cylinder(char **arr, int j, t_objects *objects)
{
	if (!convert_to_xyz(&objects->cy[j].position, arr[1]))
		return (false);
	if (!convert_to_orientation(&objects->cy[j].vec_direction, arr[2]))
		return (false);
	if (!convert_to_float(&objects->cy[j].diameter, arr[3]))
		return (false);
	if (!convert_to_float(&objects->cy[j].height, arr[4]))
		return (false);
	convert_to_rgb(&objects->cy[j].color, arr[5]);
	return (true);
}

bool	build_plane(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = count_obj(triple_arr, "pl");
	objects->pl = malloc(sizeof(t_plane) * (size + 1));
	if (!objects->pl)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "pl"))
		{
			if (!fill_plane(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	objects->pl[j] = NULL;
	return (true);
}


bool	build_cylinder(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = count_obj(triple_arr, "cy");
	objects->cy = malloc(sizeof(t_cylinder) * (size + 1));
	if (!objects->cy)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "cy"))
		{
			if (!fill_cylinder(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	objects->cy[j] = NULL;
	return (true);
}

bool	build_sphere(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = count_obj(triple_arr, "sp");
	objects->sp = malloc(sizeof(t_sphere) * (size + 1));
	if (!objects->sp)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "sp"))
		{
			if (!fill_sphere(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	objects->sp[j] = NULL;
	return (true);
}

bool	build_light(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = count_obj(triple_arr, "L");
	objects->li = malloc(sizeof(t_light) * (size + 1));
	if (!objects->li)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "L"))
		{
			if (!fill_light(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	objects->li[j] = NULL;
	return (true);
}

bool	build_camera(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	objects->cam = malloc(sizeof(t_camera) * 2);
	if (!objects->cam)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "C"))
		{
			if (!fill_ambient_light(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	objects->cam[j] = NULL;
	return (true);
}

bool	build_ambient_light(char ***triple_arr, t_objects *objects)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	objects->amb = malloc(sizeof(t_ambient_light) * 2);
	if (!objects->amb)
		return (false);
	while (triple_arr[i])
	{
		if (match_obj(triple_arr, "A"))
		{
			if (!fill_ambient_light(triple_arr[i], j, objects))
				return (false);
			j++;
		}
		i++;
	}
	objects->amb[j] = NULL;
	return (true);
}

bool	fill_each_struct(char ***triple_arr, t_objects *objects)
{
	int		i;
	bool	ret[6];
	bool	final_ret;

	final_ret = true;
	ret[0] = build_ambient_light(triple_arr, objects);
	ret[1] = build_camera(triple_arr, objects);
	ret[2] = build_light(triple_arr, objects);
	ret[3] = build_cylinder(triple_arr, objects);
	ret[4] = build_sphere(triple_arr, objects);
	ret[5] = build_plane(triple_arr, objects);
	i = 0;
	while (i < 6)
	{
		final_ret = final_ret & ret[i];
		i++;
	}
	return (final_ret);
}

void	free_structs(t_objects *objects)
{
	free(objects->amb);
	free(objects->cam);
	free(objects->li);
	free(objects->sp);
	free(objects->pl);
	free(objects->cy);
}

bool	fill_structs(char **lines, t_objects *objects)
{
	char	***triple_arr;

	triple_arr = create_triple_arr(lines);
	if (!triple_arr)
		return (false);
	if (!fill_each_struct(triple_arr, objects))
		return (free_structs(objects), false);
	return (true);
}
