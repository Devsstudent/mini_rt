/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelrhaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:37:21 by mbelrhaz          #+#    #+#             */
/*   Updated: 2023/01/25 18:03:57 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		triple_arr[i] = split_func_condition(lines[i], ft_is_space);
		if (triple_arr[i] == NULL)
			return (free_triple_arr(triple_arr), free_double_arr(lines), NULL);
		i++;
	}
	triple_arr[i] = NULL;
	return (free_double_arr(lines), triple_arr);
}

bool	match_obj(char ***triple_arr, char *type, int i)
{
	if ((triple_arr[i][0][0] == type[0]
		|| triple_arr[i][0][0] == type[0] + 32)
		&& triple_arr[i][0][1] == type[1])
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
		if (match_obj(triple_arr, type, i))
			size++;
		i++;
	}
	return (size);
}

bool	fill_each_struct(char ***triple_arr, t_objects *objects)
{
	int		i;
	bool	ret[7];
	bool	final_ret;

	final_ret = true;
	ret[0] = build_ambient_light(triple_arr, objects);
	ret[1] = build_camera(triple_arr, objects);
	ret[2] = build_light(triple_arr, objects);
	ret[3] = build_cylinder(triple_arr, objects);
	ret[4] = build_sphere(triple_arr, objects);
	ret[5] = build_plane(triple_arr, objects);
	ret[6] = build_cones(triple_arr, objects);
	i = -1;
	while (++i < 7)
		final_ret = final_ret & ret[i];
	return (final_ret);
}

bool	fill_structs(char **lines, t_objects *objects)
{
	char	***triple_arr;

	triple_arr = create_triple_arr(lines);
	if (!triple_arr)
		return (false);
	if (!fill_each_struct(triple_arr, objects))
		return (free_structs(objects), free_triple_arr(triple_arr), false);
	return (free_triple_arr(triple_arr), true);
}
