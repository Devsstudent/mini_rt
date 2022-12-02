/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:57:53 by odessein          #+#    #+#             */
/*   Updated: 2022/12/02 16:38:06 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

//check_int_max value (digit by digit from char *)

bool	check_int_max(char *str)
{
	if (ft_atoi(str) == 2147483648)
		return (false);
	return (true);
}

bool	free_split_return_false(char **line_split)
{
	int	i;

	i = 0;
	while (line_split[i])
	{
		free(line_split[i]);
		i++;
	}
	free(line_split[i]);
	return (false);
}

bool	ft_is_space(char c)
{
	if (c < 15 && c > 6)
		return (true);
	if (c == 32)
		return (true);
	return (false);
}

bool	free_array_function(t_function_parsing *arr)
{
	int	i;

	i = 0;
	while (i < ELEM_MAX)
	{
		free(arr[i].letter);
		i++;
	}
	free(arr);
	return (false);
}
