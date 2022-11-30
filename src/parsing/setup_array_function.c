/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_array_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:19:18 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 15:35:11 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static bool	attribute_function_letter(bool (*func)(), t_function_parsing *arr, char *letter)
{
	arr->f = func;
	arr->letter = ft_strdup(letter);
	if (!arr->letter)
		return(false);
	return (true);
}

bool	setup_array_function(t_function_parsing *arr)
{
	int		i;
	bool	res;

	arr = malloc(sizeof(t_function_parsing) * (ELEM_MAX + 1));
	if (!arr)
		return (false);
	i = 0;
	while (i < ELEM_MAX)
	{
		if (i == 0)
			res = attribute_function_letter(check_ambient, &arr[i], "A");
		if (i == 1)
			res = attribute_function_letter(check_light, &arr[i], "L");
		if (i == 2)
			res = attribute_function_letter(check_light, &arr[i], "l");
		if (i == 3)
			res = attribute_function_letter(check_camera, &arr[i], "C");
		if (i == 4)
			res = attribute_function_letter(check_sphere, &arr[i], "sp");
		if (i == 5)
			res = attribute_function_letter(check_plane, &arr[i], "pl");
		if (i == 6)
			res = attribute_function_letter(check_cylinder, &arr[i], "cy");
		if (!res)
			return (false);
		i++;
	}
	arr[i].f = NULL;
	return (true);
}

