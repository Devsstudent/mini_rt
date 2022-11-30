/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:26:25 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 15:48:13 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

bool	brows_arr_function(char *first, char **line_split,
			t_function_parsing *arr, t_must_have *all_elem)
{
	int	i;

	i = 0;
	while (arr[i].f != NULL)
	{
		if (!ft_strncmp(first, arr[i].letter, 3))
		{
			if (!(*arr[i].f)(line_split, all_elem))
				return (false);
			else
				return (true);
		}
		i++;
	}
	return (false);
}

bool	check_line(char *line, t_function_parsing *arr, t_must_have *all_elem)
{
	char			**line_split;

	line_split = split_func_condition(line, ft_is_space);
	if (!line_split)
		return (free_split_return_false(line_split));
	if (!brows_arr_function(line_split[0], line_split, arr, all_elem))
		return (free_split_return_false(line_split));
	if (!check_all_elem(*all_elem))
		return (free_split_return_false(line_split));
	free_split_return_false(line_split);
	return (true);
}
