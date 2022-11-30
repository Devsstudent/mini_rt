/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:57:53 by odessein          #+#    #+#             */
/*   Updated: 2022/11/30 21:55:40 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

//check_int_max value (digit by digit from char *)

bool	check_int_max(char *str)
{
	if (str[0] == '2' && str[1] == '1' && str[2] == '4' && str[3] == '7' && str[4] == '4' && str[5] == '8' && str[6] == '3' && str[7] == '6' && str[8] == '4' && str[9] == '7' && !str[10])
		return (true);
	return (false);
}

bool	check_int_min(char *str)
{
	if (str[0] == '-' && str[1] == '2' && str[2] == '1' && str[3] == '4' && str[4] == '7' && str[5] == '4' && str[6] == '8' && str[7] == '3' && str[8] == '6' && str[9] == '4' && str[10] == '8' && !str[11])
		return (true);
	return (false);
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
