/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_array_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:19:18 by odessein          #+#    #+#             */
/*   Updated: 2023/01/25 17:56:48 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	attribute_function_letter(bool (*func)(),
				t_function_parsing *arr, char *letter)
{
	if (!letter)
		return (false);
	arr->f = func;
	arr->letter = ft_strdup(letter);
	if (!arr->letter)
		return (false);
	return (true);
}

static bool	loop_attribute_func(t_function_parsing **arr, bool *res)
{
	int		i;

	i = 0;
	while (i < ELEM_MAX)
	{
		if (i == 0)
			*res = attribute_function_letter(check_ambient, &(*arr)[i], "A");
		if (i == 1)
			*res = attribute_function_letter(check_light, &(*arr)[i], "L");
		if (i == 2)
			*res = attribute_function_letter(check_camera, &(*arr)[i], "C");
		if (i == 3)
			*res = attribute_function_letter(check_sphere, &(*arr)[i], "SP");
		if (i == 4)
			*res = attribute_function_letter(check_plane, &(*arr)[i], "PL");
		if (i == 5)
			*res = attribute_function_letter(check_cylinder, &(*arr)[i], "CY");
		if (i == 6)
			*res = attribute_function_letter(check_cones, &(*arr)[i], "CO");
		if (!(*res))
			return (false);
		i++;
	}
	(*arr)[i].f = NULL;
	return (true);
}

bool	setup_array_function(t_function_parsing **arr)
{
	bool	res;

	*arr = malloc(sizeof(t_function_parsing) * (ELEM_MAX + 1));
	if (!*arr)
		return (false);
	res = false;
	if (!loop_attribute_func(arr, &res))
		return (false);
	return (true);
}
